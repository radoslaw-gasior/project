#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structures.h"


std::string inputSwitch(int argc, char* argv[]);
std::string definitionSwitch(int argc, char* argv[]);
std::string outputSwitch(int argc, char* argv[]);
int switchcontrol(std::string input, std::string definition, std::string output);
void showFiles(std::string input, std::string definition, std::string output);
void readLine(node*& root, std::string line);
node* addElement(node* root, std::string nodeindex, std::string variable1, std::string logic, float variable2, std::string nodefalse, std::string nodetrue);
void makedecision(node* root, std::vector<std::string> labels, std::vector<std::string> inputdata);
node* deleteTree(node* root);
#endif
