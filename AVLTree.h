//J+M+J
/** FILE: AVLTree.h
// CLASS: PROVIDED: AVLTree
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
// INFORMATION: FUNCTIONS:
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
// MUTATION: FUNCTIONS:
//  bool AVLTree::insert(int key, string value)
//      Postcondition: condition-0 = returns false if item error occcured or key was already inserted
//                     condition-1 = returns true if insert was correct
//
// FREINDS:
// freind ostream& operator<<(ostream& os, const AVLTree& me)
//      Postcondition: prints out tree to AVLTree::operator<<().os and returns it
//
// *v*v*v*v* PRIVATE: *v*v*v*v*
// INFORMATION: FUNCTIONS:
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

        ~AVLTree();                                                 // deconstructs tree

        int getHeight();                                            // returns height (highest height of root)

        int getSize();                                              // returns size (numElts)

        bool find(int key, string& value);                          // finds key and puts it into value or returns false

        vector<string> findRange(int highKey, int lowKey);          // finds range of keys and puts them into the vector

        bool insert(int key, string value);                                             /** NEEDS: DOCUMENTED: **/

        AVLTree& operator=(const AVLTree& toTransfer);                              /** NEEDS: DOCUMENTED: **/

        friend ostream& operator<<(ostream& os, const AVLTree& me); // prints out AVLTree

        bool testRotate(int key, char shift);                                           /** NEEDS: DOCUMENTED: **/
        
        bool rightRotate(TreeNode* toRotate);                                            /** NEEDS: DOCUMENTED: **/

        bool doubleRightR(TreeNode* toRotate);                                           /** NEEDS: DOCUMENTED: **/

        bool leftRotate(TreeNode* toRotate);                                             /** NEEDS: DOCUMENTED: **/

        bool doubleLeftR(TreeNode* toRotate);                                            /** NEEDS: DOCUMENTED: **/

    private:
    
        bool testRotate(int key, TreeNode* nodeAt, char shift);                         /** NEEDS: DOCUMENTED: **/

        void helpMake(TreeNode* nodeAt, AVLTree* treeToAdd);                            /** NEEDS: DOCUMENTED: **/

        bool insertNode(int key, string value, TreeNode*& nodeAt);                      /** NEEDS: DOCUMENTED: **/

        void clearTree(TreeNode* nodeAt);                                        /** NEEDS: DOCUMENTED: **/

        void makeTree(TreeNode* nodeAt);                                                /** NEEDS: DOCUMENTED: **/

        bool helpFind(int key, string& value, TreeNode* nodeAt);                        /** NEEDS: DOCUMENTED: **/

        ostream& helpPrint(ostream& os, TreeNode* nodeAt, int level) const;             /** NEEDS: DOCUMENTED: **/



	    class TreeNode {


	    public:
        /** NEEDS: DOCUMENTED: **/ // vvv ALL VARS BELOW vvv
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

            /** NEEDS: DOCUMENTED: **/
            // recalculates height
            void recalculateHeight(){
                if(this->right == nullptr) rightHeight = 0;
                else this->rightHeight = this->right->getHeight() + 1; // height is one more than previous
                if(this->left == nullptr) leftHeight = 0;
                else this->leftHeight = this->left->getHeight() + 1; // height is one more than previous
            }

            // get the height of a node in the treee
            int getHeight(){
                return this->leftHeight >= this->rightHeight ? this->leftHeight: this->rightHeight;                // return the heigher of the two heights in the root
            //                                                                                                     asistance from this site to format ternary operator: 
            //                                                                                                     https://www.programiz.com/cpp-programming/ternary-operator
            }

            /** NEEDS: DOCUMENTED: **/
            // calculate and get balance of a node
            int getBalance(){
                return leftHeight - rightHeight;
            }

            //* to link node to the next by left pointer
            //  bool TreeNode::linkLeft(TreeNode* node)
            //      Postcondition: condition-0 = returns false if left pointer was not nullptr
            //                     condition-1 = returns true left pointer was nullptr and links 
            //                     this->left to AVLTree::find().node and AVLTree::find().node->parent to this
            bool linkLeft(TreeNode* node) {
                if(left == nullptr){
                    left = node;
                    node->parent = this;
                    return true;
                }
                return false;
            }

            //* to link node to the next by left pointer regardless of TreeNode*'s state
            //  bool TreeNode::linkLeft(TreeNode* node)
            //      Postcondition: this->left to AVLTree::find().node and AVLTree::find().node->parent to this
            //                     to unconditionally link node to the next by left pointer
            void bangLinkLeft(TreeNode* node){
                left = node;
                node->parent = this;
            }
            
            //* to link node to the next by right pointer
            //  bool TreeNode::linkRight(TreeNode* node)
            //      Postcondition: condition-0 = returns false if left pointer was not nullptr
            //                     condition-1 = returns true left pointer was nullptr and links 
            //                     this->right to AVLTree::find().node and AVLTree::find().node->parent to this
            // to link node to the next by right pointer
            bool linkRight(TreeNode* node) {
                if(right == nullptr){
                    right = node;
                    node->parent = this;
                    return true;
                }
                return false;
            }

            //* to link node to the next by right pointer regardless of TreeNode*'s state
            //  bool TreeNode::linkRight(TreeNode* node)
            //      Postcondition: this->right to AVLTree::find().node and AVLTree::find().node->parent to this
            //                     to unconditionally link node to the next by left pointer
            void bangLinkRight(TreeNode* node){
                right = node;
                node->parent = this;
            }

            //* to unlink left node from the this
            //  bool TreeNode::unlinkRight()
            //      Postcondition: this->left->parent is set to nullptr as well as this->left
            bool unlinkLeft(){
                if(left != nullptr){
                    left->parent = nullptr;
                    left = nullptr;
                    return true;
                }
                return false;
            }
            
            //* to unlink left node from the this
            //  bool TreeNode::unlinkRight()
            //      Postcondition: this->right->parent is set to nullptr as well as this->right
            bool unlinkRight(){
                if(right != nullptr){
                    right->parent = nullptr;
                    right = nullptr;
                    return true;
                }
                return false;
            }

            //* to link node with where old was
            //  bool TreeNode::replacePointerWith
            //      Precondition: TreeNode::replacePointerWith().old and TreeNode::replacePointerWith().replaceWith
            //                    must not be nullptr
            //      Postcondition: /** FINISH: **/
            bool replacePointerWith(TreeNode* old, TreeNode* replaceWith){
                if(this->left != nullptr && this->left->key == old->key) this->bangLinkLeft(replaceWith);
                else if(this->right != nullptr && this->right->key == old->key) this->bangLinkRight(replaceWith);
                else return false;
                return true;
            }

	};
    
        // MEMBER DATA.  These are the data items that each BinarySearchTree object will contain.  Each tree will have a head and numElts
	    TreeNode* root;
	    int numElts;   // Number of elements in the sequence


};