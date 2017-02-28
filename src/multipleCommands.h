#ifndef _MULTIPLECOMMANDS_H_
#define _MULTIPLECOMMANDS_H_
#include "Command.h"

class multipleCommands : public Command {
    
    public:
    Command* left;
    Command* right;
    virtual int execute()=0;
    virtual void remove()=0;
    
};

class And : public multipleCommands {
    public: 
    And(Command *left, Command *right);
    int execute ();
    void remove();
};

class Or : public multipleCommands {
    public:
    Or(Command *left, Command *right);
    int execute ();
    void remove();
    
    
};

class Semicolon : public multipleCommands {
    public:
    Semicolon(Command *left, Command *right);
    int execute ();
    void remove();
};


#endif