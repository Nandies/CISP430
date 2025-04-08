// FILE: Permute.cpp
// Assignment 5
//
// DESCRIPTION:
// This file implements the Permute class methods for generating and storing
// permutations of character strings. It contains the implementation of the constructor,
// the recursive permutation algorithm, the print function for displaying results,
// and the destructor to properly free allocated memory.

#include <iostream>
#include "Permute.h"

// Constructor
// Purpose: Initialize a new Permute object with given strings and generate permutations
// Parameters:
//   - first: The first string whose characters will be permuted
//   - second: The second string that will be appended to each permutation
// Postcondition: All permutations are generated and stored in the linked list
Permute::Permute(std::string first, std::string second) {
    firstString = first;
    secondString = second;
    firstNode = nullptr;
    lastNode = nullptr;
    total = 0;

    // Generate permutations
    if (!first.empty()) {
        // If first string is not empty, generate permutations recursively
        permutation("", first);
    }
    else if (!second.empty()) {
        // Special case: first string is empty, add only second string
        Node* newNode = new Node(second);
        firstNode = newNode;
        lastNode = newNode;
        total = 1;
    }
    // If both strings are empty, total remains 0
}

// Recursive permutation function
// Purpose: Generate all possible permutations of a string using recursion
// Parameters:
//   - prefix: Characters already selected for the current permutation
//   - remaining: Characters still available to be added to the permutation
// Algorithm: For each character in remaining, add it to prefix and recursively permute the rest
// Postcondition: All permutations are added to the linked list
void Permute::permutation(std::string prefix, std::string remaining) {
    if (remaining.empty()) {
        // Base case: No more characters to permute
        // Add completed permutation (prefix + secondString) to linked list
        std::string result = prefix + secondString;

        Node* newNode = new Node(result);

        if (firstNode == nullptr) {
            // If this is the first node, update both firstNode and lastNode
            firstNode = newNode;
            lastNode = newNode;
        }
        else {
            // Otherwise, add to the end of the list
            lastNode->p = newNode;
            lastNode = newNode;
        }

        total++; // Increment the total count of permutations
    }
    else {
        // Recursive case: Select each remaining character in turn
        for (size_t i = 0; i < remaining.length(); i++) {
            // Choose one character to add to the prefix
            std::string newPrefix = prefix + remaining[i];

            // Remove the chosen character from remaining
            std::string newRemaining = remaining.substr(0, i) + remaining.substr(i + 1);

            // Recursively permute the new prefix and remaining characters
            permutation(newPrefix, newRemaining);
        }
    }
}

// Print function to display results
// Purpose: Display the input strings, total permutation count, and all permutations
// Postcondition: All information about the permutations is displayed to standard output
void Permute::print() {
    // Print the input strings
    std::cout << "\nString 1 for this object is: " << firstString << std::endl;
    std::cout << "String 2 for this object is: " << secondString << std::endl;

    if (total == 0) {
        // Case 1: No permutations
        std::cout << "There is no permutation." << std::endl;
    }
    else if (total == 1) {
        // Case 2: Only one permutation
        std::cout << "The total possible permutation is " << total << std::endl;
        std::cout << "That is:" << std::endl;

        Node* current = firstNode;
        std::cout << current->data << std::endl;
    }
    else {
        // Case 3: Multiple permutations
        std::cout << "The total possible permutation is " << total << std::endl;
        std::cout << "They are:" << std::endl;

        Node* current = firstNode;
        int count = 0;

        // Traverse the linked list and print each permutation
        while (current != nullptr) {
            std::cout << current->data << "  ";
            count++;

            // Format output: 4 per row if total < 100, otherwise 9 per row
            if ((total < 100 && count % 4 == 0) || (total >= 100 && count % 9 == 0)) {
                std::cout << std::endl;
            }

            current = current->p;
        }

        // Ensure the last line ends with a newline if needed
        if (count % (total < 100 ? 4 : 9) != 0) {
            std::cout << std::endl;
        }
    }
}

// Destructor
// Purpose: Free all dynamically allocated memory in the linked list
// Postcondition: All Node objects are properly deleted to prevent memory leaks
Permute::~Permute() {
    Node* current = firstNode;
    while (current != nullptr) {
        Node* temp = current; // Save the current node
        current = current->p; // Move to the next node
        delete temp;          // Delete the saved node
    }
}