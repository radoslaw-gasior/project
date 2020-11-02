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