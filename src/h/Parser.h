#ifndef DA2324_PRJ2_G28_PARSER_H
#define DA2324_PRJ2_G28_PARSER_H

#include <string>
#include "../../Data_Structures/Graph.h"
using namespace std;
class Parser {
public:
    Parser();
    Graph<int> loadToyGraph(string& filePath);
    Graph<int> loadRealWordGraph(string& edgesPath,string& nodesPath);


    Graph<int> loadExtraGraph(string &edgesPath, string &nodesPath);
};


#endif //DA2324_PRJ2_G28_PARSER_H
