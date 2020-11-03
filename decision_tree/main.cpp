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
    InputFile.close();


    cout << inputdata[1][0] <<" "<<inputdata.size()<< endl; // read testing purposes

    

    cout << input << definition << output;



    return 0;
}