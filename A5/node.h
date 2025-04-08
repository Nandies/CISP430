// FILE: Node.h
// Assignment 5
//
// DESCRIPTION:
// This header file defines the Node class used for creating a linked list
// to store permutations in the Permute class. Each node contains a string
// representing a permutation and a pointer to the next node.

#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
private:
    std::string data;  // String data storing a permutation
    Node* p;           // Pointer to the next node in the linked list

public:
    // Constructor
    // Purpose: Initialize a new Node with given string data and next pointer
    // Parameters:
    //   - str: The string data to be stored in this node
    //   - next: Pointer to the next node (default is nullptr)
    Node(std::string str, Node* next = nullptr);

    // Friend class declaration
    // Purpose: Allow Permute class to access private members of Node
    friend class Permute;
};

#endif // NODE_H