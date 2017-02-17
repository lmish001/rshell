#include "Multiple_Commands.h"


string Multiple_Commands::GetParam(){
     return name;
}

void Multiple_Commands::SetParam(){}

void Multiple_Commands::SetParam(string text){
     name = text;
}

void OR::SetParam(){
     name = "||";
}

void OR::SetParam(string text){}

void AND::SetParam(){
     name = "&&";
}

void AND::SetParam(string text){}

void SEMICOLON::SetParam(){
     name = ";";
}

void SEMICOLON::SetParam(string text){}

void COMMENT::SetParam(){
     name = "#";
}

void COMMENT::SetParam(string text){}
