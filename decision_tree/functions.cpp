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

void readLine(node*& root, string line)
{
    string variable1, logic, nodefalse, nodetrue;
    float variable2=0;
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
                counter++;
                break;
            }
            case 6:
            {
                nodetrue = word;
                counter = 1;
                break;
            }
            }
        }
    }
  root = addElement(root, nodeindex,variable1,logic,variable2,nodefalse,nodetrue);
}


node* addElement(node* root, string nodeindex, string variable1, string logic, float variable2, string nodefalse, string nodetrue) {
    if (root == NULL) {
        node* newNode = new node;
        root = newNode;
        newNode->key = stoi(nodeindex);
        newNode->var1 = variable1;
        newNode->logic = logic;
        newNode->var2 = variable2;
        newNode->condition_false = nodefalse;
        newNode->condition_true = nodetrue;
        newNode->right = NULL;
        newNode->left = NULL;
    }

    else if(nodeindex==root->condition_false){
        root->left = addElement(root->left, nodeindex, variable1, logic, variable2, nodefalse, nodetrue);
    }

    else if (nodeindex == root->condition_true) {
        root->right = addElement(root->right, nodeindex, variable1, logic, variable2, nodefalse, nodetrue);
    }

    else {
        cout << "Something's wrong I can feel it ~Eminem" << endl;
    }
    return root;
}

void makedecision(node*root, vector<string> labels, vector<string> inputdata) {
   
   
    // if (root->left == NULL && root->right == NULL) {
   //     cout << root->condition_true << endl;
  //  }
 //   else {
        string var1 = root->var1;
        bool condition=false;
        int i = 0;
        while (i < labels.size()) {
            if (labels[i] == var1) {
                break;
            }
            else i++;
        }
        string data=inputdata[i];

        addtoVector(data);

        if (root->logic == ">") {
            if (stof(data) > root->var2) {
                condition = false;
            }
            else condition = true;
        }
        else if (root->logic == "<") {
            if (stof(data) < root->var2) {
                condition = false;
            }
            else  {
                condition = true;
            }
        }

        if (condition == true) {
            if (root->right != NULL) {
                root = root->right;
                makedecision(root, labels, inputdata);
            }
            else {
                cout << root->condition_true << endl;
                addtoVector(root->condition_true);
            }
        }
        else if (condition==false) {
            if (root->left != NULL) {
                root = root->left;
                makedecision(root, labels, inputdata);
            }
            else {
                cout << root->condition_false << endl;
               // return root->condition_false;
            }
    //    }
    }
}

node* deleteTree(node* root){

    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);


        delete root;
        root = NULL;
        return root;
    }
}
