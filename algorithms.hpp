//
//  algorithms.hpp
//  AVL_Tree
//
//  Created by Michał on 16.03.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#ifndef algorithms_hpp
#define algorithms_hpp

#include <stdio.h>
#include "AVLTree.hpp"

//-----------------------------------
template<typename T>
void Postorder(AVLNode<T> *_root){
    if(_root != nullptr){
        Postorder(_root->left);
        Postorder(_root->right);
        cout<<_root->key<<" ";
    }
}
//-----------------------------------
template<typename T>
void Inorder(AVLNode<T> *_root){
    if (_root != nullptr){
        Inorder(_root->left);
        cout<<_root->key<<" ";
        Inorder(_root->right);
    }
}
//-----------------------------------
template<typename T>
void Preorder(AVLNode<T> *_root){
    if (_root != nullptr){
        cout<<_root->key<<" ";
        Preorder(_root->left);
        Preorder(_root->right);
    }
}
//-----------------------------------
#endif
