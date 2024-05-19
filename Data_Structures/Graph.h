// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "../src/h/utils.h"
#include "../Data_Structures/MutablePriorityQueue.h"

template <class T>
class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
public:
    Vertex(T in);
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue

    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    std::vector<Edge<T> *> getMstAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge<T> *getPath() const;
    double getLat();
    double getLon();
    struct VertexHash {
        int operator()(int vertex) const {
            int v = 0;
            while (vertex > 0){
                v = (v * 53) + vertex % 10;
                vertex /= 10;
            }
            return v;
        }
        bool operator()(const int& vertex1,const int& vertex2) const{
            return vertex1==vertex2;
        }
    };
    std::vector<Edge<T> *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge<T> *path);
    void setLat(double lat);
    void setLon(double lon);
    Edge<T> * addEdge(Vertex<T> *dest, double w);
    Edge<T>* addMstEdge(Vertex *d, double distance);
    bool removeEdge(T in);
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;
protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges
    std::vector<Edge<T> *> Mstadj;
    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge<T> *path = nullptr;
    double lon;
    double lat;
    std::vector<Edge<T> *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge<T> *edge);
};

/********************** Edge  ****************************/

template <class T>
class Edge {
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, double w);

    Vertex<T> * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex<T> * getOrig() const;
    Edge<T> *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge<T> *reverse);
    void setFlow(double flow);
protected:
    Vertex<T> * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;

    double flow; // for flow-related problems
};

/********************** Graph  ****************************/

template <class T>
class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex<T> *findVertex(const T &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const T &in);
    bool removeVertex(const T &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const T &sourc, const T &dest, double w);
    bool removeEdge(const T &source, const T &dest);
    bool addBidirectionalEdge(const T &sourc, const T &dest, double w);
    void updateMst(Vertex<T>* v1,Vertex<T>* v2);

    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    std:: vector<T> dfs() const;
    std:: vector<T> dfs(const T & source) const;
    void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
    std::vector<T> bfs(const T & source) const;
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    bool isDAG() const;
    bool dfsIsDAG(Vertex<T> *v) const;
    std::vector<T> topsort() const;
    void tsp_backtracking(std::vector<int>& path,std::vector<int>& soltuion,double& solution_cost,double current_cost);
    double triangularApproximation(std::queue<Vertex<T>*> &path);
    void nearestNeighborTSP(std::vector<Vertex<T> *> &path, double &distancia);
    void prim();
    void preorderTraversal(Vertex<T> *v, std::queue<Vertex<T> *> &path);
    protected:

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const T &in) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


/************************* Vertex  **************************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T> * Vertex<T>::addEdge(Vertex<T> *d, double w) {
    auto newEdge = new Edge<T>(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}
template <class T>
Edge<T> * Vertex<T>::addMstEdge(Vertex<T> *d, double distance) {
    auto newEdge = new Edge<T>(this, d, distance);
    Mstadj.push_back(newEdge);
    return newEdge;
}
/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdge(T in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        Vertex<T> *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
template <class T>
void Vertex<T>::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}
template <class T>
double Vertex<T>::getLat() {
    return this->lat;
}
template <class T>
double Vertex<T>::getLon() {
    return this->lon;
}
template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
}
template <class T>
std::vector<Edge<T>*> Vertex<T>::getMstAdj() const {
    return this->Mstadj;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return this->visited;
}

template <class T>
bool Vertex<T>::isProcessing() const {
    return this->processing;
}

template <class T>
unsigned int Vertex<T>::getIndegree() const {
    return this->indegree;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Edge<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

template <class T>
void Vertex<T>::setInfo(T in) {
    this->info = in;
}
template <class T>
void Vertex<T>::setLat(double lat) {
    this->lat = lat;
}
template <class T>
void Vertex<T>::setLon(double lon) {
    this->lon = lon;
}
template <class T>
void Vertex<T>::setVisited(bool visited) {
    this->visited = visited;
}

template <class T>
void Vertex<T>::setProcesssing(bool processing) {
    this->processing = processing;
}

template <class T>
void Vertex<T>::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

template <class T>
void Vertex<T>::setDist(double dist) {
    this->dist = dist;
}

template <class T>
void Vertex<T>::setPath(Edge<T> *path) {
    this->path = path;
}

template <class T>
void Vertex<T>::deleteEdge(Edge<T> *edge) {
    Vertex<T> *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double w): orig(orig), dest(dest), weight(w) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return this->dest;
}

template <class T>
double Edge<T>::getWeight() const {
    return this->weight;
}

template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return this->orig;
}

template <class T>
Edge<T> *Edge<T>::getReverse() const {
    return this->reverse;
}

template <class T>
bool Edge<T>::isSelected() const {
    return this->selected;
}

template <class T>
double Edge<T>::getFlow() const {
    return flow;
}

template <class T>
void Edge<T>::setSelected(bool selected) {
    this->selected = selected;
}

template <class T>
void Edge<T>::setReverse(Edge<T> *reverse) {
    this->reverse = reverse;
}
template <class T>
void Edge<T>::setFlow(double flow) {
    this->flow = flow;
}

/********************** Graph  ****************************/

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/****************** DFS ********************/

/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 */
template <class T>
std::vector<T> Graph<T>::dfs() const {
    std::vector<T> res;
    for (auto v : vertexSet)
        v->setVisited(false);
    for (auto v : vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

/*
 * Performs a depth-first search (dfs) in a graph (this) from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */
template <class T>
std::vector<T> Graph<T>::dfs(const T & source) const {
    std::vector<int> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    // Perform the actual DFS using recursion
    dfsVisit(s, res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> & res) const {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <class T>
std::vector<T> Graph<T>::bfs(const T & source) const {
    std::vector<int> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }

    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }

    // Perform the actual BFS using a queue
    std::queue<Vertex<T> *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for (auto & e : v->getAdj()) {
            auto w = e->getDest();
            if ( ! w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setProcesssing(false);
    }
    for (auto v : vertexSet) {
        if (! v->isVisited()) {
            if ( ! dfsIsDAG(v) ) return false;
        }
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->setVisited(true);
    v->setProcesssing(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (w->isProcessing()) return false;
        if (! w->isVisited()) {
            if (! dfsIsDAG(w)) return false;
        }
    }
    v->setProcesssing(false);
    return true;
}

/****************** toposort ********************/
//=============================================================================
// Exercise 1: Topological Sorting
//=============================================================================
// TODO
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
std::vector<T> Graph<T>::topsort() const {
    std::vector<int> res;

    for (auto v : vertexSet) {
        v->setIndegree(0);
    }
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    std::queue<Vertex<T> *> q;
    for (auto v : vertexSet) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while( !q.empty() ) {
        Vertex<T> * v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if(w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if ( res.size() != vertexSet.size() ) {
        //std::cout << "Impossible topological ordering!" << std::endl;
        res.clear();
        return res;
    }

    return res;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

template <class T>
Graph<T>::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}
/**
 * @brief Solves the Traveling Salesman Problem (TSP) using backtracking.
 *
 * This function recursively computes the TSP solution using backtracking.
 * It finds the shortest path that visits every vertex exactly once and returns
 * to the starting vertex.
 *
 * @param path The current path being constructed in the recursion.
 * @param solution The best solution found by the algorithm.
 * @param solution_cost The cost of the best solution found.
 * @param current_cost The current cost of the path being constructed.
 */
template <class T>
void Graph<T>::tsp_backtracking(std::vector<int>& path, std::vector<int>& solution, double& solution_cost, double current_cost) {
    if (path.size() == vertexSet.size()) {
        for (auto e : findVertex(path.back())->getAdj()) {
            if (e->getDest()->getInfo() == path.front()) {
                current_cost += e->getWeight();
                if (current_cost < solution_cost) {
                    solution_cost = current_cost;
                    solution = path;
                }
                break;
            }
        }
        return;
    }
    else {
        for (auto e : findVertex(path.back())->getAdj()) {
            auto v = e->getDest();
            if (!v->isVisited()) {
                current_cost += e->getWeight();
                path.push_back(v->getInfo());
                v->setVisited(true);
                tsp_backtracking(path, solution, solution_cost, current_cost);
                path.pop_back();
                v->setVisited(false);
                current_cost -= e->getWeight();
            }
        }
    }
}
/**
 * @brief Updates the Minimum Spanning Tree (MST) edges between two vertices.
 *
 * This function updates the MST edges between two vertices by adding new edges
 * and setting reverse edges for bidirectional connectivity.
 *
 * @param v1 The orig vertex.
 * @param v2 The dest vertex.
 */
template <class T>
void Graph<T>::updateMst(Vertex<T>* v1,Vertex<T>* v2){
    auto e1 = v1->addMstEdge(v2, v1->getPath()->getWeight());
    auto e2 = v2->addMstEdge(v1, v1->getPath()->getWeight());
    e1->setReverse(e2);
    e2->setReverse(e1);
}
/**
 * @brief Executes Prim's algorithm to compute the Minimum Spanning Tree (MST) of the graph.
 *
 * This function computes the MST using Prim's algorithm. It starts from the first vertice,
 * updates the MST edges iteratively, and maintains a priority queue to efficiently find the
 * next vertex to add to the MST.
 */
template <class T>
void Graph<T>::prim() {
    if (getVertexSet().empty()) {
        return ;
    }
    for (auto v : getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex<T>* s = getVertexSet().front();
    s->setDist(0);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        if (v->getPath() != nullptr) {
            updateMst(v,v->getPath()->getOrig());
        }
        for (auto &e : v->getAdj()) {
            Vertex<T>* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if (e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == INF) {
                        q.insert(w);
                    } else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
}
/**
 * @brief Performs a preorder traversal starting from a given vertex in the Minimum Spanning Tree (MST).
 *
 * This function performs a recursive preorder traversal starting from the given vertex
 * in the MST of the graph. It visits each vertex in the tree exactly once and adds them
 * to the provided queue in the order they are visited.
 *
 * @param v The starting vertex for the preorder traversal.
 * @param path The queue to store the vertices in the order of traversal.
 */
template <class T>
void Graph<T>::preorderTraversal(Vertex<T> *v, std::queue<Vertex<T> *> &path) {
    if (v == nullptr) return;
    path.push(v);
    v->setVisited(true);
    for (auto &e : v->getMstAdj()) {
        Vertex<T>* w = e->getDest();
        if (!w->isVisited()) {
            preorderTraversal(w, path);
        }
    }
}
/**
 * @brief Computes an approximation of the Traveling Salesman Problem (TSP) using the Triangular Approximation Method.
 *
 * This function computes an approximation of the TSP using the Triangular Approximation Method:
 * 1. Constructs a Minimum Spanning Tree (MST) using Prim's algorithm.
 * 2. Performs a preorder traversal starting from the root of the MST.
 * 3. Computes the total distance of the path formed by the preorder traversal in the TSP.
 *
 * @param path A queue to store the vertices in the order of traversal.
 * @return The total distance of the TSP approximation using the Triangular Approximation Method.
 */
template <class T>
double Graph<T>::triangularApproximation(std::queue<Vertex<T>*> &path) {
    double dist = 0.0;
    if (getVertexSet().empty()) {
        return dist;
    }
    prim();
    for (auto& vertex : getVertexSet()) {
        vertex->setVisited(false);
    }
    auto v = findVertex(0);
    preorderTraversal(v,path);
    path.push(v);
    std::queue<Vertex<T>*> temp_path = path;
    Vertex<T>* prev = temp_path.front() ;
    Vertex<T>* current = temp_path.front();
    while (!temp_path.empty()) {
        dist += Haversine(prev->getLat(),prev->getLon(), current->getLat(),current->getLon());
        prev = current;
        temp_path.pop();
        current = temp_path.front();
    }
    return dist;

}
/**
 * @brief Computes the Traveling Salesman Problem (TSP) solution using the Nearest Neighbor heuristic.
 *
 * This function computes an approximate solution to the TSP using the Nearest Neighbor heuristic:
 * 1. Starts from the first vextex.
 * 2. Iteratively selects the nearest unvisited vertex until all vertices are visited.
 * 3. Returns to the starting vertex to complete the tour.
 *
 * @param path Vector to store the vertices in the order of the TSP path.
 * @param distancia Reference to a variable to store the total distance of the TSP path.
 */
template <class T>
void Graph<T>::nearestNeighborTSP(std::vector<Vertex<T> *> &path, double &distancia) {
    distancia = 0;
    if (getVertexSet().empty()) return;
    Vertex<T>* currentVertex = findVertex(0);
    currentVertex->setVisited(true);
    while (true) {
        path.push_back(currentVertex);
        double minDist = INF;
        Vertex<T>* nextVertex = nullptr;
        for (auto v : getVertexSet()) {
            Vertex<T>* neighbor = v;
            if (!neighbor->isVisited()) {
                double current_dist = Haversine(currentVertex->getLat(),currentVertex->getLon(),neighbor->getLat(),neighbor->getLon());
                if (current_dist < minDist) {
                    minDist = current_dist;
                    nextVertex = neighbor;
                }
            }
        }

        if (nextVertex == nullptr) break;
        nextVertex->setVisited(true);
        distancia += minDist;
        currentVertex = nextVertex;
    }
    for (auto e : currentVertex->getAdj()) {
        if (e->getDest() == getVertexSet().front()) {
            distancia += Haversine(e->getOrig()->getLat(),e->getOrig()->getLon(),e->getDest()->getLat(),e->getDest()->getLon());
            break;
        }
    }

    path.push_back(getVertexSet().front());
}






#endif /* DA_TP_CLASSES_GRAPH */