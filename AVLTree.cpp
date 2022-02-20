#include "AVLTree.h"
#include <fstream>
#include <string>
#include <iostream>


using namespace std;

/*Insert an item to the binary search tree and perform rotation if necessary.*/
//update heights of parents till root
//finds unbalancednode and roatates()
void AVLTree::insert(const string &inputData){
    Node* insertNode = new Node(inputData);
    if(root == nullptr){//empty list
        root = insertNode;
    }
    else{//not empty list
        //use balence factor to insert in left or right
    }
}
/*Return the balance factor of a given node. <0 mean right heavy, >0 mean left heavy*/
int AVLTree::balanceFactor(Node* nodeUsed){
    if(nodeUsed == nullptr){//inputed nullptr node
        return 0;
    }
    Node* lNode = nodeUsed->left;
    Node* rNode = nodeUsed->right;
    if(lNode){// yes lchild and ??? rchild
        if(rNode){// yes lchild and yes rchild-----------
            return lNode->height - rNode->height;
        }
        else{// yes lchild and no rchild------------
            return lNode->height + 1;
        }
    }
    else{//no lchild and ?? rchild
        if(rNode){//no lchild but yes rchild----------
            return -1 - rNode->height;
        }
        else{//no lchild and no rchild-----------
            return 0;// ( (-1) - (-1) ) = 0
        }
    }
}
/*Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.*/
void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
} 

//---------------------------Private Helper Functions Below---------------------------
/* Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.*/
Node* AVLTree::findUnbalancedNode(Node* currNode){//first time called the inserted node is currNode
    if(currNode){//curnnode != nullptr
        if(abs(balanceFactor(currNode)) >1 ){//node violates bf property
            return currNode;        
        }
        else{
            return findUnbalancedNode(currNode->parent);
        }
    }
}

/*Implement four possible imbalance cases and update the parent of the given node.*/
void AVLTree::rotate(Node* currNode){

}

/* Rotate the subtree to left at the given node and returns the new subroot.*/
Node* AVLTree::rotateLeft(Node* yNode){//assume yNode exists
    Node* xNode = yNode->right;
    Node* aSubTree = nullptr;
    if(xNode){//can access xNode
        aSubTree = xNode->left;
    }

    //LL rotation below
    Node* tempYParent = yNode->parent;

    yNode->right = aSubTree;
    if(aSubTree){
        aSubTree->parent = yNode;
    }

    xNode->left = yNode;
    yNode->parent = xNode;

    xNode->parent = tempYParent;
    if(tempYParent){//tests if not root
        if(xNode->data <= tempYParent->data){//xNode is left child of parent
            tempYParent->left = xNode;
        }
        else{
            tempYParent->right = xNode;
        }
    }
}

/* Rotate the subtree to right at the given node and returns the new subroot.*/
Node* AVLTree::rotateRight(Node* yNode){//assume yNode and xNode exists
    //set up all parts needed to rotate
    Node* xNode = yNode->left;
    Node* bSubTree = nullptr;
    if(xNode){//can access xNode
        bSubTree = xNode->right;
    }

    //RR  rotation below
    Node* tempYParent = yNode->parent;
    yNode->left = bSubTree;
    if(bSubTree){
        bSubTree->parent = yNode;
    }

    xNode->right = yNode;
    yNode->parent = xNode;
    
    
    xNode->parent = tempYParent;
    if(tempYParent){//tests if not root
        if(xNode->data <= tempYParent->data){//xNode is left child of parent
            tempYParent->left = xNode;
        }
        else{
            tempYParent->right = xNode;
        }
    }    
}

void AVLTree::printBalanceFactors(Node* currNode){
    if(currNode){//currnode != nullptr
        printBalanceFactors(currNode->left);
        cout << currNode->data << "(" << balanceFactor(currNode) << "), ";
        printBalanceFactors(currNode->right);
    }
}


void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}