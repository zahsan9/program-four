#include "hashtable.h"

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i)
        occupied[i] = false;
}

void HashTable::insert(const Customer& c) {
    int id = c.getID();
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int slot = (id % TABLE_SIZE + i * i) % TABLE_SIZE;
        if (!occupied[slot]) {
            table[slot] = c;
            occupied[slot] = true;
            return;
        }
    }
}

Customer* HashTable::find(int id) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int slot = (id % TABLE_SIZE + i * i) % TABLE_SIZE;
        if (!occupied[slot]) return nullptr;
        if (table[slot].getID() == id) return &table[slot];
    }
    return nullptr;
}
