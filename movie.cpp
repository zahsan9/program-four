// --------------------------------- movie.cpp ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Movie base class constructor and the stock-management
//          methods shared by all genre subclasses.
// ----------------------------------------------------------------------------

#include "movie.h"

// ---------------------------------- Movie() ----------------------------------
// Default constructor.
// preconditions:  none
// postconditions: genre = ' ', stock = 0, year = 0; director and title empty
// ----------------------------------------------------------------------------
Movie::Movie() : genre(' '), stock(0), year(0) {}

// --------------------------------- borrow() ----------------------------------
// Decrements stock by one if a copy is available.
// preconditions:  none
// postconditions: stock decremented by 1 and returns true; or stock unchanged
//                 and returns false if stock was already 0
// ----------------------------------------------------------------------------
bool Movie::borrow() {
    if (stock <= 0) return false;
    --stock;
    return true;
}

// ------------------------------ returnCopy() ---------------------------------
// Increments stock by one.
// preconditions:  caller has verified the customer previously borrowed this movie
// postconditions: stock incremented by 1; always returns true
// ----------------------------------------------------------------------------
bool Movie::returnCopy() {
    ++stock;
    return true;
}
