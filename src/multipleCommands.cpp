#include <iostream>
#include "multipleCommands.h"
#include "singleCommand.h"
#include "Command.h"
#include <typeinfo>

And::And(Command *left, Command *right){
    this->left=left;
    this->right=right;
}

int And::execute(){
    
    int returnVal = left->execute();
    //Checks if the previous (left) command executed correctly
    if(returnVal==0) {
      return right->execute();
    }

    return returnVal;
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
    //Checks if the previous (left) command executed incorrectly
    if(returnVal==1) {
      return right->execute();
    }
    
    return returnVal;
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
    //Checks if the previous (left) command wasn't "exit"
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

Redir1::Redir (Command *left, Command *right){
    this->left=left;
    this->right=right;
}

int Redir1::execute(){
    left->setRedirFlag(1);
    left->setOutput(right->getInput());
    int returnVal = left ->execute();
    left ->setRedirFlag(0);
    return returnVal;
}