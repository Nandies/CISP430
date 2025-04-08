// FILE: main.cpp
// Assignment 5
//
// DESCRIPTION:
// This is the driver program that tests the Permute class by creating
// eight Permute objects with different combinations of input strings.
// It demonstrates how the Permute class generates and displays permutations
// of characters from first string followed by the second string.

#include <iostream>
#include "Permute.h"

int main() {
    // Create an array of Permute pointers
    // Purpose: Store pointers to eight Permute objects for testing
    Permute* permutes[8];

    // Initialize with the eight test cases specified in the assignment
    // Each test case has different combinations of first and second strings
    permutes[0] = new Permute("", "");                // Both strings empty
    permutes[1] = new Permute("", "CATMAN");          // First string empty
    permutes[2] = new Permute("C", "ATMAN");          // First string with 1 character
    permutes[3] = new Permute("CA", "TMAN");          // First string with 2 characters
    permutes[4] = new Permute("CAT", "MAN");          // First string with 3 characters
    permutes[5] = new Permute("CATM", "AN");          // First string with 4 characters
    permutes[6] = new Permute("CATMA", "N");          // First string with 5 characters
    permutes[7] = new Permute("CATMAN", "");          // Second string empty

    // Print results for each test case
    // Iterates through the array and calls print() for each Permute object
    for (int i = 0; i < 8; i++) {
        permutes[i]->print();
    }

    // Free memory allocated for the Permute objects
    // Prevents memory leaks by deleting all dynamically allocated objects
    for (int i = 0; i < 8; i++) {
        delete permutes[i];
    }

    // Wait for user input before exiting
    std::cout << "\nPress any key to continue . . .";
    std::cin.get();

    return 0;
}