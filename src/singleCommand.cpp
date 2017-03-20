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
#include <fstream>
#include <errno.h>
#include <stdlib.h>
#include <iterator>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

singleCommand::singleCommand(string input){
    this->input = input;
    inFiledes = -1;
    outFiledes  = -1;
}

int singleCommand::vectorize(){
  return 0; // Done
}

void singleCommand::setInFiledes(int filedes){
  this->inFiledes = filedes;
}
void singleCommand::setOutFiledes(int filedes){
  this->outFiledes = filedes;
}

string singleCommand::getInput(){
  return this->input;
}


//executes the test command
//change to bool
int singleCommand::testCommand(vector<string> v){
struct stat info;
const char * c;

if(v.size()==1) {
  cout<<"(False)"<<endl;
  return 1;
}
 
  if(v.size()>3) {
   cout<<"bash: syntax error with test"<<endl;
        return 1;
 }
    
 if (v.at(1)=="-f") {
        
    if(v.size()==2) {
      cout<<"(True)"<<endl;
      return 0;
    }
        
    else {
      c = v.at(2).c_str();
            
        if( stat(c, &info ) != 0 ) {
          cout<<"(False)"<<endl;
          return 1;
        }
            
        else if( info.st_mode & S_IFREG ) {
          cout<<"(True)"<<endl;
          return 0;
        }   
            
        else {
          cout<<"(False)"<<endl;
          return 1;
        }
    }
 }
    
 if(v.at(1)=="-d") {
        
    if(v.size()==2) {
      cout<<"(True)"<<endl;
      return 0;
    }
        
    else {
      c = v.at(2).c_str();
        
        if( stat(c, &info ) != 0 ) {
          cout<<"(False)"<<endl;
          return 1;
        }
            
        else if( info.st_mode & S_IFDIR ) {
          cout<<"(True)"<<endl;
          return 0;
        }   
            
        else {
          cout<<"(False)"<<endl;
          return 1;
        }
    } 
  }
    
 else {
        
    if(v.at(1) =="-e") {
        
        if(v.size()==2) {
          cout<<"(True)"<<endl;
          return 0;
        }
        
          c = v.at(2).c_str();
    }
        
    else {
      c = v.at(1).c_str();  
    }
        
    if( stat(c, &info ) != 0 ) {
      cout<<"(False)"<<endl;
      return 1;
    }
        
    else if( info.st_mode & S_IFMT ) {
      cout<<"(True)"<<endl;
      return 0;
    }   
        
    else {
      cout<<"(False)"<<endl;
      return 1;
    }
 }

}



int singleCommand::execute() {

   std::istringstream buf(input);
   std::istream_iterator<string> beg(buf), end;
   vector<string> tokens(beg, end);
    
    //checks if the command is a test command
    if(tokens.at(0)=="test"){
        return testCommand (tokens);
        
    }
    
    //checks if the command is an exit command
    if(tokens.at(0)=="exit"){
        return 2;
        
    }

    //to execute the command, the string needs to be changed to a char**
    vector<string>temp;
    vector<char*>argsToChar;
    string buff;
    stringstream ss(input);
    while(ss >> buff) temp.push_back (buff);

    for (unsigned i=0; i<temp.size(); ++i) {
      std::string::size_type size = (temp.at(i)).size();
      char *buffer = new char[size + 1];
      strcpy(buffer, temp.at(i).c_str());
      argsToChar.push_back(buffer);    
    }
        
    argsToChar.push_back(NULL); 
    args = &argsToChar[0];
    
    int execpipe[2];
    pipe(execpipe);
    fcntl(execpipe[1], F_SETFD, fcntl(execpipe[1], F_GETFD) | FD_CLOEXEC);
    pid = fork();
     
    if(pid<0) {
      perror("Fork failed");
      return 1;
    }
        
    if(pid==0) { //child process
      close(execpipe[0]);
      if(inFiledes!=-1){
        if (dup2(inFiledes, 0) == -1){
          perror("dup2 error1");
        }
        close(inFiledes); 
      }
        
      if(outFiledes!=-1){
        if (dup2(outFiledes, 1) == -1){
          perror("dup2 error2");
        }
        close(outFiledes);
      }
        
      execvp(args[0], args);
        
      //If execvp fails, it returns and the child writes to one end of the pipe.
      perror("Error");
      write(execpipe[1], &errno, sizeof(errno));
      exit(EXIT_FAILURE);
    }
        
    if(pid>0) {
      
      //The parent waits fot the child process
   //  if(waitpid(pid, &status, WIFEXITED(&status))!=-1){
      if(wait(&status)==-1){
        perror("Wait error");
      }

    close(execpipe[1]);
    int childErrno;
   
    //If the parent can read from the pipe, it means the execvp failed, and the function returns -1
      if(read(execpipe[0], &childErrno, sizeof(childErrno)) == sizeof(childErrno)) {
        this->input.erase (input.begin(), input.end());
        this->args = NULL;
        return 1;
      }
            
      else {
        wait(&status);
        if(WIFEXITED(status))
        {
            if(WEXITSTATUS(status) == 0)
            {
                // Program succeeded
                return 0;
            }
            else
            {
                // Program failed but exited normally
                return 1;
            }
        }

      return 0;
      }
  }
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////
int singleCommand::saveBuffer(int & filedes){
  
    std::istringstream buf(input);
    std::istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);
      
    //checks if the command is a test command
    if(tokens.at(0)=="test"){
        return testCommand (tokens);
        
    }
    
    //checks if the command is an exit command
    if(tokens.at(0)=="exit"){
        return 2;
        
    }
    
    //to execute the command, the string needs to be changed to a char**
    vector<string>temp;
    vector<char*>argsToChar;
    string buff;
    stringstream ss(input);
    while(ss >> buff) temp.push_back (buff);

    for (unsigned i=0; i<temp.size(); ++i) {
      std::string::size_type size = (temp.at(i)).size();
      char *buffer = new char[size + 1];
      strcpy(buffer, temp.at(i).c_str());
      argsToChar.push_back(buffer);    
    }
        
    argsToChar.push_back(NULL); 
    args = &argsToChar[0];
    
    //The pipe is used to see if execvp failed
    int execpipe[2];
    pipe(execpipe);
    fcntl(execpipe[1], F_SETFD, fcntl(execpipe[1], F_GETFD) | FD_CLOEXEC);
    pid = fork();
     
    if(pid<0) {
      perror("Fork failed");
      return 1;
    }
        
    if(pid==0) { //child process
      close(execpipe[0]);
        fclose(stdout);
        dup2( filedes, STDOUT_FILENO);
        close(filedes);
        execvp(args[0], args);
      
      //If execvp fails, it returns and the child writes to one end of the pipe.
      perror("Error");
      write(execpipe[1], &errno, sizeof(errno));
      exit(EXIT_FAILURE);
    }
        
    if(pid>0) {
      
      //The parent waits fot the child process
      //  if(waitpid(pid, &status, WIFEXITED(&status))!=-1){
      if(wait(&status)==-1){
        perror("Wait error");
      }

    close(execpipe[1]);
    int childErrno;
   
    //If the parent can read from the pipe, it means the execvp failed, and the function returns -1
      if(read(execpipe[0], &childErrno, sizeof(childErrno)) == sizeof(childErrno)) {
        this->input.erase (input.begin(), input.end());
        this->args = NULL;
        return 1;
      }
            
      else {
    
      return 0;
      
      }
  }
  return 0;
}

void singleCommand::remove(){
    //does nothing
}