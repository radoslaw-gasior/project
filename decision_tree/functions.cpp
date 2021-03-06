#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "structures.h"
#include "functions.h"
using namespace std;

string inputSwitch(int argc, char* argv[])
{
    string arg;
    for (int i = 0; i < argc; i++)
    {
        arg = argv[i];
        if (arg == "-i")
        {
            if (argv[i + 1])
                return argv[i + 1];
        }
    }
    return "";
}

string definitionSwitch(int argc, char* argv[])
{
    string arg;
    for (int i = 0; i < argc; i++)
    {
        arg = argv[i];
        if (arg == "-t")
        {
            if (argv[i + 1])
                return argv[i + 1];
        }
    }
    return "";
}

string outputSwitch(int argc, char* argv[])
{
    string arg;
    for (int i = 0; i < argc; i++)
    {
        arg = argv[i];
        if (arg == "-o")
        {
            if (argv[i + 1])
                return argv[i + 1];
        }
    }
    return "";
}

int switchcontrol(string input, string definition, string output) {
    if (input == "")
    {
        cout << "Input switch not found";
        return 0;
    }
    if (definition == "")
    {
        cout << "Definition switch not found";
        return 0;
    }
    if (output == "")
    {
        cout << "Output switch not found";
        return 0;
    }

    return 1;
}

void showFiles(string input, string definition, string output) {
    cout << "Input file:        " << input << endl;
    cout << "Definition file:   " << definition << endl;
    cout << "Output file:       " << output << endl;
}

void ReadInputData(vector<vector<string>>& inputdata, string input) {
    ifstream InputFile(input);
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
    InputFile.close();
}

void ReadDefinitionFile(node*& root, vector<string>& DecisionLabels, string definition) {
    ifstream DefinitionFile(definition);
    string line;
    while (getline(DefinitionFile, line)) {
        readLine(root, line, DecisionLabels);
    }
    DefinitionFile.close();
    remove(DecisionLabels);
}

bool is_number(string s) {
    bool only_digits = (s.find_first_not_of("0123456789") == string::npos);
    return only_digits;
}

void readLine(node*& root, string line, vector<string>& DecisionLabels)
{
    string variable1, logic, nodefalse, nodetrue;
    float variable2 = 0;
    string nodeindex;
    string word;
    stringstream stream(line);
    int counter = 1;

    while (stream >> word)
    {
        if (word == "%") {
            break;
        }
        else {
            switch (counter)
            {
            case 1:
            {
                nodeindex = word;
                counter++;
                break;
            }
            case 2:
            {
                variable1 = word;
                counter++;
                break;
            }
            case 3:
            {
                logic = word;
                counter++;
                break;
            }
            case 4:
            {
                variable2 = stof(word);
                counter++;
                break;
            }
            case 5:
            {
                nodefalse = word;
                if (!is_number(nodefalse)) {
                    DecisionLabels.push_back(nodefalse);
                }
                counter++;
                break;
            }
            case 6:
            {
                nodetrue = word;
                if (!is_number(nodetrue)) {
                    DecisionLabels.push_back(nodetrue);
                }
                counter = 1;
                break;
            }
            }
        }
    }
    root = addElement(root, nodeindex, variable1, logic, variable2, nodefalse, nodetrue);
}

node* addElement(node* root, string nodeindex, string variable1, string logic, float variable2, string nodefalse, string nodetrue) {
    if (root == NULL) {
        node* newNode = new node;
        root = newNode;
        newNode->key = nodeindex;
        newNode->var1 = variable1;
        newNode->logic = logic;
        newNode->var2 = variable2;
        newNode->condition_false = nodefalse;
        newNode->condition_true = nodetrue;
        newNode->right = NULL;
        newNode->left = NULL;
    }
    else if ((is_number(root->condition_false) && !is_number(root->condition_true))|| (!is_number(root->condition_false) && is_number(root->condition_true))) {
        if (is_number(root->condition_false)) {
            root->left = addElement(root->left, nodeindex, variable1, logic, variable2, nodefalse, nodetrue);
        }

        if (is_number(root->condition_true)) {
            root->right = addElement(root->right, nodeindex, variable1, logic, variable2, nodefalse, nodetrue);
        }
    }

    else {
        if (root->condition_false==nodeindex) {
            root->left = addElement(root->left, nodeindex, variable1, logic, variable2, nodefalse, nodetrue);
        }

        if (root->condition_true==nodeindex) {
            root->right = addElement(root->right, nodeindex, variable1, logic, variable2, nodefalse, nodetrue);
        }
    }
    return root;
}



void makedecision(node* root, vector<string> labels, vector<string> inputdata, vector<string>& decisions) {



    string var1 = root->var1;
    bool condition = false;
    int i = 0;
    while (i < labels.size()) {
        if (labels[i] == var1) {
            break;
        }
        else i++;
    }
    string data = inputdata[i];


    if (root->logic == ">") {
        if (stof(data) > root->var2) {
            condition = true;
        }
        else condition = false;
    }
    else if (root->logic == "<") {
        if (stof(data) < root->var2) {
            condition = true;
        }
        else {
            condition = false;
        }
    }

    if (condition) {
        if (root->right != NULL) {
            root = root->right;
            makedecision(root, labels, inputdata, decisions);
        }
        else {
            decisions.push_back(root->condition_true);
        }
    }
    else {
        if (root->left != NULL) {
            root = root->left;
            makedecision(root, labels, inputdata, decisions);
        }
        else {
            decisions.push_back(root->condition_false);
        }
    }
}

void remove(vector<string>& v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = remove(it + 1, end, *it);
    }
    v.erase(end, v.end());
}

void generateOutput(vector<vector<string>>& inputdata, string output, vector<string>& DecisionLabels) {
    int pos = (inputdata[1].size() - 1);
    ofstream OutputFile(output);
    if (!OutputFile.is_open()) {
        cout << "Failed creating a file for output" << endl;
    }
    for (int i = 0; i < DecisionLabels.size(); i++) {
        OutputFile << DecisionLabels[i] << ":" << endl;
        for (int j = 1; j < inputdata.size(); j++) {
            if (inputdata[j][pos] == DecisionLabels[i]) {

                for (int k = 0; k < pos; k++) {
                    OutputFile << inputdata[j][k] << "  ";
                }
                OutputFile << endl;
            }
        }
        OutputFile << endl;
    }
    OutputFile.close();
}

node* deleteTree(node* root) {

    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);


        delete root;
        root = NULL;
        return root;
    }
    else return 0;
}