#ifndef _PARSE_H_
#define _PARSE_H_
#include "Command.h"
#include <vector>
#include <string>


class Parse {
    
    private:
    std::vector<std::string> v;
    int returnVal;

    public:
    Parse(std::vector<std::string> v);
    int createTree();
    int get_returnVal();
    
    
};

#endif