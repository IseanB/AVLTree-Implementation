#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

struct Node{
    string data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    Node(string inputData): data(inputData), left(nullptr), right(nullptr), parent(nullptr), height(0){}
    //height 0 since all leafs have height of 0
};
#endif