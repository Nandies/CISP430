// FILE: Permute.h
// Assignment 5
//
// DESCRIPTION:
// This header file defines the Permute class which generates all possible permutations
// of a first string followed by a second string. The class uses a linked list to store
// the permutations and provides methods to generate and display them.

#ifndef PERMUTE_H
#define PERMUTE_H

#include <string>
#include "Node.h"

class Permute {
private:
    Node* firstNode;       // Pointer to first node in the linked list
    Node* lastNode;        // Pointer to last node in the linked list
    int total;             // Total number of permutations
    std::string firstString;    // First string (to be permuted)
    std::string secondString;   // Second string (appended to permutations)

public:
    // Constructor
    // Purpose: Create a new Permute object and generate all permutations
    // Parameters:
    //   - first: The first string whose characters will be permuted
    //   - second: The second string that will be appended to each permutation
    Permute(std::string first, std::string second);

    // Recursive permutation function
    // Purpose: Generate all possible permutations of the first string + second string
    // Parameters:
    //   - prefix: Characters already selected for the current permutation
    //   - remaining: Characters still available to be added to the permutation
    void permutation(std::string prefix, std::string remaining);

    // Print function
    // Purpose: Display the input strings, total permutation count, and all permutations
    void print();

    // Destructor
    // Purpose: Free all dynamically allocated memory in the linked list
    ~Permute();
};

#endif // PERMUTE_H