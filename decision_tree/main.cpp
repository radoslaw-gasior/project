#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include<sstream>
#include "functions.h"
#include "structures.h"
using namespace std;

int main(int argc, char* argv[]) {

    string input = inputSwitch(argc, argv);
    string definition = definitionSwitch(argc, argv);
    string output = outputSwitch(argc, argv);

    if (switchcontrol(input, definition, output) == 0) {
        return 0;
    }

    showFiles(input, definition, output);

    vector<vector<string>> inputdata;
    ReadInputData(inputdata, input);

    node* root = NULL;
    vector<string> DecisionLabels;

    ReadDefinitionFile(root, DecisionLabels, definition);

    vector<string>labels;
    for (int i = 0; i < inputdata[0].size(); i++) {
        labels.push_back(inputdata[0][i]);
    }

    vector<string> decisions;
    for (int i = 1; i < inputdata.size(); i++) {
        makedecision(root, labels, inputdata[i], decisions);
    }
    
    for (int i = 1; i < inputdata.size(); i++) {
        inputdata[i].push_back(decisions[i - 1]);
    }

    generateOutput(inputdata, output, DecisionLabels);

    root = deleteTree(root);
    inputdata.clear();
    decisions.clear();
    DecisionLabels.clear();
    labels.clear();

    return 0;
}