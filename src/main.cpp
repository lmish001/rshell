#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include "stdio.h"

// using namespace std;


#include "Parse.h"

// Removes all the unnessary parts of the host's username
void fixedName(char* username, char* machinename);

// Function used to compare two chars
bool charCompare(const char a, const char b);

// Parse separates userInput and should construct a tree of commands to be executed
std::vector<std::string> separator(const std::string & userInput, const std::vector<std::string> & connectors);

// Eliminates any possible spacing related issue
void fixVector(std::vector<std::string> &);

int main(){
    
    bool run = true;
    std::string userInput;
    // For changing text color of our terminal
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
    
    // To get username and machine name
    char username[HOST_NAME_MAX];
    char machinename[HOST_NAME_MAX];
    gethostname(username, HOST_NAME_MAX);
    fixedName(username, machinename);

    

    
    std::vector<std::string> connectors;
    connectors.push_back("#");
    connectors.push_back(";");
    connectors.push_back("&&");
    connectors.push_back("||");
    int exit;
    Parse* p;

    while (run){
         
        std::cout << blue << username << normal;
        std::cout << "@";
        std::cout << green << machinename << normal;
        std::cout << " $ ";
        getline(std::cin, userInput);
         
        if (userInput.size() != 0){
            // Calls separator function
            std::vector<std::string> separated_V = separator(userInput, connectors);
            fixVector(separated_V);
            // Checks to see values stored in vector
            // for (unsigned i = 0; i < separated_V.size(); ++i){
            //     cout << i << " " << separated_V.at(i) << endl;
            // }
            p = new Parse(separated_V);
            exit = p->createTree();
            
            if(exit == 2){
                break;
            }
        }
        std::cout << exit << std::endl;
        
    }
    
    return 0;
}

std::vector<std::string> separator (const std::string &userInput, const std::vector<std::string> &connectors){
    std::vector<std::string> parsed;
    std::string temp;
    std::string conn_temp;
    char conn_temp2;

    for (unsigned i = 0; i < userInput.size(); ++i){
        bool flag = false;
        for (unsigned j = 0; j < connectors.size(); ++j){
            if (!flag){
                conn_temp = connectors.at(j);
                conn_temp2 = conn_temp.at(0);
                if (charCompare(userInput.at(i), conn_temp2)){
                    if (conn_temp.size() == 1){
                        if (!temp.empty()){
                            // Prevents a single space from being pushed into its own spot in the vector
                            if (!(temp.size() == 1 && charCompare(temp.at(0), ' '))){
                                parsed.push_back(temp);
                            }
                            temp.clear();
                        }
                        if (charCompare(conn_temp2, '#')){
                            return parsed;
                        }
                        parsed.push_back(conn_temp);
                        flag = true;
                    }
                    else if (i + 1 < userInput.size() && charCompare(userInput.at(i + 1), conn_temp2)){
                        if (!temp.empty()){
                            // Prevents a single space from being pushed into its own spot in the vector
                            if (!(temp.size() == 1 && charCompare(temp.at(0), ' '))){
                                parsed.push_back(temp);
                            }
                            temp.clear();
                        }
                        parsed.push_back(conn_temp);
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
        parsed.push_back(temp);
    }
    return parsed;
}

bool charCompare(const char a, const char b){
    return a == b;
}

void fixedName(char* username, char* machinename){
    unsigned i = 0;
    while (username[i] != '-'){
        ++i;
    }
    username[i] = '\0';
    ++i;
    unsigned j = 0;
    while (username[i] != '-'){
        machinename[j] = username[i];
        ++i;
        ++j;
    }
    machinename[i] = '\0';
}

void fixVector(std::vector<std::string> &v){
    for (unsigned i = 0; i < v.size(); ++i){
        if (charCompare(v.at(i).at(0), ' ')){
            unsigned j = 0;
            // Counts number of spaces
            while (j < v.at(i).size() && charCompare(v.at(i).at(j), ' ')){
                ++j;
            }
            // If a v.at(i) contains solely spaces, v.at(i) is deleted
            if (v.at(i).size() == j){
                v.erase(v.begin() + i);
            }
        }
    }
}





