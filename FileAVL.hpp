/**
 * @file FileAVL.hpp
 * @brief Defines the interface for the AVLtree class & implementation of the Node struct
 */

#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "File.hpp"
#include <queue>

struct Node {
   size_t size_;    
   std::vector<File*> files_;
   int height_;   // The height of the Node
   Node *left_;   // A pointer to Node's left child
   Node *right_;  // A pointer to Node's right child
   
   // Parameterized constructor for a Node
   Node(File* f, Node* lt=nullptr, Node* rt=nullptr) : size_{f->getSize()}, files_{ {f} }, height_{0}, left_{lt}, right_{rt} {}
};


class FileAVL {
   public:
      std::vector<File*> query(size_t min, size_t max);
      FileAVL();
      ~FileAVL();
      void insert(File* target);   
      int height(Node* n) const;
      void displayLevelOrder() const;
      void displayInOrder() const;
      int size() const;

   private:
      static const int ALLOWED_IMBALANCE = 1;
      Node* root_;
      int size_;

      void insert(File*& target, Node*& subroot);
      void balance(Node* &t);
      void displayLevelOrder(Node* t) const;
      void displayInOrder(Node* t) const;
      void rotateWithLeftChild(Node*& k2);
      void rotateWithRightChild(Node*& k1);
      void doubleWithLeftChlid(Node*& k3);
      void doubleWithRightChild(Node*& k3);
      void deleteTree(Node*& t);
};
