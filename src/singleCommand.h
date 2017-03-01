#ifndef _SINGLECOMMAND_H_
#define _SINGLECOMMAND_H_
#include "Command.h"
#include <vector> 

class singleCommand : public Command {
    
    protected:
    char **args;
    std::string input;
    pid_t pid, wpid;
    int status;
    
    public:
    singleCommand(std::string command);
    int testCommand(std::vector<std::string> v);
    int execute();
    void remove();
    
    
};


#endif