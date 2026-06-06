#include "movie.h"

Movie::Movie() : genre(' '), stock(0), year(0) {}

bool Movie::borrow() {
    if (stock <= 0) return false;
    --stock;
    return true;
}

bool Movie::returnCopy() {
    ++stock;
    return true;
}
