#ifndef STRUCTURES_H
#define STRUCTURES_H
#include<tuple>
using namespace std;


struct Definition
{
    int node_index;
    int index_false;
    int index_true;
};

struct node
{
    int key;
    string  var1;
    string logic;
    float var2;
    string condition_true;
    string condition_false;
    struct node* left, * right;


};


#endif