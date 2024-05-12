#include "../h/Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
        graph.addVertex(id);
        graph.findVertex(id)->setLat(lat);
        graph.findVertex(id)->setLon(lon);
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