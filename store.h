// ---------------------------------- store.h ----------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the Store class, the top-level driver for the movie rental
//          system. Store owns three genre BSTrees and a customer HashTable, and
//          coordinates inventory loading, customer loading, and command processing.
// ----------------------------------------------------------------------------

#pragma once
#include <string>
#include "bstree.h"
#include "hashtable.h"

class Movie;
class Transaction;
class Customer;

class Store {
public:
    Store();

    void buildInventory(const std::string& path);   // load movies from file into genre trees
    void buildCustomers(const std::string& path);   // load customers from file into hash table
    void processCommands(const std::string& path);  // read and execute each command line

    Customer* findCustomer(int id);                  // wrapper around HashTable::find
    Movie* findMovie(char genre, const Movie& key);  // route lookup to the correct BSTree

    BSTree& getComedyTree() { return comedyTree; }   // used by InventoryTxn
    BSTree& getDramaTree() { return dramaTree; }
    BSTree& getClassicTree() { return classicTree; }

    static Movie* makeMovie(char code);              // factory: 'F'->Comedy, 'D'->Drama, 'C'->Classic
    static Transaction* makeTransaction(char action); // factory: 'B','R','I','H' or nullptr

private:
    BSTree comedyTree;    // sorted by title, then year
    BSTree dramaTree;     // sorted by director, then title
    BSTree classicTree;   // sorted by year, month, then major actor
    HashTable customers;
};
