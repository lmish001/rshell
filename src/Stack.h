#ifndef _STACK_H_
#define _STACK_H_
#include "Command.h"

class Stack {
    
    public:
    Command *c;
    Stack *next;
    Stack (Command *c){
        this->c = c;
        next = NULL;
    }
    
};

#endif