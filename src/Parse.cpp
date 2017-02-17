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
    this->v=v;
    returnVal=0;
}


int Parse::createTree(){
    
    if(this->v.size()==1){
        string input = v.at(0);
        //Create a new singleCommand object
        Command* node = new singleCommand(v.at(0));
        
        //execute the command
        returnVal = node->execute();
        node=NULL;
        return returnVal;
        
    }
    else{
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
        
       returnVal = root->execute();
       
       root->remove();
       return returnVal;
     
    }
    
    
    
}

int Parse::get_returnVal(){
    return returnVal;
}