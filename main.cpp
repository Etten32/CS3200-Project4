//J+M+J
#include "AVLTree.h"
int main(){
    AVLTree* test = new AVLTree();
    cout << *test << endl << "------------------------" << endl;

    test->insert(20,"bob");
    cout << *test << endl << "------------------------" << endl;

    test->insert(10,"jeremy");
    cout << *test << endl << "------------------------" << endl;

    test->insert(30,"dar");
    cout << *test << endl << "------------------------" << endl;
    
    test->insert(00,"caroline");
    cout << *test << endl << "------------------------" << endl;

    test->insert(40,"adda");
    cout << *test << endl << "------------------------" << endl;

    test->insert(25,"dick");
    cout << *test << endl << "------------------------" << endl;
    
    test->insert(35,"christina");
    cout << *test << endl << "------------------------" << endl;
    
    test->insert(37,"jude");
    cout << *test << endl << "------------------------" << endl;
    
    test->insert(25,"memem");
    cout << *test << endl << "------------------------" << endl;

    string jail;
    cout << test->find(30, jail) << endl << "------------------------" << endl;

    cout << jail << endl << "------------------------" << endl;
/*
    AVLTree actual = *test;
    AVLTree* boppers = new AVLTree(actual);
    cout << *test << endl << "------------------------" << endl;
    cout << *boppers << endl << "------------------------" << endl;
*/

    vector<string> prison = test->findRange(0,40);
    prison.size();
    for(int i = 0; i < prison.size(); i++){ // help from: https://www.javatpoint.com/cpp-vector-size-function
        cout << prison.back() << endl;
        prison.pop_back();

        }
    cout << "are all in prison...." <<endl << "------------------------" << endl;

    

    for(int i = 100000; i =! 0; i--){
        AVLTree* memLeak = new AVLTree();
        memLeak->insert(0,"a");
        memLeak->insert(1,"b");
        memLeak->insert(2,"c");
        memLeak->insert(3,"d");
        memLeak->insert(4,"e");
        delete(memLeak);
    }

    system("pause");
    //
}