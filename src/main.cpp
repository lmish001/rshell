#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include "stdio.h"
#include <stdlib.h>
#include <stack>
#include <limits>
#include <sstream>
#include<boost/tokenizer.hpp>

using namespace std;

#include "Parse.h"

// Parse separates userInput and should construct a tree of commands to be executed
std::vector<std::string> separator(const std::string & userInput, const std::vector<std::string> & connectors);

// Eliminates any possible spacing related issue
void fixVectorSpacing(std::vector<std::string> &);

// Function that helps check for invalid syntax
bool syntaxChecker(std::vector<std::string> &);

// Converts vector or userinput into postfix notation
std::vector<std::string> postfixConverter(const std::vector<std::string> &v);

// Function that will be used to help handle quotations being passed in from user
bool findMatch(const std::string &userInput, unsigned i, unsigned &addAmt, const char);

// Function used to help handle brackets being passed in
bool findMatchBracket(const std::string &userInput, unsigned i, unsigned &j);

// Function checks to make sure quotations are balanced and parentheses and brackets are balanced. Outputs an error if not.
bool balancedSyntax(const std::string &userInput);

// Function that checks to make sure parentheses are correct syntactically. Should be final syntax checker 
bool properSyntax(const std::vector<std::string> & v);

// Adds parentheses to fix order of execution for io redirection
void fix_io(std::vector<std::string> & v);



int main(){
    
    std::string userInput;
    
    std::vector<std::string> connectors;
    connectors.push_back("&&");
    connectors.push_back("||");
    connectors.push_back("#");
    connectors.push_back(";");
    connectors.push_back(">>"); // Output_Redir2
    connectors.push_back(">"); // Output_Redir1
    connectors.push_back("<"); // Input_Redir
    connectors.push_back("|"); // Pipe
    
    int exit;
    Parse* p;
    system("./name.sh");
    
    // pipeCreator.cpp is the file we use to help handle piping.
    system("rm -rf pipeCreator.cpp");
    system("rm -rf pipeCreator.out");
    while ( getline(std::cin, userInput)){
        
        if (userInput.size() != 0){
    
            std::vector<std::string> separated_V = separator(userInput, connectors);
            fixVectorSpacing(separated_V);
            if (syntaxChecker(separated_V) && properSyntax(separated_V)){
                    fix_io(separated_V);
                    std::vector<std::string> v1 = postfixConverter(separated_V);
        
                    if (!v1.empty()){
                        p = new Parse(v1);
                        p->createTree();
                        exit = p->run();
                        separated_V.clear();
                        std::cout << flush;
                        if (exit == 2){
                              break;
                        }
                    }
            }
        }
            system("./name.sh");
    }
    return 0;
}

std::vector<std::string> separator (const std::string &userInput, const std::vector<std::string> &connectors){
    std::vector<std::string> complexParsed;
    std::string temp;
    std::string conn_temp;
    char conn_temp2;
    
    if (!balancedSyntax(userInput)){
        return complexParsed;
    }
    for (unsigned i = 0; i < userInput.size(); ++i){
        bool flag = false;
        unsigned addAmt = 0;
        for (unsigned j = 0; j < connectors.size(); ++j){
            if (!flag){
                conn_temp = connectors.at(j);
                conn_temp2 = conn_temp.at(0);
                if ( ((userInput.at(i) == '\"') && findMatch(userInput, i, addAmt, '\"')) || ((userInput.at(i) == '\'') && findMatch(userInput, i, addAmt, '\'')) ){
                    ++i;
                    while (addAmt > 0 && i < userInput.size()){
                        temp += userInput.at(i);
                        i++;
                        addAmt--;
                    }
                    ++i;
                    if (i >= userInput.size()){
                        complexParsed.push_back(temp);
                        return complexParsed;
                    }
                }
                else if ((userInput.at(i) == '[') && findMatchBracket(userInput, i, addAmt)){
                    if (!temp.empty()){
                        complexParsed.push_back(temp);
                        temp.clear();
                    }
                    ++i;
                    temp += "test";
                    while (addAmt > 0 && i < userInput.size()){
                        temp += userInput.at(i);
                        i++;
                        addAmt--;
                    }
                    
                    if (userInput.at(i - 1) != ' ' ){
                        //std::cout << "bash: [: missing `]\'" << std::endl;
                        temp = "test -f -d -e syntaxStuff";
                        complexParsed.push_back(temp);
                        temp.clear();
                    }
                    else {
                        complexParsed.push_back(temp);
                        temp.clear();
                    }
                    i++;
                    if (i >= userInput.size()){
                        return complexParsed;
                    }
                }
                if ((userInput.at(i) == '(') || (userInput.at(i) == ')')){
                    if (!temp.empty()){
                        complexParsed.push_back(temp);
                        temp.clear();
                    }
                    temp += userInput.at(i);
                    complexParsed.push_back(temp);
                    temp.clear();
                    flag = true;
                    
                }
                else if (userInput.at(i) == conn_temp2){
                    bool enter = true;
                    if (conn_temp.size() == 1){
                        if (!temp.empty()){
                            // Prevents a single space from being pushed into its own spot in the vector
                            if (!(temp.size() == 1 && temp.at(0) == ' ')){
                                complexParsed.push_back(temp);
                            }
                            temp.clear();
                        }
                        if (conn_temp2 == '#'){
                            if (i == 0){
                                return complexParsed;    
                            }
                            else if (userInput.at(i - 1) == ' '){
                                return complexParsed;   
                            }
                            else {
                                enter = false;
                                flag = true;
                                temp += "#";
                            }
                        }
                        if (enter){
                            complexParsed.push_back(conn_temp);
                            flag = true;
                        }
                    }
                    else if (i + 1 < userInput.size() && userInput.at(i + 1) == conn_temp2){
                        if (!temp.empty()){
                            // Prevents a single space from being pushed into its own spot in the vector
                            if (!(temp.size() == 1 && temp.at(0) == ' ')){
                                complexParsed.push_back(temp);
                            }
                            temp.clear();
                        }
                        complexParsed.push_back(conn_temp);
                        flag = true;
                        i++;
                    }
                }
            }
        }
        // Makes sure a connector doesnt get re-added to the vector in another spot
        if(!flag) {
            temp += userInput.at(i);
        }
        
    }
    if (!temp.empty()){
        complexParsed.push_back(temp);
    }
    return complexParsed;
}

void fixVectorSpacing(std::vector<std::string> &v){
    for (unsigned i = 0; i < v.size(); ++i){
        if (v.at(i).empty()){
            v.erase(v.begin() + i);
        }
       else if (v.at(i).at(0) == ' ' || v.at(i).at(v.at(i).size() - 1) == ' '){
            if (v.at(i).at(0) == ' '){
                unsigned j = 0;
                // Counts number of spaces
                while (j < v.at(i).size() && v.at(i).at(j) == ' '){
                    ++j;
                }
                // If a v.at(i) contains solely spaces, v.at(i) is deleted
                if (v.at(i).size() == j){
                    v.erase(v.begin() + i);
                }
                // Otherwise, the beginning spaces are removed
                else if (j > 0){
                    v.at(i) = v.at(i).substr(j,v.at(i).size() - j);
                }
            }
            while (!(v.at(i).empty()) && v.at(i).at(v.at(i).size() - 1) == ' '){
                v.at(i).erase(v.at(i).size() - 1);
            }
            if (v.at(i).empty()){
                v.erase(v.begin() + i);
            }
        }
        else if (v.at(i).at(0) == '#'){
            v.at(i - 1) += v.at(i);
            v.erase(v.begin() + i);
        }
    }
}

bool findMatch(const std::string &userInput, unsigned i, unsigned &addAmt, const char grouper){
    ++i;
    for(; i < userInput.size(); ++i){
        ++addAmt;
        if (userInput.at(i) == grouper){
            --addAmt;
            return true;
        }
    }
    addAmt = 0;
    return false;
}

bool findMatchBracket(const std::string &userInput, unsigned i, unsigned &j){
    unsigned numInstances = 1;
    ++i;
    for(; i < userInput.size(); ++i){
        ++j;
        if (userInput.at(i) == '['){
            ++numInstances;
        }
        if (userInput.at(i) == ']'){
            if (numInstances == 1){
                --j;
                return true;
            }
            else {
                --numInstances;
            }
        }
    }
    j = 0;
    return false;
}

bool balancedSyntax(const std::string &userInput){
    bool doubleQuoteBalanced = true;
    int parenCounter = 0;
    for(unsigned i = 0; i < userInput.size(); ++i){
        if (userInput.at(i) == '\"'){
            doubleQuoteBalanced = !doubleQuoteBalanced;
            
        }
        else if (doubleQuoteBalanced && userInput.at(i) == '('){
            parenCounter++;
        }
        else if (doubleQuoteBalanced && userInput.at(i) == ')'){
            if (parenCounter <= 0){
                std::cout << "error: parentheses are unbalanced" << std::endl;
                return false;
            }
            else {
                parenCounter--;
            }
        }
    }
    if (parenCounter != 0){
        std::cout << "syntax error: parentheses are unbalanced" << std::endl;
        return false;
    }
    else if (!doubleQuoteBalanced){
        std::cout << "syntax error: double quotes are unbalanced" << std::endl;
        return false;
    }
    
    return true;
}

std::vector<std::string> postfixConverter(const std::vector<std::string> &v){
    std::vector<std::string> postfix;
    std::vector<std::string> temp;
    std::stack<std::string> s;
    std::string c;
    for(unsigned i = 0; i < v.size();++i){
        c = v.at(i);

        if (c == "&&" || c == "||" || c == ";" || c == ">>" || c == ">" || c == "<" || c == "|" || c == "(" || c == ")"){ //c is an operator
            if ( c == "("){
                s.push(c);
            }
            else if (c == ")"){
                while (s.top() != "("){
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.pop();
            }
            else{
                while (!s.empty()){
                    if (s.top() == "("){
                        break;
                    }
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.push(c);
            }
        }
        else{
            postfix.push_back(c);
        }
    }
    while (!s.empty()){
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

bool syntaxChecker(std::vector<std::string> &v){
    // Need special checker for ()'s'
    int counter = 0;
    int parenCounter = 0;
    bool io_flag = false;
    if (v.empty()){
        // No syntax exists to be checked
        return true;
    }
    // The first item in the vector should never be a connector
    if (v.at(0) == "&&" || v.at(0) == "||" || v.at(0) == ";" || v.at(0) == ">>" || v.at(0) == ">" || v.at(0) == "<" || v.at(0) == "|"){
        std::cout << "bash: syntax error near unexpected token: " << v.at(0) << std::endl;
        return false;
    }
    if (v.size() == 1 && (v.at(0) == "(" || v.at(0) == ")")){
        std::cout << "bash: syntax error near unexpected token: " << v.at(0) << std::endl;
        return false;
    }
    
    // This loop will check to make sure "connectors" are not placed consecutively after each other
    for (unsigned i = 0; i < v.size(); ++i){
        if (v.at(i) == "&&" || v.at(i) == "||" || v.at(i) == ";" || v.at(i) == ">>" || v.at(i) == ">" || v.at(i) == "<" || v.at(i) == "|"){
            ++counter;
            // Certain connectors cannot be followed by anything in parentheses
            if(v.at(i) == ">>" || v.at(i) == ">" || v.at(i) == "<"){
                io_flag = true;
            }
        }
        else if (v.at(i) == "(" || v.at(i) == ")"){
            if (io_flag){
                std::cout << "bash: syntax error near unexpected token: " << v.at(i) << std::endl;
                return false; 
            }
            if (v.at(i) == "("){
                ++parenCounter;
            }
            else {
                if (parenCounter > 0){
                    --parenCounter;
                }
                else {
                    std::cout << "bash: syntax error near unexpected token: " << v.at(i) << std::endl;
                    return false;
                }
            }
        }
        else {
            counter = 0;
            io_flag = false;
        }
        
        if (counter >= 2){
            std::cout << "bash: syntax error near unexpected token: " << v.at(i) << std::endl;
            return false;
        }
        // Makes sure a "connector" is not the last item passed from userInput
        if (i == v.size() - 1){
            if (v.at(i) == "&&" || v.at(i) == "||" || v.at(i) == ">>" || v.at(i) == ">" || v.at(i) == "<" || v.at(i) == "|"){
                    std::cout << "bash: syntax error near unexpected token: " << v.at(i) << std::endl;
                    return false;
                }
            else if (v.at(i) == ";"){
                v.pop_back();
            }
        }
    }
    if (parenCounter != 0){
        // Parentheses were unbalanced
        std::cout << "bash: syntax error near unexpected token: ("  << std::endl;
        return false;
    }
    return true;
}

bool properSyntax(const std::vector<std::string> & v){
    std::string p;
    bool flag = false;
    for (unsigned i = 0; i < v.size(); ++i){
        p = v.at(i);
        if (p == "("){
            if (i > 0){
                if (v.at(i - 1) != "(" && !(v.at(i - 1) == "&&" || v.at(i - 1) == "||" || v.at(i - 1) == ";" || v.at(i - 1) == ">>" || v.at(i - 1) == ">" || v.at(i - 1) == "<" || v.at(i - 1) == "|")){
                    std::cout << "bash: syntax error near unexpected token: " << v.at(i - 1) << std::endl;
                    return false;
                } 
            }
            flag = true;
        }
        else if (p == ")"){
            if (v.at(i - 1) == "&&" || v.at(i - 1) == "||" || v.at(i - 1) == ";" || v.at(i - 1) == ">>" || v.at(i - 1) == ">" || v.at(i - 1) == "<" || v.at(i - 1) == "|" || v.at(i - 1) == "("){
                std::cout << "bash: syntax error near unexpected token: " << v.at(i - 1) << std::endl;
                return false;
            }
            flag = false;
        }
        else if (flag){
            if (p == "&&" || p == "||" || p == ";" || p == ">>" || p == ">" || p == "<" || p == "|"){
                std::cout << "bash: syntax error near unexpected token: " << p << std::endl;
                return false;
            }
            flag = false;
        }
    }
    return true;
}

void fix_io(std::vector<std::string> & v){
    //std::cout << "Fixme: fix_io: need to be able to handle consecutive uses" << std::endl;
    int lastSeen = 0;
    bool flag = false;
    for (unsigned i = 0; i < v.size(); ++i){
        if (v.at(i) == "&&" || v.at(i) == "||" || v.at(i) == ";" || v.at(i) == ">>" || v.at(i) == ">" || v.at(i) == "<" || v.at(i) == "|"){
            if((v.at(i) == ">>" || v.at(i) == ">" || v.at(i) == "<" || v.at(i) == "|") && v.at(i - 1) != ")" ){
                lastSeen = i;
                v.insert((v.begin() + i - 1), "(");
                v.insert((v.begin() + i + 3), ")");
                ++i;
                flag = true;
            }
            else if((v.at(i) == "&&" || v.at(i) == "||" || v.at(i) == ";" ) && v.at(i - 1) == ")" ){
                flag = false;
            }
            else if(flag){
                v.insert((v.begin() + lastSeen - 1), "(");
                v.insert((v.begin() + i + 3), ")");
                ++i;
            }
        }
    }
}



