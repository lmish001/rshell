#include "Command.h"
#include "singleCommand.h"
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>
#include <errno.h>
 #include <stdlib.h>
using namespace std;

singleCommand::singleCommand(string input){
    
    this->input = input;

}



int singleCommand::execute() {


    vector<string>temp;
    vector<char*>argsToChar;
    string buff;
    stringstream ss(input);
    while(ss >> buff) temp.push_back (buff);
        
    if (temp.at(0)=="exit"){
        return 2;
    }
        
    else{
    
        for (unsigned i=0; i<temp.size(); ++i) {
            std::string::size_type size = (temp.at(i)).size();
            char *buffer = new char[size + 1];
            memcpy(buffer, temp.at(i).c_str(), size + 1);
            argsToChar.push_back(buffer);    
        }
       
        args = &argsToChar[0];
        int execpipe[2];
        pipe(execpipe);
        fcntl(execpipe[1], F_SETFD, fcntl(execpipe[1], F_GETFD) | FD_CLOEXEC);
        pid = fork();
     
        if(pid<0){
            perror("Fork failed");
             return -1;
          
        }
        
        if(pid==0){ //child process
        
           close(execpipe[0]);
          
          
           
           execvp(args[0], args);
           perror("Error");
           write(execpipe[1], &errno, sizeof(errno));
          exit(0);
             
          
           
        }
        
        if(pid>0) {
           
            if(wait(&status)==-1){
                perror("Wait error");
            }
            
            close(execpipe[1]);
            int childErrno;
            if(read(execpipe[0], &childErrno, sizeof(childErrno)) == sizeof(childErrno))
            {
                return -1;
        
            }
            
            else
            {
                return 1;
            }
        }    
        

    }
return 0;
}


void singleCommand::remove(){
    //does nothing
}