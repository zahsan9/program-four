#include "store.h"

int main() {
    Store store;
    store.buildInventory("data4movies.txt");
    store.buildCustomers("data4customers.txt");
    store.processCommands("data4commands.txt");
    return 0;
}
