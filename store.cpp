// --------------------------------- store.cpp ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Store driver. Reads movie, customer, and command files
//          line by line, delegates object creation to the factory methods, and
//          runs each transaction against the live inventory and customer records.
// ----------------------------------------------------------------------------

#include "store.h"
#include "movie.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"
#include "transaction.h"
#include "borrow.h"
#include "return_txn.h"
#include "inventory_txn.h"
#include "history_txn.h"
#include "customer.h"
#include <fstream>
#include <sstream>
#include <iostream>

// ---------------------------------- Store() ----------------------------------
// Default constructor.
// preconditions:  none
// postconditions: three empty BSTrees and an empty HashTable ready for loading
// ----------------------------------------------------------------------------
Store::Store() {}

// ------------------------------ buildInventory() -----------------------------
// Reads the movie file and inserts each valid movie into the appropriate BSTree.
// preconditions:  path refers to a readable file in the expected format
// postconditions: all valid movie lines parsed and inserted; invalid genre codes
//                 skipped with an error to stderr; file closed on return
// ----------------------------------------------------------------------------
void Store::buildInventory(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "ERROR: Cannot open " << path << "\n";
        return;
    }
    std::string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        char genreCode;
        ss >> genreCode;
        Movie* m = makeMovie(genreCode);
        if (!m) {
            std::cerr << "ERROR: Invalid movie type '" << genreCode
                      << "' — discarding line\n";
            continue;
        }
        m->setData(ss);
        if (genreCode == 'F')      comedyTree.insert(m);
        else if (genreCode == 'D') dramaTree.insert(m);
        else if (genreCode == 'C') classicTree.insert(m);
    }
}

// ------------------------------ buildCustomers() -----------------------------
// Reads the customer file and inserts each customer into the hash table.
// preconditions:  path refers to a readable file; each line holds "id last first"
// postconditions: all customers inserted; file closed on return
// ----------------------------------------------------------------------------
void Store::buildCustomers(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "ERROR: Cannot open " << path << "\n";
        return;
    }
    int id;
    std::string last, first;
    while (in >> id >> last >> first) {
        Customer c(id, last, first);
        customers.insert(c);
    }
}

// ------------------------------ processCommands() ----------------------------
// Reads the command file and executes each transaction against the store.
// preconditions:  buildInventory() and buildCustomers() have been called;
//                 path refers to a readable command file
// postconditions: each valid command executed; failed transactions deleted;
//                 successful transactions transferred to customer ownership;
//                 unknown action codes reported to stderr and skipped
// ----------------------------------------------------------------------------
void Store::processCommands(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "ERROR: Cannot open " << path << "\n";
        return;
    }
    std::string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        char action;
        ss >> action;
        Transaction* txn = makeTransaction(action);
        if (!txn) {
            std::cerr << "ERROR: Unknown action code '" << action
                      << "' — discarding command\n";
            continue;
        }
        txn->setData(ss);
        bool ok = txn->doTransaction(*this);
        // Borrow and Return transfer ownership to Customer on success; Inventory
        // and History never do, so delete them here regardless of outcome.
        if (!ok || txn->getAction() == 'I' || txn->getAction() == 'H') {
            delete txn;
        }
    }
}

// ------------------------------ findCustomer() -------------------------------
// Looks up a customer by their 4-digit ID.
// preconditions:  none
// postconditions: returns pointer to the Customer in the hash table, or nullptr
// ----------------------------------------------------------------------------
Customer* Store::findCustomer(int id) {
    return customers.find(id);
}

// ------------------------------- findMovie() ---------------------------------
// Routes a movie lookup to the BSTree for the given genre.
// preconditions:  key fields are set on the key movie object
// postconditions: returns pointer to the matching Movie, or nullptr if not found
// ----------------------------------------------------------------------------
Movie* Store::findMovie(char genre, const Movie& key) {
    if (genre == 'F') return comedyTree.find(key);
    if (genre == 'D') return dramaTree.find(key);
    if (genre == 'C') return classicTree.find(key);
    return nullptr;
}

// ================================ Factories ==================================

// -------------------------------- makeMovie() --------------------------------
// Creates and returns a heap-allocated Movie subclass for the given genre code.
// preconditions:  none
// postconditions: returns new Comedy, Drama, or Classic; returns nullptr for
//                 unrecognized codes so the caller can log and skip the line
// ----------------------------------------------------------------------------
Movie* Store::makeMovie(char code) {
    switch (code) {
        case 'F': return new Comedy();
        case 'D': return new Drama();
        case 'C': return new Classic();
        default:  return nullptr;
    }
}

// ----------------------------- makeTransaction() -----------------------------
// Creates and returns a heap-allocated Transaction subclass for the given action.
// preconditions:  none
// postconditions: returns new Borrow, ReturnTxn, InventoryTxn, or HistoryTxn;
//                 returns nullptr for unrecognized codes
// ----------------------------------------------------------------------------
Transaction* Store::makeTransaction(char action) {
    switch (action) {
        case 'B': return new Borrow();
        case 'R': return new ReturnTxn();
        case 'I': return new InventoryTxn();
        case 'H': return new HistoryTxn();
        default:  return nullptr;
    }
}
