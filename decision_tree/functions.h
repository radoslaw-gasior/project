#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structures.h"


std::string inputSwitch(int argc, char* argv[]);
std::string definitionSwitch(int argc, char* argv[]);
std::string outputSwitch(int argc, char* argv[]);
int switchcontrol(std::string input, std::string definition, std::string output);
void showFiles(std::string input, std::string definition, std::string output);
void readLine(node*& root, std::string line);
node* addElement(node* root, string nodeindex, string variable1, string logic, float variable2, string nodefalse, string nodetrue);
void makedecision();
#endif
