#ifndef AVLTREE_H
#define AVLTREE_H
#include "Node.h"
#include <fstream>
#include <string>

class AVLTree{
    private:
        Node* root;
    public:
        AVLTree(): root(nullptr){}//++++++
        /*Insert an item to the binary search tree and perform rotation if necessary.*/
        void insert(const std::string &);//
        /*Return the balance factor of a given node.*/
        int balanceFactor(Node*);//++++++++++
        /*Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.*/
        void printBalanceFactors(); //+++++++++
        /* Generate dotty file and visualize the tree using dotty program. Call this function before and after rotation.*/
        void visualizeTree(const std::string &);//=====
    private:
        /* Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.*/
        Node* findUnbalancedNode(Node*);//++++++++++
        void updateHeights(Node*);//
        void rotate(Node*);//++++++++++
        Node* rotateLeft(Node*);//+++++++
        Node* rotateRight(Node*);//+++++++++
        void printBalanceFactors(Node*);//++++++++++
        void visualizeTree(std::ofstream &, Node*);//======
        void printEverything(Node*);
};
#endif