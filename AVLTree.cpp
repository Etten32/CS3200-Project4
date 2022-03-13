//J+M+J
#include "AVLTree.h"

// creates a blank tree
AVLTree::AVLTree(){
    root = nullptr;
    numElts = 0;
}                                 
/*// ----------------------------------------------------------------------------   FIX HERE!
// creates a deep copied tree
AVLTree::AVLTree(AVLTree& original){
    // recursively go through the original tree adding all nodes that aren't nullptr
    vector<TreeNode>* listToAdd = new vector<TreeNode>();
    helpMake(original.root, listToAdd);

    // add all node copy's values into 'this' (the new tree)
    for(int i = 0; i < listToAdd->size(); i++) this->insert(listToAdd[i].key, listToAdd[i].elt);
    delete(listToAdd);
}    

void AVLTree::helpMake(TreeNode* nodeAt, vector<TreeNode>* listToAdd){
        //*base case: if node is null
        if(nodeAt == nullptr) return;

        //*recursive case: if node is not null
            //first add right
        helpMake(nodeAt->right, listToAdd);
            //second add copy of self
        listToAdd->push_back(*nodeAt);
            //third print left
        helpMake(nodeAt->left, listToAdd);
}
*/
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
vector<string> AVLTree::findRange(int lowKey, int highKey){
    vector<string> additiveBuffer = vector<string>();          // to hold all found values
    string toAdd = "";                                         // to hold string returned from find()
    for(int i = lowKey; i <= highKey; i++){
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

ostream& operator<<(ostream& os, const AVLTree& me){
    return me.helpPrint(os, me.root, 0);
}

ostream& AVLTree::helpPrint(ostream& os, TreeNode* nodeAt, int level) const{
        //*base case: if node is null
        if(nodeAt == nullptr) return os;

        //*recursive case: if node is not null
            //first print right
        helpPrint(os, nodeAt->right, level + 1);
            //second print self
        for(int i = 0; i < level; i++) os << "     ";
        os << nodeAt->key << ", " << nodeAt->elt << endl;
            //third print left
        return helpPrint(os, nodeAt->left, level + 1);
    }


    bool AVLTree::insertNode(int key, string value, TreeNode*& nodeAt){
        //*base case 0: node (and tree) is empty
        if(nodeAt == nullptr){
            nodeAt = new TreeNode(key, value);
            return true;
        }

        //*base case 1: matching key is met
        if(nodeAt->key == key) return false;

        //*base case 2: next node == nullptr and node can be inserted
            // add at right
        if(nodeAt->key < key && nodeAt->right == nullptr){
            nodeAt->linkRight(new TreeNode(key, value));
            nodeAt->rightHeight = 1;
            return true;
        }
            // add at left
        if(nodeAt->key > key && nodeAt->left == nullptr){
            nodeAt->linkLeft(new TreeNode(key, value));
            nodeAt->leftHeight = 1;
            return true;
        }

        //*base case 2: logic error occured!!
        if(nodeAt->left == nullptr && nodeAt->right == nullptr) return false;

        //*recursive case: else keep going till the right place is reached
            // go to right
        if(nodeAt->key < key){
            if(insertNode(key, value, nodeAt->right)){
                // assign right height to the greater of the right nodes heights heights + 1
                nodeAt->rightHeight = (nodeAt->right->leftHeight >= nodeAt->right->rightHeight ? nodeAt->right->leftHeight: nodeAt->right->rightHeight) + 1;
                return true;
            }
        }
            
            // go to left
        else{
            if(insertNode(key, value, nodeAt->left)){
                // assign left height to the greater of the left nodes heights heights + 1
                nodeAt->leftHeight = (nodeAt->left->leftHeight >= nodeAt->left->rightHeight ? nodeAt->left->leftHeight: nodeAt->left->rightHeight) + 1;
                return true;
            }
        }
        return false;
    }

    // recursive function to delete nodes
    void AVLTree::deleteTree(TreeNode* nodeAt){
        //*base case: if node is null
        if(nodeAt == nullptr) return;

        //*recursive case: if node is not null call deleteTree on right and left subtrees
        deleteTree(nodeAt->right);
        deleteTree(nodeAt->left);
        delete(nodeAt);
    }

    // recursive function to help find node
    bool AVLTree::helpFind(int key, string& value, TreeNode* nodeAt){
        //*base case 0: if node is null
        if(nodeAt == nullptr) return false;

        //*base case 1: if key is found
        if(nodeAt->key == key){
            value = nodeAt->elt;
            return true;
        }

        //*recursive case: call helpFind() on appropriate pointer
        if(nodeAt->key < key) return helpFind(key, value, nodeAt->right); // if value in node is less than key (so node to find would be in right subtree)
        else return helpFind(key, value, nodeAt->left); // if value in node is greater than key (so node to find would be in left subtree)
    }     
	

