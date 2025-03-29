// FILE: pqueue1.cpp
// CISP 430 Spring 2025
// Assignment 4
// 
// CLASS IMPLEMENTED: PriorityQueue (see pqueue1.h for documentation)
//
// IMPLEMENTATION NOTES:
// 1. The PriorityQueue is implemented using a linked list where nodes are
//    ordered from highest priority (at the head) to lowest priority (at the tail).
// 2. For items with equal priority, they come out in the order they were inserted
//    (FIFO for equal priorities).
// 3. The implementation includes proper memory management with copy constructor,
//    assignment operator, and destructor to handle dynamic memory allocation.

#include "pqueue1.h"
#include <cassert> // For assert - provides runtime checking of conditions

//===========================================================================
// DEFAULT CONSTRUCTOR
//===========================================================================
// Purpose: Initialize an empty priority queue with no nodes
// Precondition: None
// Postcondition: 
// - head_ptr is set to nullptr (no nodes in the list)
// - many_nodes counter is set to 0 (empty queue)
// Time complexity: O(1) - constant time operation
//===========================================================================
PriorityQueue::PriorityQueue() {
    head_ptr = nullptr;  // Initialize the head pointer to null (empty list)
    many_nodes = 0;      // Initialize the counter to track zero nodes
}

//===========================================================================
// COPY CONSTRUCTOR
//===========================================================================
// Purpose: Create a deep copy of another PriorityQueue
// Algorithm:
// 1. Initialize this queue as empty
// 2. If the source queue is empty, return (nothing to copy)
// 3. Copy the first node from source
// 4. Iterate through remaining source nodes, copying each one
// 5. Update the node count to match the source
// Precondition: Source is a valid PriorityQueue object
// Postcondition: 
// - This queue contains exact copies of all nodes from source
// - Changes to source afterward won't affect this queue (deep copy)
// - Original node ordering is preserved
// Time complexity: O(n) where n is the number of nodes in source
//===========================================================================
PriorityQueue::PriorityQueue(const PriorityQueue& source) {
    Node* source_ptr;  // Pointer to traverse nodes in source list
    Node* tail_ptr;    // Pointer to last node in the new list being built

    // Step 1: Initialize this queue as empty
    head_ptr = nullptr;
    many_nodes = 0;

    // Step 2: Handle special case - source is empty
    if (source.many_nodes == 0)
        return;  // Nothing to copy, so return with empty queue

    // Step 3: Copy the first node
    source_ptr = source.head_ptr;  // Start at source's head

    // Create first node and copy data and priority
    head_ptr = new Node;  // Allocate memory for first node
    head_ptr->data = source_ptr->data;  // Copy the item
    head_ptr->priority = source_ptr->priority;  // Copy the priority
    head_ptr->link = nullptr;  // Set the link to null (will be updated if needed)

    // Move pointers forward to prepare for remaining nodes
    source_ptr = source_ptr->link;  // Move to next source node
    tail_ptr = head_ptr;  // tail_ptr now points to the last node in our new list

    // Step 4: Copy all remaining nodes in sequence
    while (source_ptr != nullptr) {
        // Create a new node at the end of our list
        tail_ptr->link = new Node;
        tail_ptr = tail_ptr->link;  // Move tail to this new node

        // Copy the data from source node to our new node
        tail_ptr->data = source_ptr->data;
        tail_ptr->priority = source_ptr->priority;
        tail_ptr->link = nullptr;  // This might be the last node

        // Move to next source node
        source_ptr = source_ptr->link;
    }

    // Step 5: Set the node count to match source
    many_nodes = source.many_nodes;
}

//===========================================================================
// DESTRUCTOR
//===========================================================================
// Purpose: Free all dynamically allocated memory used by this queue
// Algorithm:
// 1. Start at the head of the list
// 2. For each node:
//    a. Save a pointer to the current node
//    b. Move head_ptr to the next node
//    c. Delete the saved node
// Precondition: None
// Postcondition: 
// - All dynamically allocated memory for nodes is returned to the heap
// - No memory leaks from this queue
// Time complexity: O(n) where n is the number of nodes
//===========================================================================
PriorityQueue::~PriorityQueue() {
    Node* remove_ptr;  // Temporary pointer to node being removed

    // Loop until all nodes are deleted (until head_ptr becomes null)
    while (head_ptr != nullptr) {
        remove_ptr = head_ptr;  // Save pointer to the current node
        head_ptr = head_ptr->link;  // Move head to the next node
        delete remove_ptr;  // Free memory for the saved node
    }
    // Note: No need to reset many_nodes since object is being destroyed
}

//===========================================================================
// ASSIGNMENT OPERATOR
//===========================================================================
// Purpose: Assign this queue to be a copy of another queue
// Algorithm:
// 1. Check for self-assignment (if this == &source)
// 2. Delete all current nodes in this queue
// 3. If source is empty, leave this queue empty
// 4. Otherwise, copy all nodes from source, starting with first node
// 5. Update the node count to match source
// Precondition: Source is a valid PriorityQueue object
// Postcondition: 
// - This queue is a deep copy of source queue
// - Previous contents of this queue are properly deallocated
// - Self-assignment is handled correctly (no changes if this == &source)
// Time complexity: O(n+m) where n is current size and m is source size
//===========================================================================
void PriorityQueue::operator =(const PriorityQueue& source) {
    Node* source_ptr;   // Pointer to traverse nodes in source list
    Node* tail_ptr;     // Pointer to last node in new list being built

    // Step 1: Check for self-assignment to prevent deleting our own data
    if (this == &source)
        return;  // Do nothing if assigning to self

    // Step 2: Delete all current nodes to free memory
    Node* remove_ptr;
    while (head_ptr != nullptr) {
        remove_ptr = head_ptr;
        head_ptr = head_ptr->link;
        delete remove_ptr;
    }

    // Initialize this queue as empty
    head_ptr = nullptr;
    many_nodes = 0;

    // Step 3: Handle case where source is empty
    if (source.many_nodes == 0)
        return;  // Leave this queue empty

    // Step 4a: Copy the first node from source
    source_ptr = source.head_ptr;
    head_ptr = new Node;
    head_ptr->data = source_ptr->data;
    head_ptr->priority = source_ptr->priority;
    head_ptr->link = nullptr;

    // Move pointers forward to prepare for remaining nodes
    source_ptr = source_ptr->link;
    tail_ptr = head_ptr;

    // Step 4b: Copy all remaining nodes in sequence
    while (source_ptr != nullptr) {
        tail_ptr->link = new Node;
        tail_ptr = tail_ptr->link;
        tail_ptr->data = source_ptr->data;
        tail_ptr->priority = source_ptr->priority;
        tail_ptr->link = nullptr;
        source_ptr = source_ptr->link;
    }

    // Step 5: Update node count to match source
    many_nodes = source.many_nodes;
}

//===========================================================================
// INSERT FUNCTION
//===========================================================================
// Purpose: Insert a new item with specified priority into the queue
// Algorithm:
// 1. Create a new node with the given item and priority
// 2. Find correct position to insert based on priority:
//    - Scan until we find a node with lower priority than new node
//    - For equal priorities, insert after existing ones (FIFO behavior)
// 3. Insert the node at the found position (beginning, middle, or end)
// 4. Increment node counter
// Precondition: 
// - entry is a valid Item that can be copied
// - priority is an unsigned integer
// Postcondition: 
// - New node with copy of entry and given priority is in correct position
// - PriorityQueue ordering is maintained (highest to lowest priority)
// - For equal priorities, new node is placed after existing ones
// - Node count is increased by 1
// Time complexity: O(n) where n is the number of nodes in the queue
//===========================================================================
void PriorityQueue::insert(const Item& entry, unsigned int priority) {
    Node* previous_ptr = nullptr;  // Points to node before insertion point
    Node* cursor = head_ptr;       // Used to traverse the list
    Node* new_node;                // The node we'll insert

    // Step 1: Create the new node
    new_node = new Node;
    new_node->data = entry;        // Store the item
    new_node->priority = priority; // Store the priority
    new_node->link = nullptr;      // Initialize link (will be set later)

    // Step 2: Find the correct position to insert
    // Traverse until we find a node with lower priority
    // For equal priorities, we go past them to maintain FIFO order
    while (cursor != nullptr && cursor->priority >= priority) {
        previous_ptr = cursor;      // Keep track of previous node
        cursor = cursor->link;      // Move to next node
    }

    // Step 3: Insert the node at the found position
    // Case 1: Insert at beginning (empty list or higher priority than head)
    if (previous_ptr == nullptr) {
        new_node->link = head_ptr;  // New node points to current head
        head_ptr = new_node;        // New node becomes the head
    }
    // Case 2: Insert in middle or at end
    else {
        new_node->link = cursor;          // New node points to next node
        previous_ptr->link = new_node;    // Previous node points to new node
    }

    // Step 4: Update the node count
    many_nodes++;
}

//===========================================================================
// GET_FRONT FUNCTION
//===========================================================================
// Purpose: Remove and return the highest priority item in the queue
// Algorithm:
// 1. Check precondition that queue is not empty
// 2. Save the data from the front node
// 3. Remove the front node and update head_ptr
// 4. Decrement node count
// 5. Return the saved data
// Precondition: size() > 0 (queue is not empty)
// Postcondition: 
// - Front node (highest priority) is removed from the queue
// - The data from that node is returned
// - Node count is decreased by 1
// - Memory for the removed node is freed
// Time complexity: O(1) - constant time operation
//===========================================================================
PriorityQueue::Item PriorityQueue::get_front() {
    // Step 1: Check precondition (queue is not empty)
    assert(size() > 0);  // Will throw error if queue is empty

    Node* remove_ptr;  // Points to the node being removed
    Item answer;       // To store the return value

    // Step 2: Save the data from front node
    answer = head_ptr->data;

    // Step 3: Remove the front node
    remove_ptr = head_ptr;        // Save pointer to front node
    head_ptr = head_ptr->link;    // Update head to point to next node
    delete remove_ptr;            // Free memory of removed node

    // Step 4: Update node count
    many_nodes--;

    // Step 5: Return the data
    return answer;
}