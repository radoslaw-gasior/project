#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include<sstream>
#include<tuple>
#include "functions.h"
#include "structures.h"
using namespace std;




int main(int argc, char* argv[]) {
    
    string s = "a";

        bool has_only_digits = (s.find_first_not_of("0123456789") == std::string::npos);


    if (has_only_digits == true) {
        cout << "true" << endl;
    }
    else cout << "false" << endl;

    string val = ">";
    if (val == ">") {
        cout << "yes!yes!yes!" << endl;
    }


    //END OF TESTING SECTION


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

    while (getline(DefinitionFile, line)) {
        readLine(root, line);
    }
    DefinitionFile.close();


    vector<string>labels;
    for (int i = 0; i < inputdata[0].size(); i++) {
        labels.push_back(inputdata[0][i]);
    }

    
    vector<vector<string>> processeddata;

    for (int i = 1; i < inputdata.size(); i++) {

        cout << "decision " << i << ":   ";
         makedecision(root, labels, inputdata[i]);
         cout << endl;
    }
    
    
    cout << "Input data read test:  "<<inputdata[0][1] <<" "<<inputdata[0].size()<< endl; // read testing purposes
    if (root != NULL) {
        root = root->left;
    }

    cout <<"Left child key: "<< root->key << endl;

    return 0;
}