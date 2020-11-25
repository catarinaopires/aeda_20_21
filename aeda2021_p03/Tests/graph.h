#include <iostream>
#include <vector>
#include<iterator>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};


// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists {
public:
    N begin;
    N dest;
    EdgeAlreadyExists(N b, N e) {
        begin = b;
        dest = e;
    }
};

template<class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &e)
{ out << "Edge already exists: " << e.begin << " , " << e.dest; return out; }

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template <class N>
class EdgeDoesNotExist{
public:
    N begin;
    N dest;
    EdgeDoesNotExist(N b, N e) {
        begin = b;
        dest = e;
    }
};

template<class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &e)
{ out << "Edge does not exist: " << e.begin << " , " << e.dest; return out; }

/**
 * Graph constructor
 *
 * @tparam N Node
 * @tparam E Edge
 */
template<class N, class E>
Graph<N,E>::Graph(){

}

/**
 * Graph destructor
 * @tparam N  Node
 * @tparam E Edge
 */
template<class N, class E>
Graph<N,E>::~Graph(){
    typename vector< Node<N,E> *>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
        delete *it;
}

/**
 * Number of nodes in graph
 * @tparam N Node
 * @tparam E Edge
 * @return Number of nodes
 */
template<class N, class E>
unsigned Graph<N,E>::numNodes(void) const{
    return nodes.size();
}

/**
 * Number of edges in graph
 * @tparam N Node
 * @tparam E Edge
 * @return Number of edges
 */
template<class N, class E>
unsigned Graph<N,E>::numEdges(void) const{
    unsigned nrEdges = 0;

    typename vector< Node<N,E> *>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++){
        nrEdges += (*it)->edges.size();
    }

    return nrEdges;
}

/**
 * Add node into graph
 * @tparam N Node
 * @tparam E Edge
 * @param inf Node to be inserted
 * @return Reference to the graph modified
 */
template<class N, class E>
Graph<N,E> & Graph<N,E>::addNode(const N &inf){

    bool nodeExists = false;

    for (int i = 0; i < nodes.size(); i++){
        if(nodes[i]->info == inf)
           nodeExists = true;
    }

    if(!nodeExists){
        Node<N, E> *n = new Node<N, E>(inf);
        nodes.push_back(n);
    }
    else
        throw NodeAlreadyExists<N>(inf);

    return *this;
}

/**
 * Add Edge between nodes in graph
 * @tparam N Node
 * @tparam E Edge
 * @param begin Node where edge begins
 * @param end Node where edge ends
 * @param val Value of the edge
 * @return Reference to the graph modified
 */
template<class N, class E>
Graph<N,E> & Graph<N,E>::addEdge(const N &begin, const N &end, const E &val){

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->info == begin) {
            for (int j = 0; j < nodes[i]->edges.size(); j++) {
                if (nodes[i]->edges[j].destination->info == end)
                    throw EdgeAlreadyExists<N>(begin, end);
            }

            Node<N, E> *n = new Node<N, E>(end);

            Edge<N, E> e(n,val);
            nodes[i]->edges.push_back(e);

            return *this;
        }
    }

    throw NodeDoesNotExist<N>(begin);
}

/**
 * Edge Value
 * @tparam N Node
 * @tparam E Edge
 * @param begin Node where edge begins
 * @param end Node where edge ends
 * @return Value of the edge
 */
template<class N, class E>
E & Graph<N,E>::edgeValue(const N &begin, const N &end){

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->info == begin) {
            for (int j = 0; j < nodes[i]->edges.size(); j++) {
                if (nodes[i]->edges[j].destination->info == end){
                    return nodes[i]->edges[j].value;
                }
            }
            throw EdgeDoesNotExist<N>(begin, end);
        }
    }
    throw NodeDoesNotExist<N>(begin);
}

/**
 * Remove edge
 * @tparam N Node
 * @tparam E Edge
 * @param begin Node where edge begins
 * @param end Node where edge ends
 * @return Reference to the graph modified
 */
template<class N, class E>
Graph<N,E> & Graph<N,E>::removeEdge(const N &begin, const N &end){

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->info == begin) {
            for (int j = 0; j < nodes[i]->edges.size(); j++) {
                if (nodes[i]->edges[j].destination->info == end){
                    nodes[i]->edges.erase(nodes[i]->edges.begin() + j);

                    return *this;
                }
            }
            throw EdgeDoesNotExist<N>(begin, end);
        }
    }

    throw NodeDoesNotExist<N>(begin);
}

/**
 * Print nodes and edges of the graph
 * @tparam N Node
 * @tparam E Edge
 * @param os Ostream with information of nodes and edges
 */
template<class N, class E>
void Graph<N,E>::print(std::ostream &os) const{

    for (int i = 0; i < nodes.size(); i++) {
        os << "( " << nodes[i]->info;
        for (int j = 0; j < nodes[i]->edges.size(); j++) {
            os << "[ " << nodes[i]->edges[j].destination->info << " " << nodes[i]->edges[j].value << "] ";
        }
        os << ") ";
    }
}

/**
 * Operator <<
 * @tparam N Node
 * @tparam E Edge
 * @param os Ostream with information of nodes and edges
 * @param g Graph
 * @return Reference to ostream with information of nodes and edges
 */
template<class N, class E>
std::ostream & operator<<(std::ostream &os, const Graph<N,E> &g){
    g.print(os);
    return os;
}