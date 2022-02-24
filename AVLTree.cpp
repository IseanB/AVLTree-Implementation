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
    if(root == nullptr){//empty tree
        root = insertNode;
    }
    else{//not empty tree
        //bst insert
        Node* currNode = root;
        while(currNode){
            if(currNode->data > inputData){
                if(currNode->left == nullptr){
                    insertNode->parent = currNode;
                    currNode->left = insertNode;
                    currNode = nullptr;
                }
                else{
                    currNode = currNode->left;
                }
            }                                       
            else{
                if(currNode->right == nullptr){
                    insertNode->parent = currNode;
                    currNode->right = insertNode;
                    currNode = nullptr;
                }
                else{
                    currNode = currNode->right;
                }
            }
        }
        //check for imbalence
        if(findUnbalancedNode(insertNode) != nullptr){
            rotate(findUnbalancedNode(insertNode));
        }
        //update heights
        currNode = insertNode->parent;
        int currHeight = currNode->height;
        while(currNode){
            cout << "Updated " << currNode->data << "to " << currHeight + 1 << endl;
            currNode->height = currHeight + 1;
            ++currHeight;
            currNode = currNode->parent;
        }
    }
}
/*Return the balance factor of a given node. <0 mean right heavy, >0 mean left heavy*/
int AVLTree::balanceFactor(Node* nodeUsed){
    int lHeight = -1;
    if(nodeUsed->left){
        lHeight = nodeUsed->left->height;
    }
    int rHeight = -1;
    if(nodeUsed->right){
        rHeight = nodeUsed->right->height;
    }
    return lHeight - rHeight;
}
/*Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.*/
void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
} 

//---------------------------Private Helper Functions Below---------------------------
/* Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.*/
Node* AVLTree::findUnbalancedNode(Node* currNode){//first time called the inserted node is currNode
    if(currNode){//curnnode != nullptr
        int bfactor = balanceFactor(currNode); 
        if(bfactor > 1 || bfactor < -1){//node violates bf property
            return currNode;        
        }
        else{
            return findUnbalancedNode(currNode->parent);
        }
    }
    return nullptr;
}

/*Implement four possible imbalance cases and update the parent of the given node.*/
void AVLTree::rotate(Node* currNode){//assume currNode is unbalenced with either -2 or 2
    if(currNode == nullptr){
        return;
    }
    cout << this->balanceFactor(currNode);
    if(this->balanceFactor(currNode)==2){
        if(this->balanceFactor(currNode->left) < 0){// LL then RR
            rotateLeft(currNode->left);
            rotateRight(currNode);
        }
        else{// RR
            rotateRight(currNode);
        }
    }
    else if(this->balanceFactor(currNode)==-2){//right heavy heavy
        if(this->balanceFactor(currNode->right) > 0){// RR then LL
            rotateRight(currNode->right);
            rotateLeft(currNode);
        }
        else{// LL
            rotateLeft(currNode);
        }
    }
    else{
        cout << endl << "Error Balancing Factor Calculation" << endl;
    }
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
    return xNode;
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
    return xNode;
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