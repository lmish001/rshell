#ifndef _PARSE_H_
#define _PARSE_H_
#include "Command.h"
#include <vector>
#include <string>


class Parse {
    
    private:
    std::vector<std::string> v;
    Command* root;

    public:
    Parse(std::vector<std::string> v);
    void createTree();
    int returnVal;
    int get_returnVal();
    int run();
    
};

#endif