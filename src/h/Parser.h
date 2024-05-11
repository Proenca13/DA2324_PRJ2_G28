#ifndef DA2324_PRJ2_G28_PARSER_H
#define DA2324_PRJ2_G28_PARSER_H

#include <string>
#include "../../Data_Structures/Graph.h"
class Parser {
public:
    Parser();
    Graph<int> loadToyGraph(const std::string& filePath);
    Graph<int> loadRealWordGraph(const std::string& filePath);
};


#endif //DA2324_PRJ2_G28_PARSER_H
