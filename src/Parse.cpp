#include "Parse.h"
#include "Command.h"
#include "singleCommand.h"
#include "multipleCommands.h"
#include <sstream>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;



Parse::Parse(vector<string> v){
    //takes in a a vector of string that contains commands and connectors
    this->v=v;
    returnVal = 0;
    top = NULL;
}


Command* Parse::pop() {
    
        Command *c = top->c;
        top = top->next;
        return c;
        
}

void Parse::push(Command *c) {
    
    if(top==NULL){
        top = new Stack (c);
    }
    
    else {
        Stack *root = new Stack (c);
        root->next = top;
        top = root;
    }
    
}


//creates tree that will later be traversed in=order to be executed. 
void Parse::createTree(){
    Command *left, *right;
    for(unsigned i=0; i<v.size(); i++) {
        if (v.at(i)=="&&" || v.at(i)=="||" || v.at(i)==";" || v.at(i)=="<" || v.at(i)==">>" || v.at(i)==">" || v.at(i)=="|") {
        	right = top->c;
            top = top->next;
            left = top->c;
            top = top->next;
        	if (v.at(i)=="&&"){
        		Command * root = new And(left, right);
                push(root);
        	}
        	if (v.at(i)=="||"){
        		Command * root = new Or(left, right);
        		push (root);
        	}
            if (v.at(i)==";") {
        		Command * root = new Semicolon(left, right);
                push(root);
        	}
    		if (v.at(i) == "<"){
    		    Command * root = new Input_Redir(left, right);
    		    push(root);
    		}
    		if (v.at(i) == ">>"){
    		    Command * root = new Output_Redir2(left, right);
    		    push(root);
    		}
    		if (v.at(i) == ">"){
    		    Command * root = new Output_Redir1(left, right);
    		    push(root);
    		}
    		if (v.at(i) == "|"){
    		    Command * root = new Pipe(left, right);
    		    push(root);
    		}
    	}
    	
        else {
    	    Command *node = new singleCommand (v.at(i));
    	    push (node);
    	}
    }
    this->root = top->c;

}

//runs the command. 
int Parse::run (){
    
    if(returnVal!=-1){
        returnVal = root->execute();
        root=NULL;
        return returnVal;
    }
    return returnVal;
    
}

//returns the return value from the last executed command. Used to see if the exit command was executed.
int Parse::get_returnVal(){
    return returnVal;
}