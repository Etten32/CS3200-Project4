//J+M+J
#include "AVLTree.h"

// creates a blank tree
AVLTree::AVLTree(){
    root = nullptr;
    numElts = 0;
}                                 

// creates a deep copied tree
AVLTree::AVLTree(AVLTree& original){
    // recursively go through the original tree adding all nodes that aren't nullptr
    // pass a pointer to 'this', so each case can add itself (the node the methods on) to the tree using insert
}    

// deconstructs tree
AVLTree::~AVLTree(){
    deleteTree(root);
}                                

// returns height (highest height of root)
int AVLTree::getHeight(){
    if(numElts > 0) return root->leftHeight >= root->rightHeight ? root->leftHeight: root->rightHeight; // return the heigher of the two heights in the root
    //                                                                                                     asistance from this site to format ternary operator: 
    //                                                                                                     https://www.programiz.com/cpp-programming/ternary-operator
    return 0; // if tree has no nodes
}                           

// returns size (numElts)
int AVLTree::getSize(){
    return numElts;
}                             

// finds key and puts it into value or returns false
bool AVLTree::find(int key, string& value){
    
    return helpFind(key, value, root); //** VALUE& NOT VALID WAY TO PASS... WILL NOT WORK!!! (FIX NEEDED!)
}         

// finds range of keys and puts them into the vector
vector<string> AVLTree::findRange(){
    vector<string> additiveBuffer = vector<string>();          // to hold all found values
    string toAdd = "";                                         // to hold string returned from find()
    for(int i = 0; i < this->numElts; i++){
        if(find(i,toAdd)) additiveBuffer.push_back(toAdd);
    }
    return additiveBuffer;

}        

bool AVLTree::insert(int key, string value){
    if(insertNode(key, value, this->root)){
        this->numElts++;
        return true;
    }
    return false;
}

// prints out AVLTree
/*
ostream& AVLTree::operator<<(ostream& os, const AVLTree& me){

}*/