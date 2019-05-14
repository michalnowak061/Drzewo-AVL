//
//  test_functions.hpp
//  AVL_Tree
//
//  Created by Michał on 20.03.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#ifndef test_functions_hpp
#define test_functions_hpp

#include <stdio.h>
#include "AVLTree.hpp"

template<typename T>
void insert_test(AVLTree<T> &_Tree){
    cout<<"************** INSERT TEST **********************************"<<endl;
    cout<<endl<<"EMPTY TREE: "<<endl;
    _Tree.print();
    cout<<endl;
    
    cout<<endl<<"TREE AFTER INSERTION. INSERTED KEY'S: 44,17,78,32,50,88,48,62"<<endl;
    _Tree.insert(44);
    _Tree.insert(17);
    _Tree.insert(78);
    _Tree.insert(32);
    _Tree.insert(50);
    _Tree.insert(88);
    _Tree.insert(48);
    _Tree.insert(62);
    _Tree.print();
    cout<<endl;
    
    cout<<endl<<"TREE AFTER INSERTION. INSERTED KEY: 54"<<endl;
    _Tree.insert(54);
    _Tree.print();
    cout<<endl;
    cout<<"*************************************************************"<<endl;
}

template<typename T>
void remove_test(AVLTree<T> &_Tree){
    cout<<"************** REMOVE TEST **********************************"<<endl;
    cout<<endl<<"TREE BEFORE REMOVAL: "<<endl;
    _Tree.print();
    
    cout<<endl<<"TREE AFTER REMOVAL. REMOVED KEY: 32"<<endl;
    _Tree.remove(32);
    _Tree.print();
    cout<<"*************************************************************"<<endl;
}
#endif
