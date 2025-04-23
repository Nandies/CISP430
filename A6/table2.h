// FILE: table2.h

// Assignment 6
// 
// CLASS PROVIDED: Table (a template container class for storing records)
//
// IMPLEMENTATION NOTES:
// 1. The Table class implements a hash table using chained hashing for
//    collision resolution.
// 2. Records are stored in linked lists attached to each hash table bucket.
// 3. The template parameter RecordType must have an integer key field.
// 4. The implementation includes proper memory management with copy constructor,
//    assignment operator, and destructor to handle dynamic memory allocation.
// 5. This design provides efficient insertion, removal, and searching operations.

#ifndef TABLE2_H
#define TABLE2_H
#include <stdlib.h> // Provides size_t
#include "link2.h" // Provides the linked list toolkit

// Constants
const size_t TABLE_SIZE = 10; // Size of the hash table

//===========================================================================
// TABLE CLASS TEMPLATE
//===========================================================================
// Purpose: Implements a hash table for storing records
// Template parameter:
// - RecordType: The type of records stored in the table
//   RecordType must have:
//   - default constructor
//   - copy constructor
//   - assignment operator
//   - an integer member variable called key
//
// Invariants:
// - data[0..TABLE_SIZE-1] is an array of pointers to linked lists of records
// - For any record with key k, it is stored in the list at data[hash(k)]
// - total_records accurately tracks the total number of records in all lists
//===========================================================================
template <class RecordType>
class Table
{
public:
    //===========================================================================
    // CONSTRUCTOR
    //===========================================================================
    // Purpose: Create an empty table
    // Postcondition: 
    // - All entries in data array are initialized to NULL (empty lists)
    // - total_records is set to 0
    // Time complexity: O(TABLE_SIZE) - constant time since TABLE_SIZE is fixed
    //===========================================================================
    Table();

    //===========================================================================
    // COPY CONSTRUCTOR
    //===========================================================================
    // Purpose: Create a deep copy of another Table
    // Precondition: source is a valid Table object
    // Postcondition: 
    // - This table contains exact copies of all records from source
    // - Changes to source afterward won't affect this table (deep copy)
    // Time complexity: O(n) where n is the total number of records in source
    //===========================================================================
    Table(const Table<RecordType>& source);

    //===========================================================================
    // ASSIGNMENT OPERATOR
    //===========================================================================
    // Purpose: Assign this table to be a copy of another table
    // Precondition: source is a valid Table object
    // Postcondition: 
    // - This table contains exact copies of all records from source
    // - Previous contents of this table are properly deallocated
    // - Self-assignment is handled correctly (no changes if this == &source)
    // - Returns a reference to this table
    // Time complexity: O(m+n) where m is current size and n is source size
    //===========================================================================
    Table<RecordType>& operator=(const Table<RecordType>& source);

    //===========================================================================
    // DESTRUCTOR
    //===========================================================================
    // Purpose: Free all dynamically allocated memory used by this table
    // Postcondition: 
    // - All linked lists and their nodes are properly deallocated
    // - All entries in data array are set to NULL
    // - total_records is reset to 0
    // Time complexity: O(n) where n is the total number of records
    //===========================================================================
    ~Table();

    //===========================================================================
    // INSERT FUNCTION
    //===========================================================================
    // Purpose: Insert a record into the table
    // Algorithm:
    // 1. Calculate the hash value for the record's key
    // 2. Check if the key already exists in the list at that position
    // 3. If the key exists, replace the data
    // 4. If the key doesn't exist, add a new node to the list
    // Precondition: entry is a valid RecordType object with a key value
    // Postcondition: 
    // - If entry's key wasn't in the table, a new record is inserted
    // - If entry's key was already in the table, the data is updated
    // - total_records is incremented only if a new record was added
    // Time complexity: O(L) where L is the length of the list at the hash position
    //===========================================================================
    void insert(const RecordType& entry);

    //===========================================================================
    // REMOVE FUNCTION
    //===========================================================================
    // Purpose: Remove a record with the specified key from the table
    // Algorithm:
    // 1. Calculate the hash value for the key
    // 2. Search for the key in the list at that position
    // 3. If found, remove the node containing that key
    // Precondition: key is an integer
    // Postcondition: 
    // - If a record with the given key existed, it is removed
    // - If no record with the key existed, the table is unchanged
    // - total_records is decremented if a record was removed
    // Time complexity: O(L) where L is the length of the list at the hash position
    //===========================================================================
    void remove(int key);

    //===========================================================================
    // PRINT FUNCTION
    //===========================================================================
    // Purpose: Print the contents of a hash table bucket
    // Algorithm:
    // 1. Check if the specified index has any records
    // 2. If empty, print a NULL indicator
    // 3. If not empty, print all keys in the linked list at that index
    // Precondition: index is a valid index in the range [0, TABLE_SIZE-1]
    // Postcondition: 
    // - The contents of the specified bucket are displayed
    // - The table is unchanged
    // Time complexity: O(L) where L is the length of the list at the specified index
    //===========================================================================
    void print(int index) const;

    //===========================================================================
    // IS_PRESENT FUNCTION
    //===========================================================================
    // Purpose: Check if a record with the same key as target exists in the table
    // Algorithm:
    // 1. Calculate the hash value for the target's key
    // 2. Search for the key in the list at that position
    // Precondition: target is a valid RecordType object with a key value
    // Postcondition: 
    // - Returns true if a record with the same key exists
    // - Returns false otherwise
    // - The table is unchanged
    // Time complexity: O(L) where L is the length of the list at the hash position
    //===========================================================================
    bool is_present(const RecordType& target) const;

    //===========================================================================
    // FIND FUNCTION
    //===========================================================================
    // Purpose: Find a record with the specified key
    // Algorithm:
    // 1. Calculate the hash value for the key
    // 2. Search for the key in the list at that position
    // 3. Set found to true/false based on whether the key was found
    // 4. If found, copy the record data to result
    // Precondition: key is an integer
    // Postcondition: 
    // - found is set to true if a record with the key exists, false otherwise
    // - If found is true, result contains a copy of the record
    // - If found is false, result is unchanged
    // - The table is unchanged
    // Time complexity: O(L) where L is the length of the list at the hash position
    //===========================================================================
    void find(int key, bool& found, RecordType& result) const;

    //===========================================================================
    // SIZE FUNCTION
    //===========================================================================
    // Purpose: Get the total number of records in the table
    // Postcondition: 
    // - Returns the value of total_records
    // - The table is unchanged
    // Time complexity: O(1) - constant time operation
    //===========================================================================
    size_t size() const;

private:
    Node<RecordType>* data[TABLE_SIZE];  // Array of pointers to linked lists
    size_t total_records;               // Count of total records in the table

    //===========================================================================
    // HASH FUNCTION
    //===========================================================================
    // Purpose: Calculate the hash value for a key
    // Algorithm: Simple modulo hashing - key mod TABLE_SIZE
    // Precondition: key is an integer
    // Postcondition: 
    // - Returns an index in the range [0, TABLE_SIZE-1]
    // Time complexity: O(1) - constant time operation
    //===========================================================================
    size_t hash(int key) const;

    //===========================================================================
    // FIND_NODE FUNCTION (HELPER)
    //===========================================================================
    // Purpose: Find a node with the specified key in a linked list
    // Algorithm:
    // 1. Start at the beginning of the list
    // 2. Traverse the list, comparing each node's key with the target
    // 3. Track both the current node and the previous node
    // Precondition: 
    // - cursor initially points to the head of a linked list
    // - precursor is used to track the node before cursor
    // - key is an integer to search for
    // Postcondition: 
    // - Returns pointer to the node containing key, or NULL if not found
    // - cursor points to the found node or NULL if not found
    // - precursor points to the node before the found node, or NULL if found at head
    // Time complexity: O(L) where L is the length of the linked list
    //===========================================================================
    Node<RecordType>* find_node(Node<RecordType>*& cursor, Node<RecordType>*& precursor, int key) const;
};

#include "table2.template"  // Include the implementation
#endif