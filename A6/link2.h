// FILE: link2.h

// Assignment 6
// 
// TOOLKIT PROVIDED: A set of template functions for linked list operations.
//
// IMPLEMENTATION NOTES:
// 1. This file provides declarations for ten template functions that manipulate
//    singly linked lists.
// 2. Each function is carefully designed to handle edge cases such as empty lists.
// 3. The implementation of these functions is in link2.template, which is included
//    at the bottom of this file.
// 4. This design pattern (separated declaration and implementation) allows for
//    better organization of template code.

#ifndef LINK2_H
#define LINK2_H
#include <stdlib.h> // Provides size_t

    //===========================================================================
    // NODE STRUCT TEMPLATE
    //===========================================================================
    // Purpose: Defines the basic building block for linked lists
    // Template parameter:
    // - Item: The data type stored in each node
    // Components:
    // - data: Holds the actual information
    // - link: Points to the next node in the list (or NULL if none)
    //===========================================================================
template <class Item>
struct Node
{
    Item data;
    Node* link;
};

// FUNCTIONS for the linked list toolkit

//===========================================================================
// LIST_LENGTH FUNCTION
//===========================================================================
// Purpose: Count the number of nodes in a linked list
// Precondition: head_ptr is the head pointer of a linked list (may be NULL)
// Postcondition: 
// - Returns the number of nodes in the list
// - The list is unchanged
// Time complexity: O(n) where n is the number of nodes
//===========================================================================
template <class Item>
size_t list_length(Node<Item>* head_ptr);

//===========================================================================
// LIST_HEAD_INSERT FUNCTION
//===========================================================================
// Purpose: Insert a new node at the beginning of a linked list
// Precondition: head_ptr is the head pointer of a linked list (may be NULL)
// Postcondition: 
// - A new node containing entry is added at the front of the list
// - head_ptr now points to this new node
// - The list is one node longer
// Time complexity: O(1) - constant time operation
//===========================================================================
template <class Item>
void list_head_insert(Node<Item>*& head_ptr, const Item& entry);

//===========================================================================
// LIST_INSERT FUNCTION
//===========================================================================
// Purpose: Insert a new node after a specified node in a linked list
// Precondition: previous_ptr points to a node in a linked list
// Postcondition: 
// - A new node containing entry is added after the node that previous_ptr points to
// - The list is one node longer
// Time complexity: O(1) - constant time operation
//===========================================================================
template <class Item>
void list_insert(Node<Item>*& previous_ptr, const Item& entry);

//===========================================================================
// LIST_SEARCH FUNCTION
//===========================================================================
// Purpose: Find the first occurrence of a target value in a linked list
// Precondition: head_ptr is the head pointer of a linked list (may be NULL)
// Postcondition: 
// - Returns a pointer to the first node containing the target
// - Returns NULL if target is not found
// - The list is unchanged
// Time complexity: O(n) where n is the number of nodes
//===========================================================================
template <class Item>
Node<Item>* list_search(Node<Item>* head_ptr, const Item& target);

//===========================================================================
// LIST_LOCATE FUNCTION
//===========================================================================
// Purpose: Find the node at a specified position in a linked list
// Precondition: 
// - head_ptr is the head pointer of a linked list (may be NULL)
// - position > 0
// Postcondition: 
// - Returns a pointer to the node at the specified position
// - Returns NULL if no such position exists
// - The list is unchanged
// - The head node is position 1, the next is position 2, etc.
// Time complexity: O(n) where n is the position value
//===========================================================================
template <class Item, class SizeType>
Node<Item>* list_locate(Node<Item>* head_ptr, SizeType position);

//===========================================================================
// LIST_HEAD_REMOVE FUNCTION
//===========================================================================
// Purpose: Remove the first node from a linked list
// Precondition: 
// - head_ptr is the head pointer of a linked list
// - The list has at least one node
// Postcondition: 
// - The head node is removed and its memory returned to the heap
// - head_ptr now points to the second node (or NULL if there was only one node)
// - The list is one node shorter
// Time complexity: O(1) - constant time operation
//===========================================================================
template <class Item>
void list_head_remove(Node<Item>*& head_ptr);

//===========================================================================
// LIST_REMOVE FUNCTION
//===========================================================================
// Purpose: Remove the node after a specified node in a linked list
// Precondition: 
// - previous_ptr points to a node in a linked list
// - This is not the tail node of the list (there is a node after it)
// Postcondition: 
// - The node after previous_ptr is removed and its memory returned to the heap
// - The list is one node shorter
// Time complexity: O(1) - constant time operation
//===========================================================================
template <class Item>
void list_remove(Node<Item>* previous_ptr);

//===========================================================================
// LIST_CLEAR FUNCTION
//===========================================================================
// Purpose: Remove all nodes from a linked list
// Precondition: head_ptr is the head pointer of a linked list (may be NULL)
// Postcondition: 
// - All nodes are removed and their memory returned to the heap
// - head_ptr is set to NULL (empty list)
// Time complexity: O(n) where n is the number of nodes
//===========================================================================
template <class Item>
void list_clear(Node<Item>*& head_ptr);

//===========================================================================
// LIST_COPY FUNCTION
//===========================================================================
// Purpose: Create a copy of a linked list
// Precondition: source_ptr is the head pointer of a linked list (may be NULL)
// Postcondition: 
// - head_ptr points to the head of a new list that contains copies of all nodes
//   from the source_ptr list
// - tail_ptr points to the last node in this new list (or NULL if list is empty)
// - The original list is unchanged
// Time complexity: O(n) where n is the number of nodes in the source list
//===========================================================================
template <class Item>
void list_copy
(Node<Item>* source_ptr, Node<Item>*& head_ptr, Node<Item>*& tail_ptr);

//===========================================================================
// LIST_PIECE FUNCTION
//===========================================================================
// Purpose: Create a copy of a segment of a linked list
// Precondition: 
// - source_ptr and end_ptr are pointers to nodes on the same linked list
// - source_ptr node is at or before the end_ptr node
// Postcondition: 
// - head_ptr points to the head of a new list containing copies of all nodes 
//   from source_ptr up to and including end_ptr
// - tail_ptr points to the last node in this new list
// - The original list is unchanged
// Time complexity: O(n) where n is the number of nodes copied
//===========================================================================
template <class Item>
void list_piece
(Node<Item>* source_ptr, Node<Item>* end_ptr,
    Node<Item>*& head_ptr, Node<Item>*& tail_ptr);

#include "link2.template"  // Include the implementation
#endif