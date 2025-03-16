
// FILE: sequence4.h 
// TEMPLATE CLASS PROVIDED:
//   sequence<Item> (part of the namespace CISP430_A3)
//   This is a container class for a sequence of items,
//   where each List may have a designated item called the current item).
//   The template parameter <value_type> is the data type of the items
//   in the List. It may be any of the C++ built-in types (int, char, etc.),
//   or a class with a default constructor, an assignment operator,
//   and a copy constructor.
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   sequence<Item>::value_type
//     Thisis the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   sequence<Item>::size_type
//     This is the data type of any variable that keeps track of
//     how many items are in a sequence.
//
// CONSTRUCTOR for the sequence<Item> class:
//   sequence( )
//     Postcondition: The sequence has been initialized as an empty sequence.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence<Item> class:
//   void start( )
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and
//     the item after this (if there is one) is now the new current item.
//
// CONSTANT MEMBER FUNCTIONS for the sequence<Item> class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequence.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
// INVARIANTS for the sequence class:
//   1. The number of items in the sequence is stored in many_nodes.
//   2. head_ptr is the head pointer of a linked list containing all items.
//   3. tail_ptr points to the last node in the linked list.
//   4. If there is a current item, cursor points to it and precursor points
//      to the node before it (or is NULL if the current item is the first node).
//      If there is no current item, cursor and precursor are both NULL.

#ifndef SEQUENCE4_H
#define SEQUENCE4_H
#include <cstdlib>  // Provides size_t
#include "node2.h"  // Provides node class

namespace CISP430_A3
{
    template <class Item>
    class sequence
    {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef Item value_type;     // Type of items stored in the sequence
        typedef size_t size_type;    // Type used for counting items

        // CONSTRUCTORS and DESTRUCTOR
        sequence();                  // Default constructor creates empty sequence
        sequence(const sequence& source); // Copy constructor
        ~sequence();                 // Destructor frees all dynamic memory

        // MODIFICATION MEMBER FUNCTIONS
        void start();                // Set cursor to first item
        void advance();              // Move cursor to next item
        void insert(const value_type& entry); // Insert before current item
        void attach(const value_type& entry); // Insert after current item
        void operator =(const sequence& source); // Assignment operator
        void remove_current();       // Remove the current item

        // CONSTANT MEMBER FUNCTIONS
        size_type size() const { return many_nodes; } // Return item count
        bool is_item() const { return (cursor != NULL); } // Check for current item
        value_type current() const;  // Return the current item's value

    private:
        // Linked list implementation using pointers to track the sequence
        node<Item>* head_ptr;   // Pointer to the first node in the sequence
        node<Item>* tail_ptr;   // Pointer to the last node in the sequence
        node<Item>* cursor;     // Pointer to the current item (if any)
        node<Item>* precursor;  // Pointer to the node before cursor (or NULL if cursor is at head)
        size_type many_nodes;   // Number of items in the sequence
    };
}

// The implementation of a template class must be included in its header file:
#include "sequence4.template"
#endif
