//
//  main.cpp
//  AVL_Tree
//
//  Created by Michał Nowak 235213 on 02.03.2018.
//  Copyright © 2018 Michał Nowak 235213. All rights reserved.
//

/*
 Zadania na ocenę bdb (5.0):
 1. Należy zaimplementować drzewo AVL przechowujące elementy określonego typu (np.: int, float, itp.). Należy napisać funkcje wykonujące podstawowe
 operacje na tym drzewie (m. in. dodawanie i usuwanie elementów, wyświetlanie elementu w korzeniu drzewa, wyświetlanie wysokości drzewa).
 2. Korzystając z drzewa z zadania 1 należy zaimplemntować przejścia pre-order, in-order i post-order. Należy zaprezentować działanie algorytmów.
 */

#include <cstdlib>
#include <ctime>

#include "AVLTree.hpp"
#include "algorithms.hpp"
#include "test_functions.hpp"

using namespace std;

double get_seconds( clock_t czas ){
    return static_cast < double >( czas ) / CLOCKS_PER_SEC;
}

int main(void) {
    
    AVLTree<int> Tree;
    
    int key=0;
    int choice=0;
    
    cout<<endl<<"-----Program functions:-----"<<endl;
    cout<<"1.View tree"<<endl;
    cout<<"2.Insert test"<<endl;
    cout<<"3.Remove test"<<endl;
    cout<<"4.Inorder"<<endl;
    cout<<"5.Postorder"<<endl;
    cout<<"6.Preorder"<<endl;
    cout<<"7.Manual Control"<<endl;
    cout<<"9.Exit"<<endl;
    
    while(1){
    
        cout<<"(Functions->press 8) > ";
        cin>>choice;
        if(choice==9){
            cout<<"Program ended with exit code 0"<<endl;
            break;
        }
        
        switch(choice){
            case 1:
                Tree.print();
                break;
            case 2:
                insert_test(Tree);
                break;
            case 3:
                remove_test(Tree);
                break;
            case 4:
                cout<<endl<<"Inorder traversal of AVL tree: "<<endl;
                Inorder(Tree.return_root());
                cout<<endl<<"Execution Time: "<<get_seconds(clock())<<"sec."<<endl<<endl;
                break;
            case 5:
                cout<<endl<<"Postorder traversal of AVL tree: "<<endl;
                Postorder(Tree.return_root());
                cout<<endl<<"Execution Time: "<<get_seconds(clock())<<"sec."<<endl<<endl;
                break;
            case 6:
                cout<<endl<<"Preorder traversal of AVL tree: "<<endl;
                Preorder(Tree.return_root());
                cout<<endl<<"Execution Time: "<<get_seconds(clock())<<"sec."<<endl<<endl;
                break;
            case 7:
                cout<<endl<<"------Manual control:-------"<<endl;
                cout<<"1.View tree"<<endl;
                cout<<"2.Add a key to the tree"<<endl;
                cout<<"3.Remove the key from the tree"<<endl;
                cout<<"4.Node information"<<endl;
                cout<<"8.Return"<<endl<<endl;
                while(1){
                    cout<<"(Return->press 8) > ";
                    cin>>choice;
                    if(choice==8) break;
                  
                    switch(choice){
                        case 1:
                            Tree.print();
                            break;
                        case 2:
                            cout<<"Enter key: ";
                            cin>>key;
                            Tree.insert(key);
                            break;
                        case 3:
                            cout<<"Enter key: ";
                            cin>>key;
                            Tree.remove(key);
                            break;
                        case 4:
                            cout<<"Enter key: ";
                            cin>>key;
                            Tree.get_node_info(key);
                            break;
                    }
                }
            case 8:
                cout<<endl<<"-----Program functions:-----"<<endl;
                cout<<"1.View tree"<<endl;
                cout<<"2.Insert test"<<endl;
                cout<<"3.Remove test"<<endl;
                cout<<"4.Inorder"<<endl;
                cout<<"5.Postorder"<<endl;
                cout<<"6.Preorder"<<endl;
                cout<<"9.Exit"<<endl<<endl;
                break;
        }
    }
    
    return 0;
}
