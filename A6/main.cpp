// FILE: main.cpp

// Assignment 6
// 
// PROGRAM DESCRIPTION: This is a driver program to test the functionality of the 
// Table class that implements a chained hash table.
//
// IMPLEMENTATION NOTES:
// 1. The program tests all major operations of the Table class: constructor, 
//    insertion, removal, assignment operator, and size queries.
// 2. The test uses a simple Record structure with an integer key field.
// 3. Random numbers are used to generate data for the tests.
// 4. The program demonstrates the effects of various operations by displaying
//    the contents of the table before and after each operation.

#include <iostream>  // Provides cout and cin
#include <cstdlib>   // Provides EXIT_SUCCESS and rand
#include <ctime>     // Provides time for random seed
#include <string>    // Provides string
#include "table2.h"  // Provides the Table class

//===========================================================================
// RECORD STRUCT
//===========================================================================
// Purpose: Define a simple record structure for testing the Table class
// Components:
// - key: An integer that uniquely identifies the record
// - Default constructor: Initializes key to 0
// - Parameterized constructor: Sets key to the provided value
//===========================================================================
struct Record
{
    int key;
    // Additional data can be added here if needed

    Record() { key = 0; }
    Record(int k) { key = k; }
};

//===========================================================================
// DISPLAY_TABLE FUNCTION
//===========================================================================
// Purpose: Display the contents of a Table object
// Algorithm:
// 1. Print the total number of records in the table
// 2. Iterate through all buckets in the table
// 3. Call the table's print function for each bucket
// Precondition: 
// - table is a valid Table<Record> object
// - table_num is 1 or 2 (used to identify first or second table in output)
// Postcondition: 
// - The table's information is displayed to the console
// - The table itself is unchanged
// Time complexity: O(TABLE_SIZE + n) where n is the total number of records
//===========================================================================
void display_table(const Table<Record>& table, int table_num)
{
    std::cout << "          Total records in the " << (table_num == 1 ? "first" : "second") << " Table object is " << table.size() << std::endl;
    std::cout << "          Contains of the " << (table_num == 1 ? "first" : "second") << " object display at below:" << std::endl;

    for (size_t i = 0; i < TABLE_SIZE; i++)
    {
        table.print(i);
    }
}

//===========================================================================
// MAIN FUNCTION
//===========================================================================
// Purpose: Test all the major functionality of the Table class
// Algorithm:
// The program performs the following sequence of operations:
// a. Create two empty Table objects
// b. Display the initial state of both tables
// c. Insert 70 random numbers into each table
// d. Display both tables after insertion
// e. Remove all data from the first table
// f. Display both tables after removal
// g. Assign the second table to the first table
// h. Display both tables after assignment
// Postcondition: Program exits with success status
//===========================================================================
int main()
{
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // Step a: Instantiate two Table objects
    Table<Record> table1;
    Table<Record> table2;

    // Step b: Display the two Table objects' information
    std::cout << "Instantiate two Table objects.\n" << std::endl;
    display_table(table1, 1);
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    display_table(table2, 2);
    std::cout << "=============================================================================" << std::endl;

    // Step c: Generate 70 random numbers for each table
    std::cout << "\n\n\n**Using random number generator generates 70 numbers each for the objects.**\n\n" << std::endl;

    for (int i = 0; i < 70; i++)
    {
        // Generate random numbers between 0-200 for each table
        int rand_num1 = std::rand() % 201;
        int rand_num2 = std::rand() % 201;

        // Create Record objects with the random numbers as keys
        Record record1(rand_num1);
        Record record2(rand_num2);

        // Insert the records into their respective tables
        table1.insert(record1);
        table2.insert(record2);
    }

    // Step d: Display the two Table objects' information after insertions
    display_table(table1, 1);
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    display_table(table2, 2);
    std::cout << "=============================================================================" << std::endl;

    // Step e: Remove all data from table1
    std::cout << "\n\n\n** Calling remove function removes all the contents in first object. **\n\n" << std::endl;

    // Attempt to remove all possible keys (0-200) from table1
    for (int i = 0; i < 201; i++)
    {
        table1.remove(i);
    }

    // Step f: Display the two Table objects' information after removal
    display_table(table1, 1);
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    display_table(table2, 2);
    std::cout << "=============================================================================" << std::endl;

    // Step g: Assign table2 to table1
    std::cout << "\n\n\n** Using TBObject1 = TBObject2 displays the assignment operator overloading. **\n\n" << std::endl;
    table1 = table2;

    // Step h: Display the two Table objects' information after assignment
    display_table(table1, 1);
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    display_table(table2, 2);
    std::cout << "=============================================================================" << std::endl;

    return EXIT_SUCCESS;
}