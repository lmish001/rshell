#include "multipleCommands.h"
#include "singleCommand.h"
#include "Command.h"
#include <typeinfo>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <boost/lexical_cast.hpp>
using namespace std;

vector <string> multipleCommands::redir_v;
vector <string> multipleCommands::vector_pipe;


int multipleCommands::vectorize(){
    singleCommand* temp = dynamic_cast<singleCommand*>(left);
    if(temp == 0) { // The left child is another connector
        Pipe* check = dynamic_cast<Pipe*>(left);
        if (check == 0){ // Piping unable to handle complex input at this time
            return 1;
        }
        left->vectorize();
        multipleCommands::vector_pipe.push_back(static_cast<singleCommand*>(right)->getInput());
        return 0;
    }
    else{ // The left child is a singleCommand
        multipleCommands::vector_pipe.push_back(static_cast<singleCommand*>(left)->getInput());
        multipleCommands::vector_pipe.push_back(static_cast<singleCommand*>(right)->getInput());
        return 0;
    }
}


void multipleCommands::fileStarter(std::ofstream & file){
    file << "#include <iostream> \n";
    file << "#include <unistd.h> \n";
    file << "#include <errno.h> \n";
    file << "#include <sys/wait.h> \n";
    file << "#include <fstream> \n";
    file << "#include <fcntl.h> \n";
    file << "#include <stdio.h> \n";
    file << "#include <stdlib.h> \n";
    file << "using namespace std; \n \n";
    
    file << "int specialExecute (int in, int out, struct command *cmd); \n";
    file << "int execute (int size, struct command *cmd); \n";
    
    file << "struct command{ \n";
    file << "  const char **argv; \n";
    file << "}; \n";
    
    file << "int main (){ \n";
    file << "int size = 0; \n";
    
}

void multipleCommands::fileFinisher(std::ofstream & file){
    // file << "ofstream output; \n";
    // file << "output.open(\"returnVal.cpp\"); \n";
    //
    // char buffer[256];
    // snprintf(buffer, sizeof(buffer), "./returnVal.out %i", returnVal);
    // system(buffer);
    file << "int returnVal = execute(size, cmd); \n";
    //file << "cout << \"ReturnVal is \" << returnVal << endl; \n";
    // file << "output << returnVal; \n";
    // file << "output.close(); \n";
    //file << "system(\"./returnVal.cpp returnVal\"); \n";
   file << "return returnVal; \n";
    file << "} \n";
    file << "int execute (int size, struct command *cmd){ \n";
        file << "  int i; \n";
        file << "  pid_t pid; \n";
        file << "  int in, filedes [2]; \n";
        file << "  in = 0; \n";
        file << "  for (i = 0; i < size - 1; ++i){ \n";
        file << "    pipe(filedes); \n";
        file << "fcntl(filedes[1], F_SETFD, fcntl(filedes[1], F_GETFD) | FD_CLOEXEC); \n";
        file << "    specialExecute(in, filedes[1] ,cmd + i); \n";
        file << "    close (filedes[1]); \n";
        file << "    in = filedes [0]; \n";
        file << "  } \n \n";
        file << "if (in != 0){ \n";
        file << "  dup2(in, 0); \n";
        file << "} \n";
        file << "return execvp(cmd[i].argv[0], (char * const *)cmd [i].argv); \n";
        // file << "perror(\"Error\"); \n";
        //     file << "write(execpipe[1], & errno, sizeof(errno)); \n";
        //     file << "exit(EXIT_FAILURE); \n";
    file << "} \n";
    
    file << "int specialExecute (int in, int out, struct command *cmd) { \n";
        file << "  int status; \n"; 
        file << "  pid_t pid; \n";
        file << "  if ((pid = fork() ) == 0){ // Child Process \n";
        file << "    if (in != 0){; \n";
        file << "      dup2(in,0); \n";
        file << "      close(in); \n";
        file << "    } \n";
        file << "    if (out != 1){ \n";
        file << "      dup2(out,1); \n";
        file << "      close (out); \n";
        file << "    } \n";
        file << "    return execvp (cmd->argv[0], (char * const *)cmd->argv); \n";
        file << "  } \n";
        file << " else if (pid > 0) { // Parent Process \n";
            file << "wait(&status); \n";
            file << "if(WIFEXITED(status)){ \n";
                file << "if(WEXITSTATUS(status) == 0){ return 0 ;} \n";
                file << "else {return 1;} \n";
            file << "} \n";
        file << "} \n";
        file << "return pid; \n";
    file << "} \n";
   
    
}

int multipleCommands::containsElem(std::string elem){
    unsigned i;
    for (i=0; i<multipleCommands::redir_v.size(); i++){
        if (multipleCommands::redir_v.at(i)==elem){
            return 1;
        }
    }
    return 0;
}


int multipleCommands::getInFiledes(){
    unsigned i;
    for (i=0; i<multipleCommands::redir_v.size(); i++){
        if(redir_v.at(i)=="in"){
             int value = boost::lexical_cast<int>(multipleCommands::redir_v.at(i+1));
             return value;
        }
    }
    return 0;
}

int multipleCommands::getOutFiledes(){
    unsigned i;
    for (i=0; i<multipleCommands::redir_v.size(); i++){
        if(redir_v.at(i)=="out"){
             int value = boost::lexical_cast<int>(multipleCommands::redir_v.at(i+1));
             return value;
        }
    }
    return 0;
}

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

int And::saveBuffer(int & filedes){
    int returnVal = left->saveBuffer(filedes);
    if (returnVal == 0){
        return right->saveBuffer(filedes);
    }
    return returnVal;
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

int Or::saveBuffer(int & filedes){
    int returnVal = left->saveBuffer(filedes);
    if (returnVal == 1){
        right->saveBuffer(filedes);
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

int Semicolon::saveBuffer(int & filedes){
    int returnVal = left->saveBuffer(filedes);
    if (returnVal != 2){
        right->saveBuffer(filedes);
    }
    return returnVal;
}

void Semicolon::remove(){
    this->left = NULL;
    this->right = NULL;
}


Input_Redir::Input_Redir(Command *left, Command *right){
    this->left=left;
    this->right=right;
}


int Input_Redir::execute(){
    // Input is from the right child
    // The left child will process the contents of the right child
    int filedes;
    string s = static_cast<singleCommand*>(right)->getInput();
    if (s.empty()){
        std::cout << "Error in singleCommand: string s is NULL" << std::endl;
        return 1;
    }
      
    const char *input = s.c_str();
      
    struct stat buffer;   
    if(stat (s.c_str(), &buffer) != 0) {
        std::cout << "bash: " << s << ": No such file or directory" << std::endl;
        return 1;
    }
    
    else {
      filedes = open(input, O_RDONLY, 0777 );
    }
     
    if( filedes == 0 ) {
      perror("Error opening file");
      return 1;
    }
    
    if(containsElem("in")==0){
        multipleCommands::redir_v.push_back("in");
        string f =  boost::lexical_cast<string>(filedes);
        multipleCommands::redir_v.push_back(f);
    }
    singleCommand* test=dynamic_cast<singleCommand*>(left);
    if(test!=0){
        static_cast<singleCommand*>(left)->setInFiledes(getInFiledes());
        if(getOutFiledes()!=0){
          static_cast<singleCommand*>(left)->setOutFiledes(getOutFiledes());  
        }
        multipleCommands::redir_v.clear();
    }
    int returnVal = left->execute();
    return returnVal;
    
}

int Input_Redir::saveBuffer(int &pipeBuffer){
    int filedes;
    string s = static_cast<singleCommand*>(right)->getInput();
    if (s.empty()){
        std::cout << "Error in singleCommand: string s is NULL" << std::endl;
        return 1;
    }
      
    const char *input = s.c_str();
      
    struct stat buffer;   
    if(stat (s.c_str(), &buffer) != 0) {
        std::cout << "bash: " << s << ": No such file or directory" << std::endl;
        return 1;
    }
    
    else {
      filedes = open(input, O_RDONLY, 0777 );
    }
     
    if( filedes == 0 ) {
      perror("Error opening file");
      return 1;
    }
    
    if(containsElem("in")==0){
        multipleCommands::redir_v.push_back("in");
        string f =  boost::lexical_cast<string>(filedes);
        multipleCommands::redir_v.push_back(f);
    }
    if(containsElem("out")==0){
        multipleCommands::redir_v.push_back("out");
        string f =  boost::lexical_cast<string>(pipeBuffer);
        multipleCommands::redir_v.push_back(f);
    }
    singleCommand* test=dynamic_cast<singleCommand*>(left);
    if(test!=0){
        static_cast<singleCommand*>(left)->setInFiledes(getInFiledes());
        if(getOutFiledes()!=0){
          static_cast<singleCommand*>(left)->setOutFiledes(getOutFiledes());  
        }
        multipleCommands::redir_v.clear();
    }
    int returnVal = left->execute();
    return returnVal;
}

void Input_Redir::remove(){
    this->left = NULL;
    this->right = NULL;
}


Output_Redir1::Output_Redir1(Command *left, Command *right){
    this->left=left;
    this->right=right;
}


int Output_Redir1::execute(){

    // Template for how to execute ">"
    int filedes;
    string s = static_cast<singleCommand*>(right)->getInput();
    if (s.empty()){
        std::cout << "Error in singleCommand: string s is NULL" << std::endl;
        return 1;
    }
      
    const char *output = s.c_str();
    // filedes = open(output,  O_CREAT| O_TRUNC| O_WRONLY , 0777 );
    struct stat buffer;  
    if(stat (s.c_str(), &buffer) == 0){
        filedes = open(output, O_WRONLY | O_TRUNC, 0777 );
    }
    else{
        filedes = open(output, O_WRONLY | O_CREAT, 0777 );
    }
   
    if( filedes == -1 ) {
        perror("Error opening file");
        return 1;
    }
    int returnVal = left->saveBuffer(filedes);
    return returnVal;
}

int Output_Redir1::saveBuffer(int & pipeBuffer){
    int filedes;
    string s = static_cast<singleCommand*>(right)->getInput();
    if (s.empty()){
        std::cout << "Error in singleCommand: string s is NULL" << std::endl;
        return EXIT_FAILURE;
    }
      
    const char *output = s.c_str();
    //struct stat buffer;
    std::ifstream f(s.c_str());
    if (f.good()){
        filedes = open(output, O_WRONLY | O_TRUNC, 0777 );
    }
    else{
        filedes = open(output, O_WRONLY | O_CREAT, 0777 );
    }
      
        
      if( filedes == -1 ) {
        perror(output);
        return EXIT_FAILURE;
      }
    int returnVal = left->saveBuffer(pipeBuffer);
    return returnVal;
}

void Output_Redir1::remove(){
    this->left = NULL;
    this->right = NULL;
}


Output_Redir2::Output_Redir2(Command *left, Command *right){
    this->left=left;
    this->right=right;
}


int Output_Redir2::execute(){
    // Template for how to execute ">>"
    int filedes;
     string s = static_cast<singleCommand*>(right)->getInput();
     if (s.empty()){
        std::cout << "Error in singleCommand: string s is NULL" << std::endl;
        return 1;
    }
      
    const char *output = s.c_str();
    struct stat buffer;   
    if(stat (s.c_str(), &buffer) != 0){
        filedes = open(output, O_WRONLY | O_CREAT, 0777 );
    }
    else{
        filedes = open(output, O_WRONLY | O_APPEND, 0777);
    }
    if( filedes == -1 ) {
        perror("Error opening file");
        return 1;
    }
    int returnVal = left->saveBuffer(filedes);
    return returnVal;
}

int Output_Redir2::saveBuffer(int & pipeBuffer){
    
    int filedes;
    string s = static_cast<singleCommand*>(right)->getInput();
    if (s.empty()){
        std::cout << "Error in singleCommand: string s is NULL" << std::endl;
        return EXIT_FAILURE;
    }
        
    const char *output = s.c_str();
    struct stat buffer;
    
    if(stat (s.c_str(), &buffer) != 0){
        filedes = open(output, O_WRONLY | O_CREAT, 0777 );
    }
    else{
        filedes = open(output, O_WRONLY | O_APPEND, 0777);
    }
        
    if( filedes == -1 ) {
        perror(output);
        return EXIT_FAILURE;
    }
    int returnVal = left->saveBuffer(pipeBuffer);
    return returnVal;
}

void Output_Redir2::remove(){
    this->left = NULL;
    this->right = NULL;
}


Pipe::Pipe(Command *left, Command *right){
    this->left=left;
    this->right=right;
}

int Pipe::saveBuffer(int & pipeBuffer){
    return this->execute();
}

void Pipe::remove(){

    this->left = NULL;
    this->right = NULL;
}

int Pipe::execute(){
    multipleCommands::vector_pipe.clear();
    int exit = this->vectorize();
    if (exit != 0){
        return 1;
    }
    ofstream myfile;
    myfile.open("pipeCreator.cpp");
    
    fileStarter(myfile);
    // Enter Variable Information here
    char letter = 'A';
    for (unsigned int i = 0; i < multipleCommands::vector_pipe.size(); ++i){
        string params;
        string templat = "const char *";
        templat += letter;
        templat += "[] = { ";
        
        singleCommand s = multipleCommands::vector_pipe.at(i);
        vector<string>temp;
        vector<char*>argsToChar;
        string buff;
        stringstream ss(s.getInput());
        while(ss >> buff) temp.push_back (buff);
    
        for (unsigned j = 0; j < temp.size(); ++j) {
          std::string::size_type size = (temp.at(j)).size();
          char *buffer = new char[size + 1];
          strcpy(buffer, temp.at(j).c_str());
          argsToChar.push_back(buffer);    
        }
            
        argsToChar.push_back(NULL);
        for (unsigned a = 0; a < argsToChar.size() - 1; ++a){
            params += "\"";
            params += argsToChar.at(a);
            params += "\"";
            //cout << i << " " << argsToChar.at(i) << endl;
            params += ", ";
            
          
        }
        params += "0 }; \n";
        templat += params;
        myfile << templat;
        ++letter;
    }
    string templat = "struct command cmd [] = { ";
    char letterA = 'A';
    char numIncrement = '0';
    while (letterA < letter){
        string params = "{";
        params += letterA;
        params += "}";
        if (letterA < letter - 1){
            params += ", ";
        }
        templat += params;
        ++letterA;
        ++numIncrement;
    }
    templat += " }; \n";
    myfile << templat;
    string final = "size = ";
    final += numIncrement;
    final += "; \n";
    myfile << final;
    // Enter Variable Information here
    myfile << "\n";
    fileFinisher(myfile);
    myfile.close();
    
    system("g++ pipeCreator.cpp -o pipeCreator.out");
    system("./pipeCreator.out");
    return 0;
    
    
}
