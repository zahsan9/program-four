// ------------------------------ transaction.cpp ------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Transaction base class constructor. All subclass
//          behavior is defined in the respective subclass .cpp files.
// ----------------------------------------------------------------------------

#include "transaction.h"

// ------------------------------ Transaction() --------------------------------
// Default constructor.
// preconditions:  none
// postconditions: customerID = 0, action = ' ', movie = nullptr
// ----------------------------------------------------------------------------
Transaction::Transaction() : customerID(0), action(' '), movie(nullptr) {}
