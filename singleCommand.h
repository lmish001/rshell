#ifndef _SINGLECOMMAND_H_
#define _SINGLECOMMAND_H_
#include "Command.h"
#include <vector> 

class singleCommand : public Command {
    protected:
    char **args;
    std::string input;
    
    public:
    singleCommand(std::string command);
    int execute();
    void remove();
    
};


#endif