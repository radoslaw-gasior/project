#ifndef STRUCTURES_H
#define STRUCTURES_H

struct node
{
    int key;
    std::string  var1;
    std::string logic;
    float var2;
    std::string condition_true;
    std::string condition_false;
    struct node* left, * right;
};


#endif