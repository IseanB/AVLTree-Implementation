#include "AVLTree.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// ostringstream outputAll;

void AVLTree::printEverything(Node* insertNode){
    if(insertNode){//currnode != nullptr
        // printEverything(insertNode->left);
        // cout << "Node: " << insertNode->data << endl;
        // string parentData = "null parent";
        // if(insertNode->parent){
        //     parentData = insertNode->parent->data;
        // }
        // string leftData = "null left";
        // if(insertNode->left){
        //     leftData = insertNode->left->data;
        // }
        // string rightData = "null right";
        // if(insertNode->right){
        //     rightData = insertNode->right->data;
        // }
        // cout << "Node Height: " << insertNode->height << endl;
        // cout << "Node Parent: " << parentData << endl;
        // cout << "Node Left Child: " << leftData << endl;
        // cout << "Node right Child: " << rightData << endl;
        // cout << endl;
        // printEverything(insertNode->right);
    }
}

/*Insert an item to the binary search tree and perform rotation if necessary.*/
//update heights of parents till root
//finds unbalancednode and roatates()
void AVLTree::updateHeights(Node* unBalNode){
    //update heights
    while(unBalNode){
        // cout << "Before Updated Height of " << unBalNode->data << "is " << unBalNode->height << endl;
        int lHeight = -1;
        int rHeight = -1;
        if(unBalNode->left){
            lHeight = unBalNode->left->height;
        }
        if(unBalNode->right){
            rHeight = unBalNode->right->height;
        }
        unBalNode->height = (1 + max(lHeight, rHeight));
        // cout << "After Updated Height of " << unBalNode->data << " is " << unBalNode->height << endl;
        unBalNode = unBalNode->parent;
    }
}

void AVLTree::insert(const string &inputData){
    Node* insertNode = new Node(inputData);
    if(root == nullptr){//empty tree
        root = insertNode;
        // cout << "Empty Tree" << endl;
    }
    else{//not empty tree

        //bst insert
        Node* currNode = root;
        bool done = false;
        while(currNode && !done){
            if(currNode->data > inputData){
                if(currNode->left == nullptr){
                    currNode->left = insertNode;
                    insertNode->parent = currNode;
                    done = true;
                }
                else{
                    currNode = currNode->left;
                }
            }                                       
            else if(currNode->data < inputData){
                if(currNode->right == nullptr){
                    currNode->right = insertNode;
                    insertNode->parent = currNode;
                    done = true;
                }
                else{
                    currNode = currNode->right;
                }
            }
            else{
                return;
            }
        }
        updateHeights(insertNode);
        // cout << "After Update Height" << endl;
        // printEverything(root);
        // cout << "After Update Height2" << endl;
        //     // /////////////////////////////////////
            // cout << endl;
            // cout << "Before Rotation Inserted: " << inputData << endl;
            // string parentData = "null parent";
            // if(insertNode->parent){
            //     parentData = insertNode->parent->data;
            // }
            // string leftData = "null left";
            // if(insertNode->left){
            //     leftData = insertNode->left->data;
            // }
            // string rightData = "null right";
            // if(insertNode->right){
            //     parentData = insertNode->right->data;
            // }  
            // cout << "Inserted Parent: " << parentData << endl;
            // cout << "Inserted Left Child: " << leftData << endl;
            // cout << "Inserted right Child: " << rightData << endl;
            // cout << endl;
            // ////////////////////////////
        //check for imbalence once
        Node* unBalNode = findUnbalancedNode(insertNode); 
        // Node* updateMe = insertNode;
        // if(balanceFactor(unBalNode)>0){//is right heavy
        //     updateMe = insertNode->parent;
        // }
        if(unBalNode != nullptr){//found unbalanced node
            // cout << "Imbalance Detected at " << insertNode->data << endl << endl;
            rotate(unBalNode);
        }
        else{
            // cout << "No imbalance" << endl;
        }
            // /////////////////////////////////////
            // cout << endl;
            // cout << "After Rotation Inserted: " << inputData << endl;
            // parentData = "null parent";
            // if(insertNode->parent){
            //     parentData = insertNode->parent->data;
            // }
            // leftData = "null left";
            // if(insertNode->left){
            //     leftData = insertNode->left->data;
            // }
            // rightData = "null right";
            // if(insertNode->right){
            //     parentData = insertNode->right->data;
            // }
            // cout << "Inserted Parent: " << parentData << endl;
            // cout << "Inserted Left Child: " << leftData << endl;
            // cout << "Inserted right Child: " << rightData << endl;
            // cout << endl;
            // ////////////////////////////
        
        updateHeights(insertNode->left);
        updateHeights(insertNode->right);
        updateHeights(insertNode);
    }
}
/*Return the balance factor of a given node. <0 mean right heavy, >0 mean left heavy*/
int AVLTree::balanceFactor(Node* nodeUsed){
    int lHeight = -1;
    if(nodeUsed->left != nullptr){
        lHeight = nodeUsed->left->height;
    }
    int rHeight = -1;
    if(nodeUsed->right != nullptr){
        rHeight = nodeUsed->right->height;
    }
    return lHeight - rHeight;
}
/*Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.*/
void AVLTree::printBalanceFactors(){
    // printEverything(root);
    // cout << endl;
    // printEverything(root);
    printBalanceFactors(root);
    cout << endl;
} 

//---------------------------Private Helper Functions Below---------------------------
/* Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.*/
Node* AVLTree::findUnbalancedNode(Node* currNode){//first time called the inserted node is currNode
    if(currNode){//curnnode != nullptr, or root Node
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
    // cout << this->balanceFactor(currNode);
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
    //set up all parts needed to rotate
    // cout << "LR Called" << endl;
    Node* xNode = yNode->right;
    Node* bSubTree = nullptr;
    Node* cSubTree = nullptr;
    if(yNode->left){
        cSubTree = yNode->left;
    }
    bSubTree = xNode->left;
    
    //LL rotation below
    Node* tempYParent = yNode->parent;
        //Properly move B Subtree
    yNode->right = bSubTree;
    if(bSubTree){
        bSubTree->parent = yNode;
    }
        //properly move/update xNode to be top
    xNode->left = yNode;
    yNode->parent = xNode;

    //updates parent
    xNode->parent = tempYParent;
    if(tempYParent){//tests if not root
        if(tempYParent->left == yNode){//yNode is left child?
            tempYParent->left = xNode;
        }
        else{
            tempYParent->right = xNode;
        }
    }
    else{
        // cout << "Updated Height LR";
        // cout << xNode->data << endl;
        root = xNode;
    }
    //update yNode height
    int bSubHeight = -1;
    int cSubHeight = -1;
    if(bSubTree){
        bSubHeight = bSubTree->height;
    }
    if(cSubTree){
        cSubHeight = cSubTree->height;
    }
    yNode->height = 1 + max(bSubHeight, cSubHeight);
    return xNode;
}

/* Rotate the subtree to right at the given node and returns the new subroot.*/
Node* AVLTree::rotateRight(Node* yNode){//assume yNode and xNode exists
    //set up all parts needed to rotate
    // cout << "RR Called" << endl;
    Node* xNode = yNode->left;
    Node* bSubTree = nullptr;
    bSubTree = xNode->right;
    Node* cSubTree = nullptr;
    if(yNode->right){
        cSubTree = yNode->right;
    }
    //RR  rotation below
    Node* tempYParent = yNode->parent;
        //Properly move B Subtree
    yNode->left = bSubTree;
    if(bSubTree){
        bSubTree->parent = yNode;
    }
        //properly move/update xNode to be top
    xNode->right = yNode;
    yNode->parent = xNode;
    

    xNode->parent = tempYParent;
    if(tempYParent){//tests if not nullptr, or if yNode was root
        if(tempYParent->left == yNode){//xNode is left child of parent
            tempYParent->left = xNode;
        }
        else{
            tempYParent->right = xNode;
        }
    }
    else{
        // cout << "Updated Height RR";
        // cout << xNode->data << endl;
        root = xNode;
    }

    //update yNode height
    int bSubHeight = -1;
    int cSubHeight = -1;
    if(bSubTree){
        bSubHeight = bSubTree->height;
    }
    if(cSubTree){
        cSubHeight = cSubTree->height;
    }
    yNode->height = 1 + max(bSubHeight, cSubHeight);
    return xNode;
}

void AVLTree::printBalanceFactors(Node* currNode){
    if(currNode){//currnode != nullptr
        printBalanceFactors(currNode->left);
        cout << currNode->data << "(" << balanceFactor(currNode) << "), ";
        printBalanceFactors(currNode->right);
    }
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
