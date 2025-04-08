// FILE: Node.cpp
// Assignment 5
//
// DESCRIPTION:
// This file implements the Node class constructor for the linked list nodes
// used in the Permute class. Each node stores a string and a pointer to the next node.

#include "Node.h"

// Constructor
// Purpose: Initialize a new Node with given string data and next pointer
// Parameters:
//   - str: The string data to be stored in this node
//   - next: Pointer to the next node (default is nullptr)
// Postcondition: Node is created with the specified data and pointer
Node::Node(std::string str, Node* next) {
    data = str;  // Store the string
    p = next;    // Set the next pointer
}