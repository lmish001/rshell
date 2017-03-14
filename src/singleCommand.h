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
    int redirFlag;
    std::string output;
    
    public:
    singleCommand(std::string command);
    int testCommand(std::vector<std::string> v);
    int execute();
    void remove();
    void setRedirFlag(int f);
    void setOutput(std::string output);
    std::string getInput();
    
    
};


#endif