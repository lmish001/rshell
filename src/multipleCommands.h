#ifndef _MULTIPLECOMMANDS_H_
#define _MULTIPLECOMMANDS_H_
#include "Command.h"
#include <vector>
#include <string>
#include <fstream>

struct command{
    const char **argv;

};

class multipleCommands : public Command {
    
    public:
    Command* left;
    Command* right;
    virtual int execute()=0;
    virtual void remove()=0;
    void fileStarter(std::ofstream &);
    void fileFinisher(std::ofstream &);
    
    protected:
    static std::vector<std::string> redir_v;
    static std::vector<std::string> vector_pipe;
    
    int containsElem(std::string elem);
    int getInFiledes();
    int getOutFiledes();
    int vectorize();

    virtual int saveBuffer(int &pipeBuffer) = 0;
    
};

class And : public multipleCommands {
    public: 
    And(Command *left, Command *right);
    int execute();
    void remove();
   
    int saveBuffer(int &pipeBuffer);
};

class Or : public multipleCommands {
    public:
    Or(Command *left, Command *right);
    int execute();
    void remove();
   
    int saveBuffer(int &pipeBuffer);
    
};

class Semicolon : public multipleCommands {
    public:
    Semicolon(Command *left, Command *right);
    int execute();
    void remove();
   
    int saveBuffer(int &pipeBuffer);
};

class Input_Redir : public multipleCommands {
    public:
    Input_Redir(Command *left, Command *right);
    int execute();
    void remove();
    int saveBuffer(int &pipeBuffer);
   
};

class Output_Redir1 : public multipleCommands {
    // Redirect stdout to a file.
    // Creates the file if not present, otherwise overwrites it.
    
    public:
    Output_Redir1(Command *left, Command *right);
    int execute();
    void remove();
    int saveBuffer(int &pipeBuffer);
   
};

class Output_Redir2 : public multipleCommands {
    // Redirect stdout to a file.
    // Creates the file if not present, otherwise appends to it.
    
    public:
    Output_Redir2(Command *left, Command *right);
    int execute();
    void remove();
    int saveBuffer(int &pipeBuffer);
   
};

class Pipe : public multipleCommands {
    public:
    Pipe(Command *left, Command *right);
    int execute();
    void remove();
    int saveBuffer(int &pipeBuffer);
   
};


#endif