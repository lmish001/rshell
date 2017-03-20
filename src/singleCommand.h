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
    int outFiledes;
    int inFiledes;
    
    public:
    singleCommand(std::string command);
    int testCommand(std::vector<std::string> v);
    int execute();
    void remove();
    
    void setInFiledes (int filedes);
    void setOutFiledes (int filedes);
    
    std::string getInput();
    int saveBuffer(int &);

    int vectorize();
};


#endif