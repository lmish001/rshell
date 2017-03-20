#ifndef _COMMAND_H_
#define _COMMAND_H_
#include <string>


class Command {

    public:
    virtual int execute() = 0;
    virtual void remove()=0;
    virtual int saveBuffer(int &) = 0;
    
    virtual int vectorize() = 0;
};

#endif