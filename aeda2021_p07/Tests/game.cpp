#include "game.h"
#include <sstream>


ostream &operator << (ostream &os, Circle &c1)
{
    // “points-state-nVisits\nl”
    os << c1.points << "-";
    if(c1.state)
        os << "true";
    else
        os << "false";
    os << "-" << c1.nVisits << endl;
	return os;
}


Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    game = initGame(0, h, points, states);
}

BinaryTree<Circle>Game::initGame(int pos,int niv, vector<int> &points, vector<bool> &states){

    Circle c1(points[pos],states[pos]);
    if (niv==0)
        return BinaryTree<Circle>(c1);

    BinaryTree<Circle> filhoEsq = initGame(2*pos+1,niv-1,points, states);
    BinaryTree<Circle> filhoDir = initGame(2*pos+2,niv-1,points, states);

    return BinaryTree<Circle>(c1, filhoEsq, filhoDir);
}


string Game::writeGame()
{
    BTItrLevel<Circle> it(game);
	/*string info = "";

    // “points-state-nVisits\nl”
	while (!it.isAtEnd()){
	    info += to_string(it.retrieve().getPoints()) + "-";
	    if(it.retrieve().getState())
	        info += "true-";
	    else
	        info += "false-";
	    info += to_string(it.retrieve().getNVisits()) + "\n";
	    it.advance();
	}
	return info;*/

	stringstream info("");
    while (!it.isAtEnd()){
        info << it.retrieve();
        it.advance();
    }
    return info.str();

}


int Game::move()
{
    int pos = 1; int pontos = -1;
    BTItrLevel<Circle> it(game);

    if (it.isAtEnd())
        return pontos;

    while (true) {
        Circle &c1 = it.retrieve();
        bool estado = c1.getState();
        int n;

        // Bola para esquerda
        if (!estado)
            n = pos;
        // Bola para direita
        else
            n = pos + 1;

        c1.changeState();
        c1.incNVisits();

        pontos = c1.getPoints();
        int i = 0;

        while(i < n && !it.isAtEnd()) {
            it.advance();        // avanca p/ filho esquerdo ou direito
            i++;
        }
        if (!it.isAtEnd())
            pos += n;
        else
            break;
    }
    return pontos;
}


int Game::mostVisited()
{
    BTItrLevel<Circle> it(game);
    int nVisits = -1;
    if(it.isAtEnd())
        return nVisits;
    it.advance();

    while (!it.isAtEnd()){
        if(it.retrieve().getNVisits() > nVisits){
            nVisits = it.retrieve().getNVisits();
        }
        it.advance();
    }
    return nVisits;
}
