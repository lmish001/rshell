#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include "stdio.h"
#include <stdlib.h>
#include <utility>



#include "Parse.h"

// Parse separates userInput and should construct a tree of commands to be executed
std::vector<std::pair<std::string, int> > separator(const std::string & userInput, const std::vector<std::string> & connectors);

// Eliminates any possible spacing related issue
void fixVectorSpacing(std::vector<std::pair<std::string, int> > &);

// Function that will be used to help handle quotations and parentheses being passed in from user
bool findMatch(const std::string &userInput, unsigned i, unsigned &j, const char);

bool findMatchParentheses(const std::string &userInput, unsigned i, unsigned &j);

// Function checks to make sure quotations are balanced and parentheses and brackets are balanced. Outputs an error if not.
bool balancedSyntax(const std::string &userInput);

bool properSyntax(const std::vector<std::pair<std::string, int> > & v, const std::vector<std::string> &connectors);

int main(){
    
    bool run = true;
    std::string userInput;
    

    
    std::vector<std::string> connectors;
    connectors.push_back("#");
    connectors.push_back(";");
    connectors.push_back("&&");
    connectors.push_back("||");
    int exit;
    Parse* p;

    while (run){
         
        system("./name.sh");
        getline(std::cin, userInput);
        // userInput is only empty when a here string is used in one of the test scripts
        if (userInput.empty()){
            break;
        }
        if (userInput.size() != 0){
            
            std::vector<std::pair<std::string, int> > separated_V = separator(userInput, connectors);
            fixVectorSpacing(separated_V);
            
            std::vector<std::string> temp_separated_V;
            for (unsigned int i = 0; i < separated_V.size(); ++i){
                temp_separated_V.push_back(separated_V.at(i).first);
            }

            if ((temp_separated_V.size()%2)!=0){
                p = new Parse(temp_separated_V);
                p->createTree();
                exit = p->run();
                separated_V.clear();
                if(exit == 2){
                      break;
                }
            }
                
        }
        
    }
    
    return 0;
}

std::vector<std::pair<std::string, int> > separator (const std::string &userInput, const std::vector<std::string> &connectors){
    std::vector<std::pair<std::string, int> > complexParsed;
    std::pair<std::string, int> p;
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
                if ((userInput.at(i) == '\"') && findMatch(userInput, i, addAmt, '\"')){
                    ++i;
                    while (addAmt > 0 && i < userInput.size()){
                        temp += userInput.at(i);
                        i++;
                        addAmt--;
                    }
                    ++i;
                    if (i >= userInput.size()){
                        p.first = temp;
                        p.second = 0;
                        complexParsed.push_back(p);
                        return complexParsed;
                    }
                }
                else if ((userInput.at(i) == '(') && findMatchParentheses(userInput, i, addAmt)){
                    if (!temp.empty()){
                        p.first = temp;
                        p.second = 0;
                        complexParsed.push_back(p);
                        temp.clear();
                    }
                    ++i;
                    while (addAmt > 0 && i < userInput.size()){
                        temp += userInput.at(i);
                        i++;
                        addAmt--;
                    }
                    ++i;
                    p.first = temp;
                    p.second = 1;
                    complexParsed.push_back(p);
                    temp.clear();
                    if (i >= userInput.size()){
                        return complexParsed;
                    }
                }
                if (userInput.at(i) == conn_temp2){
                    if (conn_temp.size() == 1){
                        if (!temp.empty()){
                            // Prevents a single space from being pushed into its own spot in the vector
                            if (!(temp.size() == 1 && temp.at(0) == ' ')){
                                p.first = temp;
                                p.second = 0;
                                complexParsed.push_back(p);
                            }
                            temp.clear();
                        }
                        if (conn_temp2 == '#'){
                            return complexParsed;
                        }
                        p.first = conn_temp;
                        p.second = 0;
                        complexParsed.push_back(p);
                        flag = true;
                    }
                    else if (i + 1 < userInput.size() && userInput.at(i + 1) == conn_temp2){
                        if (!temp.empty()){
                            // Prevents a single space from being pushed into its own spot in the vector
                            if (!(temp.size() == 1 && temp.at(0) == ' ')){
                                p.first = temp;
                                p.second = 0;
                                complexParsed.push_back(p);
                            }
                            temp.clear();
                        }
                        p.first = conn_temp;
                        p.second = 0;
                        complexParsed.push_back(p);
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
        p.first = temp;
        p.second = 0;
        complexParsed.push_back(p);
    }
    return complexParsed;
}

void fixVectorSpacing(std::vector<std::pair<std::string, int> > &v){
    for (unsigned i = 0; i < v.size(); ++i){
        if (v.at(i).first.empty()){
            v.erase(v.begin() + i);
        }
        else if (v.at(i).first.at(0) == ' '){

            unsigned j = 0;
            // Counts number of spaces
            while (j < v.at(i).first.size() && v.at(i).first.at(j) == ' '){
                ++j;
            }
            // If a v.at(i) contains solely spaces, v.at(i) is deleted
            if (v.at(i).first.size() == j){
                v.erase(v.begin() + i);
            }
            // Otherwise, the beginning spaces are removed
            else if (j > 0){
                v.at(i).first = v.at(i).first.substr(j,v.at(i).first.size() - j);
            }
        }
    }
}

bool findMatch(const std::string &userInput, unsigned i, unsigned &j, const char grouper){
    ++i;
    for(; i < userInput.size(); ++i){
        ++j;
        if (userInput.at(i) == grouper){
            --j;
            return true;
        }
    }
    j = 0;
    return false;
}

bool findMatchParentheses(const std::string &userInput, unsigned i, unsigned &j){
    unsigned numInstances = 1;
    ++i;
    for(; i < userInput.size(); ++i){
        ++j;
        if (userInput.at(i) == '('){
            ++numInstances;
        }
        if (userInput.at(i) == ')'){
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
        std::cout << "error: parentheses are unbalanced" << std::endl;
        return false;
    }
    else if (!doubleQuoteBalanced){
        std::cout << "error: double quotes are unbalanced" << std::endl;
        return false;
    }
    
    return true;
}

bool properSyntax(const std::vector<std::pair<std::string, int> > & v, const std::vector<std::string> &connectors){
    std::pair<std::string, int> p;
    for (unsigned i = 0; i < v.size(); ++i){
        p = v.at(i);
        if (i % 2 != 0){
            // Should have connectors only
            if (p.second == 0){
                if (!(p.first == "&&" || p.first == "||" || p.first == ";")){
                    std::cout << "bash: syntax error near unexpected token: " << p.first << std::endl;
                    return false;
                }
            }
            else if (p.second == 1){
                std::string reducedString; 
                for (unsigned j = 0; j < p.first.size(); ++j){
                    if (p.first.at(j) != '(' || p.first.at(j) != ')'){
                        reducedString += p.first.at(j);
                    }
                }
                if (!(reducedString == "&&" || reducedString == "||" || reducedString == ";")){
                    std::cout << "bash: syntax error near unexpected token: " << "(" << std::endl;
                    return false;
                }
                
            }
        }
        else {
            std::vector<std::pair<std::string, int> > v = separator(p.first, connectors);
            fixVectorSpacing(v);
            if (p.second == 0){
                // First and last parts cannot have a connector, with the expection being a semi-colon at the end
                if (v.at(0).first == "&&" || v.at(0).first == "||" || v.at(0).first == ";"){
                    std::cout << "bash: syntax error near unexpected token: " << v.at(0).first << std::endl;
                    return false;
                }
                else if (v.at(v.size() - 1).first == "&&" || v.at(v.size() - 1).first == "||"){
                    std::cout << "bash: syntax error near unexpected token: " << v.at(v.size() - 1).first << std::endl;
                    return false;
                }
                
            }
            else if (p.second == 1){
                properSyntax(v, connectors);
            }
        }
    }
    return true;
}











