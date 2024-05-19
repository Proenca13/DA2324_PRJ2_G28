#ifndef DA2324_PRJ2_G28_PARSER_H
#define DA2324_PRJ2_G28_PARSER_H

#include <string>
#include "../../Data_Structures/Graph.h"
using namespace std;
class Parser {
public:
    /**
     * @brief Default constructor for Parser.
     */
    Parser();
    /**
     * @brief Loads a toy graph from a file.
     *
     * This function reads a toy graph from the specified file path. The file should contain
     * edges in the format: origem,destino,distancia. Each vertex is added to the graph
     * if it does not already exist, and edges are added bidirectionally.
     *
     * @param filePath Path to the file containing the toy graph.
     * @return Graph<int> The loaded toy graph.
     */
    Graph<int> loadToyGraph(string& filePath);
    /**
     * @brief Loads an fully connected graph from two files containing edges and nodes.
     *
     * This function reads edges and nodes from the specified file paths. It creates vertices
     * and adds them to the graph. It then creates edges between the vertices based on the
     * provided data. The files should be in the following format:
     * - edges file: origem,destino,distancia
     * - nodes file: id,lon,lat
     *
     * @param edgesPath Path to the file containing the edges.
     * @param nodesPath Path to the file containing the nodes.
     * @return Graph<int> The loaded fully connected graph.
     */
    Graph<int> loadExtraGraph(string &edgesPath, string &nodesPath);
    /**
     * @brief Loads a real world graph from two files containing edges and nodes.
     *
     * This function reads edges and nodes from the specified file paths. It creates vertices
     * and adds them to the graph with their respective longitude and latitude. It then creates
         * edges between the vertices based on the provided data. The files should be in the following format:
     * - nodes file: id,lon,lat
     * - edges file: origem,destino,distancia
     *
     * @param edgesPath Path to the file containing the edges.
     * @param nodesPath Path to the file containing the nodes.
     * @return Graph<int> The loaded real world graph.
     */
    Graph<int> loadRealWordGraph(string& edgesPath,string& nodesPath);



};


#endif //DA2324_PRJ2_G28_PARSER_H
