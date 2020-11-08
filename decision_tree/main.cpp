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

    ifstream InputFile(input);

    vector<vector<string>> inputdata;
    string line;
    int i = 0;
    while (getline(InputFile, line)) {

        string data;
        inputdata.push_back(vector<string>());
        istringstream exist(line);

        while (exist >> data) {

            if (data == "%") {
                break;
            }
            else {
                inputdata[i].push_back(data);
            }
        }
        i++;
    }
    i = 0;
    InputFile.close();


    ifstream DefinitionFile(definition);
    node* root = NULL;
    vector<string> DecisionLabels;
    vector<string>* DL= &DecisionLabels;
    while (getline(DefinitionFile, line)) {
        readLine(root, line, DL);
    }
    DefinitionFile.close();
    remove(DecisionLabels);


    vector<string>labels;
    for (int i = 0; i < inputdata[0].size(); i++) {
        labels.push_back(inputdata[0][i]);
    }

    vector<string> decisions;
    vector<string>* tmp=&decisions;
    for (int i = 1; i < inputdata.size(); i++) {

        cout << "decision " << i << ":   ";
        makedecision(root, labels, inputdata[i], tmp);
        cout << endl;


    }
    
    for (int i = 1; i < inputdata.size(); i++) {

        inputdata[i].push_back(decisions[i - 1]);

    }

    generateOutput(decisions, inputdata, output, DecisionLabels);

    root = deleteTree(root);
    inputdata.clear();

    return 0;
}