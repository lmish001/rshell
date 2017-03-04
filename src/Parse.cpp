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

// int Parse::createTree(){
//     if (!properSyntax()){
//         return -1;
//     }
//     //If the vector has only 1 position, create and directly execute a single command.
//     if(this->v.size()==1){
//         string input = v.top();
    
//         //Create a new singleCommand object
//         Command* node = new singleCommand(v.top());
        
//         //execute the command
//         returnVal = node->execute(true);
//         node = NULL;
//         //return returnVal;
        
//     }
    
//     //If the input was multiple commands, create a tree to recursively call the execute functions. The left nodes are alwas leaf nodes and are always a single command.
//     //The right nodes can be a connector or a command. The root node is a connector. The return value is used to keep track of when the "exit" command was called.
//     else {
        
//         Command *root, *left, *right;
//         string input;
//         int returnVal;
//         std::stack<Command*> temp;
//         bool first = false;
//         while (v.size() > 0){
//             //std::cout << v.size() << " begin" << std::endl;
//             if (v.top().size() > 2 || !(v.top() == "&&" || v.top() == "||" || v.top() == ";")){
//                 temp.push(new singleCommand(v.top()));
//                 v.pop();
//             }
//             else {
//                 // Need to manually assign left or right as singleCommand or multipleCommand 
//                 if (!first){
//                     right = new singleCommand(temp.top()->getInput());
//                     std::cout << "f_right is: " << temp.top()->getInput() << std::endl;
//                     temp.pop();
//                     left = new singleCommand(temp.top()->getInput());
//                     std::cout << "f_left is: " << temp.top()->getInput() << std::endl;
//                     temp.pop();
//                     first = true;
                    
//                 }
//                 else {
//                     Command *tempR = temp.top();
//                     temp.pop();
//                     Command *tempL = temp.top();
//                     temp.pop();
//                     if (tempR->getInput() == "&&" || tempR->getInput() == "||" || tempR->getInput() == ";"){
//                         std::cout << "complex right" << std::endl;
//                         right = tempR;
//                     }
//                     else {
//                         right = new singleCommand(tempR->getInput());
//                         std::cout << "right is: " << tempR->getInput() << std::endl;
//                     }
//                     if (tempL->getInput() == "&&" || tempL->getInput() == "||" || tempL->getInput() == ";"){
//                         std::cout << "complex left" << std::endl;
//                         left = tempL;
//                     }
//                     else {
//                         left = new singleCommand(tempL->getInput());
//                         std::cout << "left is: " << tempL->getInput() << std::endl;
//                     }
//                 }
                
//                 if (v.top() == "&&"){
//                     root = new And(left, right);
//                     temp.push(root);
//                 } 
//                 else if (v.top() == "||"){
//                     root = new Or(left, right);
//                     temp.push(root);
//                 }
//                 else if (v.top() == ";"){
//                     root = new Semicolon(left, right);
//                     temp.push(root);
//                 }
//                 else {
//                     std::cout << "ERROR IN PARSE" << std::endl;
//                     break;
//                 }
//                 v.pop();
//             }
//         }

//         returnVal = root->execute(true);
       
//         root->remove();

//     }
    
    
    
// }


/*
void Parse::createTree(){
    
    //If the vector has only 1 position, create and directly execute a single command.
    if(this->v.size()==1){
        string input = v.at(0);
        //Create a new singleCommand object
        Command* node = new singleCommand(v.at(0));
        this->root = node;
        
        //execute the command
        returnVal = node->execute();
        node=NULL;
        return returnVal;
        
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
        
      returnVal = root->execute();
       
      root->remove();
      return returnVal;
     
   }
    
    
    
}*/


Command* Parse::pop(){
    
        Command *c = top->c;
        top = top->next;
        return c;
        
}

void Parse::push(Command *c){
    if(top==NULL){
        top = new Stack (c);
    }
    
    else {
        Stack *root = new Stack (c);
        root->next = top;
        top = root;
    }
    
    
}

void Parse::createTree(){
    Command *left, *right;
    
/*    if(v.at(0)=="&&"||v.at(0)=="||"||v.at(0)==";"){
        cout<<"Syntax Error"<<endl;
        returnVal = -1;
        return;
    }
    
    if((v.size()!=1)&&(v.at(1)=="&&"||v.at(1)=="||"||v.at(1)==";")){
        cout<<"Syntax Error"<<endl;
        returnVal = -1;
        return;
    }
    
    if((v.at(v.size()-1)!="&&"||v.at(v.size()-1)!="||"||v.at(v.size()-1)!=";")&&(v.size()!=1)){
        cout<<"Syntax Error"<<endl;
        returnVal = -1;
        return;
    }*/
    
    for(unsigned i=0; i<v.size(); i++){
        
        if (v.at(i)=="&&"||v.at(i)=="||"||v.at(i)==";"){
    	right = top->c;
    	top = top->next;
    	left = top->c;
    	top = top->next;
    	
    		if (v.at(i)=="&&"){
    			Command * root = new And (left, right);
                push(root);
    		}
    
    		if (v.at(i)=="||"){
    			Command * root = new Or (left, right);
    			push (root);
    		}
    
    		if (v.at(i)==";"){
    			Command * root = new Semicolon (left, right);
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

int Parse::run (){
    
    if(returnVal!=-1){
    returnVal = root->execute();
    root=NULL;
    return returnVal;
    }
    return returnVal;
    
}

int Parse::get_returnVal(){
    return returnVal;
}