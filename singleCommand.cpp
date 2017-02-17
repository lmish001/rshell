#include "Command.h"
#include "singleCommand.h"
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <sys/wait.h>
#include <cstring>
#include <cstdint>
using namespace std;

singleCommand::singleCommand(string input){
    
    this->input = input;
}

int singleCommand::execute( ) {
    
    vector<string>temp;
    string buff;
    stringstream ss(input);
    while(ss >> buff) temp.push_back (buff);
    
    
    
    if(temp.at(0)=="exit"){
        return 2;
    }
    
    else{
    
    vector<char*>argsToChar;
    
    for (unsigned i=0; i<temp.size(); ++i){
            std::string::size_type size = (temp.at(i)).size();
            char *buffer = new char[size + 1];
            memcpy(buffer, temp.at(i).c_str(), size + 1);
            argsToChar.push_back(buffer);    
    }
   
    
    args = &argsToChar[0];
    
    pid_t pid, wpid;
    int status;
    pid = fork();
    if(pid<0){
        return -1;
        perror("Error");
    }
    else if(pid==0){ //child process
       
        
        
        if (execvp(args[0], args) == -1) {
            return -1;
        perror("Error");
    }
    }
    else{
        do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return 1;
    }
    
}

void singleCommand::remove(){
    //doesnt do anything
}