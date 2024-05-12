#include "../h/Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
Parser::Parser() {};
Graph<int> Parser::loadToyGraph(const std::string &filePath) {
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