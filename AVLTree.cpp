//J+M+J
#include "AVLTree.h"

// creates a blank tree
AVLTree::AVLTree(){
    root = nullptr;
    numElts = 0;
}                                 

// creates a deep copied tree
AVLTree::AVLTree(AVLTree& original){
    // set up initials
    root = nullptr;
    numElts = 0;
    // recursively go through the original tree adding all nodes that aren't nullptr
    this->makeTree(original.root);
}    
/* 
//* DEPRECATED
// Adds all nodes in subtree of AVLTree::helpMake().nodeAt inclusive to AVLTree::helpMake().treeToAdd
void AVLTree::helpMake(TreeNode* nodeAt, AVLTree* treeToAdd){
        //*base case: if node is null
        if(nodeAt == nullptr) return;

        //*recursive case: if node is not null
            //first add copy of self
        treeToAdd->insert(nodeAt->key, nodeAt->elt);
            //second add right
        helpMake(nodeAt->right, treeToAdd);
            //third print left
        helpMake(nodeAt->left, treeToAdd);
}
//*/

// deconstructs tree
AVLTree::~AVLTree(){
    clearTree(root);
}                                


// returns height (highest height of root)
int AVLTree::getHeight(){
    if(numElts > 0) return root->getHeight();
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

bool AVLTree::testRotate(int key, char shift){
    return testRotate(key, this->root, shift);
}

bool AVLTree::testRotate(int key, TreeNode* nodeAt, char shift){
        //*base case 0: if node is null
        if(nodeAt == nullptr) return false;

        //*base case 1: if key is found
        if(nodeAt->key == key){
            if(shift == 'r') return rightRotate(nodeAt);
            else if(shift == 'l') return leftRotate(nodeAt);
            else if(shift == 'R') return doubleRightR(nodeAt);
            else if(shift == 'L') return doubleLeftR(nodeAt);
            else return false;
        }

        //*recursive case: call helpFind() on appropriate pointer
        if(nodeAt->key < key) return testRotate(key, nodeAt->right, shift); // if value in node is less than key (so node to find would be in right subtree)
        else return testRotate(key, nodeAt->left, shift);
}

// makes a single right rotate at node
bool AVLTree::rightRotate(TreeNode* toRotate){
    if(toRotate == nullptr || toRotate->left == nullptr) return false;
    
    TreeNode* hook = toRotate->left;
    TreeNode* clip = hook->right;       // temp storage
    // if node to rotate at is the root
    if(toRotate->key == this->root->key){
        if(clip != nullptr) hook->unlinkRight();
        toRotate->unlinkLeft(); 
        hook->linkRight(toRotate);
        if(clip != nullptr) toRotate->linkLeft(clip);
        this->root = hook;
    }
    else{
        // if node to rotate ins't the root
        TreeNode* parent = toRotate->parent;

        if(clip != nullptr) hook->unlinkRight(); 
        toRotate->unlinkLeft(); 
        hook->linkRight(toRotate);
        if(clip != nullptr) toRotate->linkLeft(clip);
        parent->replacePointerWith(toRotate, hook); // replace old parents left or right * with a * to hook
    }
    // recalculate changed heights
    toRotate->recalculateHeight();
    hook->recalculateHeight();
    return true;
}                                          

// makes a double left rotate at node
bool AVLTree::doubleRightR(TreeNode* toRotate){
    return leftRotate(toRotate->left) && rightRotate(toRotate);
}                                         

// makes a single left rotate at node
bool AVLTree::leftRotate(TreeNode* toRotate){
    if(toRotate == nullptr || toRotate->right == nullptr) return false;
    
    TreeNode* hook = toRotate->right;   // hook node
    TreeNode* clip = hook->left;        // temp storage
    // if node to rotate at is the root
    if(toRotate->key == this->root->key){
        if(clip != nullptr) hook->unlinkLeft();
        toRotate->unlinkRight(); 
        hook->linkLeft(toRotate);
        if(clip != nullptr) toRotate->linkRight(clip);
        this->root = hook;
    }
    else{
        // if node to rotate isn't the root
        TreeNode* parent = toRotate->parent;

        if(clip != nullptr) hook->unlinkLeft();
        toRotate->unlinkRight(); 
        hook->linkLeft(toRotate);
        if(clip != nullptr) toRotate->linkRight(clip);
        parent->replacePointerWith(toRotate, hook);
    }
    // recalculate changed heights after insert / rotation
    toRotate->recalculateHeight();
    hook->recalculateHeight();
    return true;
}                                          

// makes a double left rotate at node
bool AVLTree::doubleLeftR(TreeNode* toRotate){
    return rightRotate(toRotate->right) && leftRotate(toRotate);
} 

// make one AVLTree equal to the other (this <-equal-to-< toTransfer)
AVLTree& AVLTree::operator=( const AVLTree& toTransfer ){
    // clear whatever is there first
    this->clearTree(this->root->left);
    this->clearTree(this->root->right);

    TreeNode* toDelete = this->root;
    this->root = nullptr;
    this->numElts--;

    // copy over from toTransfer
    this->makeTree(toTransfer.root);

    delete(toDelete);

    return (*this);

}

// prints out AVLTree
ostream& operator<<(ostream& os, const AVLTree& me){
    return me.helpPrint(os, me.root, 0);
}

// recursive function to print out AVLTree
ostream& AVLTree::helpPrint(ostream& os, TreeNode* nodeAt, int level) const{
        //*base case: if node is null
        if(nodeAt == nullptr) return os;

        //*recursive case: if node is not null
            //first print right
        helpPrint(os, nodeAt->right, level + 1);
            //second print self
        for(int i = 0; i < level; i++) os << "     ";
        os << nodeAt->key << ", " << nodeAt->elt << /*" H = " << nodeAt->getHeight() << " B = " << nodeAt->leftHeight - nodeAt->rightHeight << */endl;
            //third print left
        return helpPrint(os, nodeAt->left, level + 1);
    }

// recursive function to insert a node (includes balancing)
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
                // recalculate heights after a node has been inserted
                nodeAt->recalculateHeight();
                //check if left rotations are needed (-2)
                if(nodeAt->getBalance() == -2){
                    if(nodeAt->right->getBalance() > 0) doubleLeftR(nodeAt); // if it needs a double rotation
                    else leftRotate(nodeAt); // otherwise it needs a single rotation
                }
                nodeAt->recalculateHeight();
                return true;
            }
        }
            
            // go to left
        else{
            if(insertNode(key, value, nodeAt->left)){
                // recalculate heights after a node has been inserted
                nodeAt->recalculateHeight();
                //check if right rotations are needed (2)
                if(nodeAt->getBalance() == 2){
                    if(nodeAt->left->getBalance() < 0) doubleRightR(nodeAt); // if it needs a double rotation
                    else rightRotate(nodeAt); // otherwise it needs a single rotation
                }
                nodeAt->recalculateHeight();
                return true;
            }
        }
        return false;
    }

// recursive function to delete nodes
void AVLTree::clearTree(TreeNode* nodeAt){
        //*base case: if node is null
        if(nodeAt == nullptr) return;

        //*recursive case: if node is not null call deleteTree on right and left subtrees
        this->clearTree(nodeAt->right);
        this->clearTree(nodeAt->left);
        delete(nodeAt);
        this->numElts--;
    }

// recursively inserts from a given node into this tree
void AVLTree::makeTree(TreeNode* nodeAt){
        //*base case: if node is null
        if(nodeAt == nullptr) return;

        //*recursive case: add subtrees and itself to tree
        this->insert(nodeAt->key, nodeAt->elt);
        makeTree(nodeAt->left);
        makeTree(nodeAt->right);
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


