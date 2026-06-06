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

Store::Store() {}

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
        if (!txn->doTransaction(*this)) {
            delete txn;
        }
    }
}

Customer* Store::findCustomer(int id) {
    return customers.find(id);
}

Movie* Store::findMovie(char genre, const Movie& key) {
    if (genre == 'F') return comedyTree.find(key);
    if (genre == 'D') return dramaTree.find(key);
    if (genre == 'C') return classicTree.find(key);
    return nullptr;
}

Movie* Store::makeMovie(char code) {
    switch (code) {
        case 'F': return new Comedy();
        case 'D': return new Drama();
        case 'C': return new Classic();
        default:  return nullptr;
    }
}

Transaction* Store::makeTransaction(char action) {
    switch (action) {
        case 'B': return new Borrow();
        case 'R': return new ReturnTxn();
        case 'I': return new InventoryTxn();
        case 'H': return new HistoryTxn();
        default:  return nullptr;
    }
}
