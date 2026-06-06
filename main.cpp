// ---------------------------------- main.cpp ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Entry point for the movie rental store program. Creates a Store,
//          loads the movie catalog and customer list, then processes all
//          transaction commands from the provided input files.
// ----------------------------------------------------------------------------

#include "store.h"

// ---------------------------------- main() -----------------------------------
// preconditions:  data/data4movies.txt, data/data4customers.txt,
//                 data/data4commands.txt exist relative to the working directory
// postconditions: all commands processed; output written to stdout; errors to
//                 stderr; returns 0
// ----------------------------------------------------------------------------
int main() {
    Store store;
    store.buildInventory("data/data4movies.txt");
    store.buildCustomers("data/data4customers.txt");
    store.processCommands("data/data4commands.txt");
    return 0;
}
