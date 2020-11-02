#include <iostream>
#include <fstream>
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


    cout << input << definition << output;



    return 0;
}