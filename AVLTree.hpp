//
//  AVL_Tree.hpp
//  AVL_Tree
//
//  Created by Michał on 16.03.2018.
//  Copyright © 2018 Michał. All rights reserved.
//
#ifndef Header_h
#define Header_h

#include <iostream>
#include <stdio.h>

using namespace std;

//**************************************************
//************** AVL Tree Node *********************
template<typename T>
class AVLNode{
public:
    AVLNode *left;      // <-address of the left son
    AVLNode *right;     // <-address of the right son
    T key;              // <-data (T-data type)
    int balancefactor;  // <-balancefactor
    
    AVLNode();  //constructor
    ~AVLNode(); //destructor
};
//**************************************************
//**************************************************
//--------------------------------------------------

template<typename T>
AVLNode<T>::AVLNode(){
    left=nullptr;
    right=nullptr;
    balancefactor=0;
}
//--------------------------------------------------
template<typename T>
AVLNode<T>::~AVLNode(){
    delete left;
    delete right;
}
//**************************************************
//************** AVL Tree **************************
template<class T>
class AVLTree{
//--------------------------------------------------
private:
    AVLNode<T> *root;  // <-tree root
    int nodecount;     // <-number of nodes
//--------------------------------------------------
public:
    AVLTree();  //constructor
    ~AVLTree(); //destructor
    
    int return_count(){return nodecount;}         //return number of nodes
    AVLNode<T> *const return_root(){return root;} //return pointer to the root
    
    void insert(T _key);    //insert a node with key
    void remove(T _key);    //remove a node with key
    void print();           //print the tree
    int height();           //return tree height
    
    void get_node_info(T _key); //print node info
//---------------------------------------------------
private:
    AVLNode<T> *search_AVL(AVLNode<T> *_root,T _key); //finds a node with a given key
    
    void remove_AVL(AVLNode<T> *&_root,T _key);  //remove a tree node with key and root
    void insert_AVL(AVLNode<T> *&_root,T _data); //insert a tree node with key and root
    void print_AVL(AVLNode<T> *root, int space); //print the tree
    
    int height_AVL(AVLNode<T> *_root); //return tree or subtree hight
    
    AVLNode<T> *rotationRR_AVL(AVLNode<T> *&_root); //one right rotation
    AVLNode<T> *rotationLL_AVL(AVLNode<T> *&_root); //one left rotation
    AVLNode<T> *rotationRL_AVL(AVLNode<T> *&_root); //one right rotation and one left rotation
    AVLNode<T> *rotationLR_AVL(AVLNode<T> *&_root); //one left rotation and one right rotation
    
    int get_balance_AVL(AVLNode<T> *_root);  //return balancefactor
    void restructure_AVL(AVLNode<T> *&temp); //return balance in the tree
};
//**************************************************
//**************************************************
//------------------------------------------------------------------------------------
template<typename T>
AVLTree<T>::AVLTree(){
    root = nullptr;
    nodecount = 0;
}
//------------------------------------------------------------------------------------
template<typename T>
AVLTree<T>::~AVLTree(){
    delete root;
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::insert_AVL(AVLNode<T> *&_root,T _key){
    
    //1 case: tree is empty or we got to the leaf
    if (_root == nullptr){
        _root = new AVLNode<T>; //allocation of a new node in memory
        _root->key=_key;        //entering the key into the node
        nodecount++;
    }
    //2 case: the key in the compared node is larger
    else if(_root->key>_key){
        insert_AVL(_root->left, _key);   //move to the left child
    }
    //3 case: the key in the compared node is smaller
    else if(_root->key<=_key){
        insert_AVL(_root->right, _key);  //move to the right child
    }
    
    _root->balancefactor = get_balance_AVL(_root);  //save balancefactor in node
    if (_root->balancefactor == 2 || _root->balancefactor == -2){   //the balance is disturbed
        restructure_AVL(_root); //return balance
    }
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::insert(T _key){
    insert_AVL(root,_key); //add a node with the given key by searching the tree
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::remove_AVL(AVLNode<T> *&_root,T _key)
{
    AVLNode<T> *temp = nullptr;
    
    //1 case: tree is empty or we got to the leaf
    if(_root == nullptr){return;}
    //2 case: the key in the compared node is smaller
    if(_key < _root->key) remove_AVL(_root->left, _key);
    //3 case: the key in the compared node is larger
    else if(_key > _root->key) remove_AVL(_root->right, _key);
    //4 case: root is to be deleted
    else if(_key == _root->key){
        // 0 children
        if(_root->left == nullptr && _root->right == nullptr){
            free(_root);
            _root=nullptr;
            nodecount--;
        }
        // 1 right child
        else if(_root->left == nullptr && _root->right != nullptr){
            temp=_root->right;
            free(_root);
            _root=temp;
            nodecount--;
        }
        // 1 left child
        else if(_root->right == nullptr && _root->left != nullptr){
            temp=_root->left;
            free(_root);
            _root=temp;
            nodecount--;
        }
        // 2 children
        else if(_root->right != nullptr && _root->left != nullptr){
            temp = _root->left;
            
            while (temp->right != NULL) {
                temp = temp->right;
            }
            _key = temp->key;
            remove_AVL(_root->left, _key);
            _root->key = _key;
        }
    }
    
    if (_root != nullptr){
        _root->balancefactor = get_balance_AVL(_root); //save balancefactor in node
        if (_root->balancefactor == 2 || _root->balancefactor == -2)
            restructure_AVL(_root); //return balance in tree
    }
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::remove(T _key){
    remove_AVL(root,_key);
}
//------------------------------------------------------------------------------------
template<typename T>
int AVLTree<T>::height_AVL(AVLNode<T> *_root){
    //1 case: subtree is empty
    if(_root == nullptr) return 0;
    //2 case: find recursive and return the longest path
    else return max(height_AVL(_root->left),height_AVL(_root->right))+1;
}
//------------------------------------------------------------------------------------
template<typename T>
int AVLTree<T>::height(){
    return height_AVL(root);
}
//------------------------------------------------------------------------------------
template<typename T>
AVLNode<T> *AVLTree<T>::rotationRR_AVL(AVLNode<T> *&_root)
{
    AVLNode<T> *temp=_root->right;
    _root->right=temp->left;
    temp->left=_root;
    //fix balancefactor in rotated nodes
    _root->balancefactor=get_balance_AVL(_root);
    temp->balancefactor=get_balance_AVL(temp);
    cout<<"RR rotation"<<endl;
    return temp;
}
//------------------------------------------------------------------------------------
template<typename T>
AVLNode<T> *AVLTree<T>::rotationLL_AVL(AVLNode<T> *&_root)
{
    AVLNode<T> *temp=_root->left;
    _root->left=temp->right;
    temp->right=_root;
    //fix balancefactor in rotated nodes
    _root->balancefactor=get_balance_AVL(_root);
    temp->balancefactor=get_balance_AVL(temp);
    cout<<"LL rotation"<<endl;
    return temp;
}
//------------------------------------------------------------------------------------
template<typename T>
AVLNode<T> *AVLTree<T>::rotationRL_AVL(AVLNode<T> *&_root){
    AVLNode<T> *temp=_root->right;
    _root->right=rotationLL_AVL(temp);
    return rotationRR_AVL(_root);
}
//------------------------------------------------------------------------------------
template<typename T>
AVLNode<T> *AVLTree<T>::rotationLR_AVL(AVLNode<T> *&_root){
    AVLNode<T> *temp=_root->left;
    _root->left=rotationRR_AVL(temp);
    return rotationLL_AVL(_root);
}
//------------------------------------------------------------------------------------
template<typename T>
int AVLTree<T>::get_balance_AVL(AVLNode<T> *_root){
    return  height_AVL(_root->left)-height_AVL(_root->right);
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::restructure_AVL(AVLNode<T> *&_root)
{
    //1 case: left subtree is higher
    if (_root->balancefactor == 2){
        if (_root->left->balancefactor > 0) _root=rotationLL_AVL(_root);
        else _root = rotationLR_AVL(_root);
    }
    //2 case: right subtree is higher
    else if (_root->balancefactor == -2){
        if (_root->right->balancefactor > 0) _root=rotationRL_AVL(_root);
        else _root=rotationRR_AVL(_root);
    }
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::print_AVL(AVLNode<T> *_root,int _space){
    // Base case
    if (_root != nullptr){
        // Increase distance between levels
        _space+=10;
        // Process right child first
        print_AVL(_root->right,_space);
        // Print current node after space
        cout<<endl;
        for (int i = 10; i < _space; i++)
            cout<<" ";
        cout<<"("<<_root->key<<"|"<<_root->balancefactor<<")"<<endl;
        // Process left child
        print_AVL(_root->left,_space);
    }
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::print(){
    print_AVL(root,10);
    cout<<endl<<"Number of nodes: "<<nodecount<<endl;
    cout<<"Tree height: "<<height_AVL(root)<<endl;
}
//------------------------------------------------------------------------------------
template<typename T>
AVLNode<T> *AVLTree<T>::search_AVL(AVLNode<T> *_root,T _key){
    if(_root==nullptr) return _root;
    else if(_root->key<_key) return search_AVL(_root->right,_key);
    else if(_key==_root->key) return _root;
    else return search_AVL(_root->left,_key);
}
//------------------------------------------------------------------------------------
template<typename T>
void AVLTree<T>::get_node_info(T _key){
    AVLNode<T> *temp = search_AVL(root,_key);
    
    if(temp != nullptr){
        cout<<endl<<"Node key: "<<temp->key<<endl;
        cout<<"Node belancefactor: "<<temp->balancefactor<<endl;
        if(temp->left!=nullptr){
            cout<<"Left child adress: "<<temp->left<<endl;
            cout<<"Left child key: "<<temp->left->key<<endl;
        }
        if(temp->right!=nullptr){
            cout<<"Right child adress: "<<temp->right<<endl;
            cout<<"Right child key: "<<temp->right->key<<endl;
        }
        if(temp->left==nullptr && temp->right==nullptr) cout<<"Child's: 0"<<endl;
    }else cout<<endl<<"Node not found"<<endl;    
}
//------------------------------------------------------------------------------------
#endif




