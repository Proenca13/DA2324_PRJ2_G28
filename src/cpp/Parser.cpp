#include "../h/Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;
Parser::Parser() {};
Graph<int> Parser::loadToyGraph(string &filePath) {
    ifstream in;
    in.open(filePath);
    string line;
    Graph<int> graph;
    if (!in.is_open()){
        cout << "File not found!"<<'\n';
    }
    getline(in, line);
    while (getline(in, line)) {
        stringstream ss(line);
        int origem,destino;
        double distancia;
        ss >> origem;
        ss.ignore(1);
        ss >> destino;
        ss.ignore(1);
        ss >> distancia;
        ss.ignore(1);
        if(graph.findVertex(origem)== nullptr){
            graph.addVertex(origem);
        }
        if(graph.findVertex(destino)== nullptr){
            graph.addVertex(destino);
        }
        graph.addBidirectionalEdge(origem,destino,distancia);
    }
    return graph;
}
Graph<int> Parser::loadRealWordGraph(string& edgesPath,string& nodesPath){
    ifstream nodes,edges;
    std::unordered_map<int ,Vertex<int>*,Vertex<int>::VertexHash> vertexhash;
    nodes.open(nodesPath);
    edges.open(edgesPath);
    Graph<int> graph;
    string line;
    if (!nodes.is_open() or !edges.is_open()){
        cout << "File not found!"<<'\n';
    }
    getline(nodes, line);
    getline(edges,line);
    while (getline(nodes, line)) {
        stringstream ss(line);
        int id;
        double lon,lat;
        ss >> id;
        ss.ignore(1);
        ss >> lon;
        ss.ignore(1);
        ss >> lat;
        ss.ignore(1);
        Vertex<int>* ver = new Vertex(id);
        ver->setLat(lat);
        ver->setLon(lon);
        graph.vertexSet.push_back(ver);
        vertexhash[id] = ver;
    }
    while (getline(edges, line)) {
        stringstream ss(line);
        int origem,destino;
        double distancia;
        ss >> origem;
        ss.ignore(1);
        ss >> destino;
        ss.ignore(1);
        ss >> distancia;
        ss.ignore(1);
        if(vertexhash[origem]== nullptr){
            graph.addVertex(origem);
        }
        if(vertexhash[destino] == nullptr){
            graph.addVertex(destino);
        }
        vertexhash[origem]->addEdge(vertexhash[destino],distancia);
        vertexhash[origem]->addEdge(vertexhash[destino],distancia);
    }
    return graph;
}