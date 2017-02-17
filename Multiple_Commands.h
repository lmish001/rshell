#ifndef MULTIPLE_COMMANDS__H
#define MULTIPLE_COMMANDS__H

#include <iostream>
using namespace std;

class Multiple_Commands {
     protected:
          string name;
     public:
     
     // Constructor
     Multiple_Commands(){}
     
     //Mutator
     virtual void SetParam();
     virtual void SetParam(string);
     // Accessor
     string GetParam();

};


class OR : public Multiple_Commands{
     public:
          OR(){
               SetParam();
          }
          void SetParam();
          void SetParam(string);
};

class AND : public Multiple_Commands{
     public:
          AND(){
               SetParam();
          }
          void SetParam();
          void SetParam(string);
};

class SEMICOLON : public Multiple_Commands{
     public:
          SEMICOLON(){
               SetParam();
          }
          void SetParam();
          void SetParam(string);
};

class COMMENT : public Multiple_Commands{
     public:
          COMMENT(){
               SetParam();
          }
          void SetParam();
          void SetParam(string);
};








#endif



