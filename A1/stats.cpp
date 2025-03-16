
// Assignment 1

// FILE: stats.cpp
// brief Implementation of the statistician class.

#include <cassert>  // Provides assert
#include <iostream>
#include <limits> // for numeric limits
#include "stats.h"

namespace CISP430_A1 {

	// Constructor
	statistician::statistician() : count(0), total(0.0), tiniest(0.0), largest(0.0) {}

	// Add a new number to the sequence
	void statistician::next(double r) {
		if (count == 0) {
			tiniest = r;
			largest = r;
		}
		else {
			if (r < tiniest) tiniest = r;
			if (r > largest) largest = r;
		}
		total += r;
		count++;
	}

	// Reset the statistician
	void statistician::reset() {
		count = 0;
		total = 0.0;
		tiniest = 0.0;
		largest = 0.0;
	}

	// Calculate the mean of the sequence
	double statistician::mean() const {
		assert(count > 0);
		return total / count;
	}

	// Return the smallest number in the sequence
	double statistician::minimum() const {
		assert(count > 0);
		return tiniest;
	}

	// Return the largest number in the sequence
	double statistician::maximum() const {
		assert(count > 0);
		return largest;
	}

	// Overload the + operator to add two statisticians
	statistician operator+(const statistician& s1, const statistician& s2) {
		statistician result;

		result.count = s1.count + s2.count;
		result.total = s1.total + s2.total;

		if (s1.count == 0) {
			result.tiniest = s2.tiniest;
			result.largest = s2.largest;
		}
		else if (s2.count == 0) {
			result.tiniest = s1.tiniest;
			result.largest = s1.largest;
		}
		else {
			result.tiniest = std::min(s1.tiniest, s2.tiniest);
			result.largest = std::max(s1.largest, s2.largest);
		}

		return result;
	}

	// Overloaded * operator
	statistician operator*(double scale, const statistician& s) {
		statistician result;
		if (s.count > 0) {
			result.count = s.count;
			result.total = s.total * scale;
			if (scale >= 0) {
				result.tiniest = s.tiniest * scale;
				result.largest = s.largest * scale;
			}
			else {
				result.tiniest = s.largest * scale;
				result.largest = s.tiniest * scale;
			}
		}
		return result;
	}

	// Overloaded == operator
	bool operator==(const statistician& s1, const statistician& s2) {
		if (s1.count == 0 && s2.count == 0) {
			return true;
		}
		return s1.count == s2.count &&
			s1.total == s2.total &&
			s1.tiniest == s2.tiniest &&
			s1.largest == s2.largest;
	}


} // namespace CISP430_A1
