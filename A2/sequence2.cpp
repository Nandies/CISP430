// CISP 430 Spring 2025 Fernando Mendoza W2008623
// Assignment #
// FILE: sequence2.cpp
// (This file implements the sequence class as declared in sequence2.h.
//  It uses a dynamic array that grows as needed (by at least 10% increments)
//  and provides proper copy control including a copy constructor, assignment operator,
//  and destructor. The design and techniques used here are based on the approaches
//  described in Michael Main and Walter Savitch's Data Structures and Other Objects Using C++ (4th Edition).
//  Detailed comments are included to explain every part of the implementation.)

#include "sequence2.h"    // Includes the declaration of the sequence class.
#include <cassert>        // For assert to check preconditions

namespace CISP430_A2
{
    // -------------------------------------------------------------------------
    // Constructor: sequence
    // Purpose: Create a new sequence with an initial capacity (default CAPACITY).
    // Parameters:
    //   entry - The initial capacity for the dynamic array.
    // Postcondition:
    //   - A dynamic array of size 'entry' is allocated.
    //   - The number of used elements is initialized to 0.
    //   - The current index is set to 0.
    // -------------------------------------------------------------------------
    sequence::sequence(size_type entry)
        : used(0), capacity(entry), current_index(0)
    {
        // Allocate a dynamic array for storing the sequence items.
        data = new value_type[capacity];
    }

    // -------------------------------------------------------------------------
    // Copy Constructor: sequence
    // Purpose: Create a new sequence as an exact copy of an existing sequence.
    // Parameters:
    //   entry - The sequence to be copied.
    // Postcondition:
    //   - A new dynamic array is allocated with the same capacity as 'entry'.
    //   - All items from 'entry' are copied.
    //   - The used count and current index are copied.
    // -------------------------------------------------------------------------
    sequence::sequence(const sequence& entry)
        : used(entry.used), capacity(entry.capacity), current_index(entry.current_index)
    {
        // Allocate new dynamic memory with the same capacity as the original sequence.
        data = new value_type[capacity];
        // Copy each item from the original sequence into the new array.
        for (size_type i = 0; i < used; ++i)
        {
            data[i] = entry.data[i];
        }
    }

    // -------------------------------------------------------------------------
    // Destructor: ~sequence
    // Purpose: Release the dynamic memory allocated for the sequence.
    // Postcondition:
    //   - The dynamic array is deallocated.
    // -------------------------------------------------------------------------
    sequence::~sequence()
    {
        delete[] data;
    }

    // -------------------------------------------------------------------------
    // Member Function: start
    // Purpose: Set the current index to the first element of the sequence.
    // Postcondition:
    //   - If the sequence is not empty, the first item becomes the current item.
    // -------------------------------------------------------------------------
    void sequence::start()
    {
        if (used > 0)
        {
            current_index = 0;
        }
    }

    // -------------------------------------------------------------------------
    // Member Function: advance
    // Purpose: Move the current index to the next item in the sequence.
    // Precondition:
    //   - is_item() must return true (i.e., there is a valid current item).
    // Postcondition:
    //   - The current index is incremented.
    //   - If the current item was the last element, there is no current item.
    // -------------------------------------------------------------------------
    void sequence::advance()
    {
        // Ensure there is a current item.
        assert(is_item());
        ++current_index;
    }

    // -------------------------------------------------------------------------
    // Member Function: insert
    // Purpose: Insert a new entry before the current item.
    // Parameters:
    //   entry - The value to be inserted.
    // Postcondition:
    //   - If no current item exists, the new entry is inserted at the beginning.
    //   - Otherwise, the entry is inserted just before the current item.
    //   - If the dynamic array is full, it is resized (increased by at least 10%).
    //   - The newly inserted entry becomes the current item.
    // -------------------------------------------------------------------------
    void sequence::insert(const value_type& entry)
    {
        // If the array is full, resize it by increasing its capacity by at least 10%.
        if (used >= capacity)
        {
            size_type increase = capacity / 10;
            if (increase == 0)
            {
                increase = 1; // Ensure at least one extra space if capacity is small.
            }
            resize(capacity + increase);
        }

        // If there is no current item, insert at the beginning.
        if (!is_item())
        {
            current_index = 0;
        }

        // Shift all items starting at current_index one position to the right
        // to create space for the new entry.
        for (size_type i = used; i > current_index; --i)
        {
            data[i] = data[i - 1];
        }

        // Insert the new entry at the current_index.
        data[current_index] = entry;
        ++used;  // Increase the count of used elements.
    }

    // -------------------------------------------------------------------------
    // Member Function: attach
    // Purpose: Insert a new entry after the current item.
    // Parameters:
    //   entry - The value to be attached.
    // Postcondition:
    //   - If no current item exists, the new entry is appended at the end.
    //   - Otherwise, the entry is inserted immediately after the current item.
    //   - If the dynamic array is full, it is resized (increased by at least 10%).
    //   - The newly attached entry becomes the current item.
    // -------------------------------------------------------------------------
    void sequence::attach(const value_type& entry)
    {
        // If the array is full, resize it.
        if (used >= capacity)
        {
            size_type increase = capacity / 10;
            if (increase == 0)
            {
                increase = 1;
            }
            resize(capacity + increase);
        }

        // Determine the index for the new entry:
        // If a current item exists, attach after it; otherwise, attach at the end.
        if (is_item())
        {
            ++current_index;
        }
        else
        {
            current_index = used;
        }

        // Shift all items from current_index onward one position to the right.
        for (size_type i = used; i > current_index; --i)
        {
            data[i] = data[i - 1];
        }

        // Insert the new entry at the current_index.
        data[current_index] = entry;
        ++used;  // Update the used count.
    }

    // -------------------------------------------------------------------------
    // Member Function: remove_current
    // Purpose: Remove the current item from the sequence.
    // Precondition:
    //   - is_item() must return true.
    // Postcondition:
    //   - The current item is removed.
    //   - All subsequent items are shifted one position to the left.
    //   - The item that followed the removed item becomes the new current item.
    // -------------------------------------------------------------------------
    void sequence::remove_current()
    {
        // Ensure there is a current item to remove.
        assert(is_item());

        // Shift items leftward to overwrite the current item.
        for (size_type i = current_index; i < used - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        --used;  // Decrement the count of used items.
        // current_index remains unchanged; if it now equals used, there is no current item.
    }

    // -------------------------------------------------------------------------
    // Member Function: resize
    // Purpose: Change the capacity of the sequence.
    // Parameters:
    //   new_capacity - The new capacity for the dynamic array.
    // Precondition:
    //   - new_capacity must be greater than the number of used items.
    // Postcondition:
    //   - A new dynamic array of size new_capacity is allocated.
    //   - All existing items are copied to the new array.
    //   - The old dynamic array is deallocated.
    // -------------------------------------------------------------------------
    void sequence::resize(size_type new_capacity)
    {
        // Verify that the new capacity is valid.
        assert(new_capacity > used);

        // Allocate a new dynamic array with the new capacity.
        value_type* new_data = new value_type[new_capacity];

        // Copy all existing items into the new array.
        for (size_type i = 0; i < used; ++i)
        {
            new_data[i] = data[i];
        }

        // Deallocate the old array.
        delete[] data;

        // Update data pointer and capacity.
        data = new_data;
        capacity = new_capacity;
    }

    // -------------------------------------------------------------------------
    // Member Function: operator=
    // Purpose: Overload the assignment operator to assign one sequence to another.
    // Parameters:
    //   other - The sequence object on the right-hand side.
    // Precondition:
    //   - Self-assignment is handled.
    // Postcondition:
    //   - The current sequence becomes a deep copy of 'other'.
    // -------------------------------------------------------------------------
    void sequence::operator=(const sequence& other)
    {
        // Handle self-assignment.
        if (this == &other)
            return;

        // Deallocate the existing dynamic array.
        delete[] data;

        // Copy over the capacity, number of used items, and current index.
        capacity = other.capacity;
        used = other.used;
        current_index = other.current_index;

        // Allocate a new dynamic array and copy items from 'other'.
        data = new value_type[capacity];
        for (size_type i = 0; i < used; ++i)
        {
            data[i] = other.data[i];
        }
    }

    // -------------------------------------------------------------------------
    // Member Function: size
    // Purpose: Return the number of items in the sequence.
    // Postcondition:
    //   - Returns the value of the 'used' member variable.
    // -------------------------------------------------------------------------
    sequence::size_type sequence::size() const
    {
        return used;
    }

    // -------------------------------------------------------------------------
    // Member Function: is_item
    // Purpose: Check if there is a valid current item.
    // Postcondition:
    //   - Returns true if current_index is less than used; otherwise, false.
    // -------------------------------------------------------------------------
    bool sequence::is_item() const
    {
        return current_index < used;
    }

    // -------------------------------------------------------------------------
    // Member Function: current
    // Purpose: Return the current item.
    // Precondition:
    //   - is_item() must return true.
    // Postcondition:
    //   - Returns the item at the current index.
    // -------------------------------------------------------------------------
    sequence::value_type sequence::current() const
    {
        // Ensure that a current item exists.
        assert(is_item());
        return data[current_index];
    }
} // End namespace CISP430_A2
