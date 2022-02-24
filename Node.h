#ifndef NODE_H
#define NODE_H
#include <string>

struct Node{
    std::string data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    Node(std::string inputData) : data(inputData), left(nullptr), right(nullptr), parent(nullptr), height(0){}
    //height 0 since all leafs have height of 0
};
#endif