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
}


void Parse::createTree(){
    
    //If the vector has only 1 position, create and directly execute a single command.
    if(this->v.size()==1){
        string input = v.at(0);
        //Create a new singleCommand object
        Command* node = new singleCommand(v.at(0));
        this->root = node;
        
        //execute the command
        /*returnVal = node->execute();
        node=NULL;
        return returnVal;*/
        
    }
    
    //If the input was multiple commands, create a tree to recursively call the execute functions. The left nodes are alwas leaf nodes and are always a single command.
    //The right nodes can be a connector or a command. The root node is a connector. The return value is used to keep track of when the "exit" command was called.
    else {
        Command *root, *left, *right;
        string input;
        int numConnectors = (v.size()-1)/2;
        input = v.at(numConnectors*2-2);

        left = new singleCommand(input);
        input = v.at(numConnectors*2);

        
        right = new singleCommand(input);
        
        
        
        if (v.at(numConnectors*2-1)=="&&"){
            root = new And(left, right);
        }
        
        if (v.at(numConnectors*2-1)=="||"){
            root = new Or(left, right);
        }
        
        if (v.at(numConnectors*2-1)==";"){
            root = new Semicolon(left, right);
        }
        
        if(numConnectors>1){
            for (int i = v.size()-5; i>=0; i=i-2){
                
            input = v.at(i);
            left = new singleCommand(input);
            right = root;
                
                if (v.at(i+1)=="&&"){
                    root = new And(left, right);
                }
                
                if (v.at(i+1)=="||"){
                    root = new Or(left, right);
                }
                
                if (v.at(i+1)==";"){
                    root = new Semicolon(left, right);
                }
            }
        }
        
        this->root = root;
        
       /*returnVal = root->execute();
       
       root->remove();
       return returnVal;*/
     
    }
    
    
    
}

int Parse::run (){
    
    returnVal = root->execute();
    root=NULL;
    return returnVal;
    
}

int Parse::get_returnVal(){
    return returnVal;
}