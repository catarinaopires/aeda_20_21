#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}

bool sortkarts(CKart c1, CKart c2){
    return c1.getNumero() < c2.getNumero();
}

//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
	for(size_t i = 0; i < pistasG.size(); i++){
        for(size_t j = 0; j < pistasG[i].getFrotaActual().size(); j++){
            vord.push_back(pistasG[i].getFrotaActual()[j]);
        }
	}
	sort(vord.begin(), vord.end(), sortkarts);
	return vord;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    int counter = 0;
    for(size_t i = 0; i < pistasG.size(); i++){
        for(size_t j = 0; j < pistasG[i].getKartsAvariados().size(); j++){
            if(pistasG[i].getKartsAvariados()[j].getCilindrada() == cilind)
                counter++;
        }
    }
    return counter;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    bool notEnough = false;
    queue<CKart> corrida;
    for(size_t i = 0; i < frotaKartsPista.size(); i++){
        if(frotaKartsPista[i].getCilindrada() == cilind && !frotaKartsPista[i].getAvariado()) {
            corrida.push(frotaKartsPista[i]);
        }
    }
    if(corrida.size() < numeroKarts)
        notEnough = true;

    while(!corrida.empty()){
        kartsLinhaPartida.push(corrida.front());
        corrida.pop();
    }

    return notEnough;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    while(!kartsLinhaPartida.empty()){
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }

    return kartsEmProva.size();
}

