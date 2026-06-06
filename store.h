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

    void buildInventory(const std::string& path);
    void buildCustomers(const std::string& path);
    void processCommands(const std::string& path);

    Customer* findCustomer(int id);
    Movie* findMovie(char genre, const Movie& key);

    BSTree& getComedyTree() { return comedyTree; }
    BSTree& getDramaTree() { return dramaTree; }
    BSTree& getClassicTree() { return classicTree; }

    static Movie* makeMovie(char code);
    static Transaction* makeTransaction(char action);

private:
    BSTree comedyTree;
    BSTree dramaTree;
    BSTree classicTree;
    HashTable customers;
};
