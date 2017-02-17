#include <iostream>
#include "multipleCommands.h"
#include "Command.h"

And::And(Command *left, Command *right){
    this->left=left;
    this->right=right;
}


int And::execute(){
    
    int returnVal = left->execute();
    //checks if the previous (left) command executed correctly
    if(returnVal==1){
      return right->execute();
    }
    else{
        return returnVal;
    }
   
}


void And::remove(){
    this->left = NULL;
    this->right = NULL;
}


Or::Or(Command *left, Command *right){
    this->left=left;
    this->right=right;    
}


int Or::execute(){
    
    int returnVal = left->execute();
    //checks if the previous (left) command executed incorrectly
    if(returnVal==-1){
      return right->execute();
    }
    else{
        return returnVal;
    }
}


void Or::remove(){
    this->left = NULL;
    this->right = NULL;
}


Semicolon::Semicolon(Command *left, Command *right){
    
    this->left=left;
    this->right=right;
}


int Semicolon::execute(){
    
    int returnVal = left->execute();
    //Executes all the commands. If the command was "exit", does not execute any further.
    if(returnVal!=2){
      return right->execute();
    }
    else{
        return returnVal;
    }
}


void Semicolon::remove(){
    this->left = NULL;
    this->right = NULL;
}