//J+M+J
/** FILE: AVLTree.h
// CLASS:PROVIDED: AVLTree
//
// *v*v*v*v* PUBLIC: *v*v*v*v*
// CONSTRUCTORS:
//  AVLTree::AVLTree()
//      Postcondition: Creates an empty tree 
//                     sets AVLTree::numElts = 0
//
//  AVLTree::AVLTree(AVLTree& original)
//      Postcondition: Creates a deep copy of AVLTree::AVLTree().original AVLTree
//
// DESTRUCTOR:
//  ~AVLTree()
//      Postcondition: recursively deletes all nodes
//
// INFORMATION:FUNCTIONS:
//  int AVLTree::getHeight()
//      Postcondition: condition-0 (no nodes present) = returns 0
//                     condition-1 (nodes present) = returns the height of the AVLTree by getting the higher of 
//                                                   the two heights of the root node
//
//  int AVLTree::getSize()
//      Postcondition: return the size of the AVLTree (total number of nodes)
//                     returns AVLTree::numElts
//
//  bool AVLTree::find(int key, string& value)
//      Predcondition: AVLTree::find().value contains an empty string reference to copy the value to once found
//      Postcondition: condition-0 = returns false if item is not found and AVLTree::find().value is left empty
//                     condition-1 = returns true if item is found and AVLTree::find().value contains value
//
//  vector<string> AVLTree::findRange(int lowKey, int highKey)
//      Postcondition: returns vector containing all values with key pair within the range of
//                     AVLTree::findRange().lowkey and AVLTree::findRange().lowkey inclusively
//
// MUTATION:FUNCTIONS:
//  bool AVLTree::insert(int key, string value)
//      Postcondition: condition-0 = returns false if item error occcured or key was already inserted
//                     condition-1 = returns true if insert was correct
//
// FREINDS:
// freind ostream& operator<<(ostream& os, const AVLTree& me)
//      Postcondition: prints out tree to AVLTree::operator<<().os and returns it
//
// *v*v*v*v* PRIVATE: *v*v*v*v*
// INFORMATION:FUNCTIONS:
//  bool AVLTree::helpFind(int key, string& value, TreeNode nodeAt)
//      Postcondition: condition-0 = returns false if key was not found in this or any sub-branches and 
//                                   AVLTree::find().value is left empty
//                     condition-1 = returns true if key was found in this or any sub-branch and 
//                                   AVLTree::find().value contains value
//
//  void deleteTree(TreeNode* nodeAt)
//      Postcondition: condition-0 = returns if AVLTree::deleteTree().nodeAt == nullptr
//                     condition-1 = calls AVLTree::deleteTree() on AVLTree::deleteTree().nodeAt->left and 
//                                   AVLTree::deleteTree().nodeAt->right children and then deletes 
//                                   AVLTree::deleteTree().nodeAt
**/

#include <iostream>
#include <vector>

using namespace std;

class AVLTree {
    private:
        class TreeNode;

    public:
        AVLTree();                                                  // creates a blank tree

        AVLTree(AVLTree& original);                                 // creates a deep copied tree

        void helpMake(TreeNode* nodeAt, vector<TreeNode>* listToAdd);

        ~AVLTree();                                                 // deconstructs tree

        int getHeight();                                            // returns height (highest height of root)

        int getSize();                                              // returns size (numElts)

        bool find(int key, string& value);                          // finds key and puts it into value or returns false

        vector<string> findRange(int highKey, int lowKey);                                 // finds range of keys and puts them into the vector

        bool insert(int key, string value);

        friend ostream& operator<<(ostream& os, const AVLTree& me); // prints out AVLTree

    private:
        bool insertNode(int key, string value, TreeNode*& nodeAt);

        void deleteTree(TreeNode* nodeAt);

        bool helpFind(int key, string& value, TreeNode* nodeAt);

        ostream& helpPrint(ostream& os, TreeNode* nodeAt, int level) const;



	    class TreeNode {


	    public:
		    TreeNode *right;
		    TreeNode *left;
            TreeNode *parent;
            int key;
		    string elt;
            int rightHeight;
            int leftHeight;

		    TreeNode(int inKey, string inElt) { // defualt constructor
			    right = nullptr;
			    left = nullptr;
                parent = nullptr;
                key = inKey;
                elt = inElt;
                rightHeight = 0;
                leftHeight = 0;
		    }

            TreeNode(const TreeNode* copy){ // assigns null to right, left and parent so it won't connect in unwanted ways
                this->right = NULL;
                this->left = NULL;
                this->parent = NULL;
                this->elt = copy->elt;
                this->key = copy->key;
		    }

            ~TreeNode() {}; // not needed since 'new' is not used

            // to link node to the next by left pointer
            bool linkLeft(TreeNode* node) {
                if(left == nullptr){
                    left = node;
                    node->parent = this;
                    return true;
                }
                return false;
            }
            // to link node to the next by right pointer
            bool linkRight(TreeNode* node) {
                if(right == nullptr){
                    right = node;
                    node->parent = this;
                    return true;
                }
                return false;
            }

            // to unlink left node from the this
            bool unlinkLeft(){
                if(left != nullptr){
                    left->parent = nullptr;
                    left = nullptr;
                    return true;
                }
                return false;
            }
            // to unlink right node from this
            bool unlinkRight(){
                if(right != nullptr){
                    right->parent = nullptr;
                    right = nullptr;
                    return true;
                }
                return false;
            }

	};
    
        // MEMBER DATA.  These are the data items that each BinarySearchTree object will contain.  Each tree will have a head and numElts
	    TreeNode* root;
	    int numElts;   // Number of elements in the sequence


};