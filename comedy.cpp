// -------------------------------- comedy.cpp ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Comedy genre subclass. Parses movie data, defines
//          sort and equality by title then year, and formats output.
// ----------------------------------------------------------------------------

#include "comedy.h"

static std::string trimStr(const std::string& s) {  // strip leading/trailing whitespace
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

// --------------------------------- Comedy() ----------------------------------
// Default constructor.
// preconditions:  none
// postconditions: genre set to 'F'; all inherited fields at Movie defaults
// ----------------------------------------------------------------------------
Comedy::Comedy() { genre = 'F'; }

// --------------------------------- setData() ---------------------------------
// Parses one inventory line after the genre character.
// preconditions:  in holds ", stock, director, title, year"
// postconditions: stock, director, title, and year populated from stream
// ----------------------------------------------------------------------------
void Comedy::setData(std::istream& in) {
    char ch;
    in >> ch;        // ','
    in >> stock;
    in >> ch;        // ','
    in.get(ch);      // ' '
    getline(in, director, ',');
    director = trimStr(director);
    getline(in, title, ',');
    title = trimStr(title);
    in >> year;
}

// ----------------------------- setSearchKey() --------------------------------
// Parses the search key fields from a borrow or return command.
// preconditions:  in holds " title, year"
// postconditions: title and year populated for subsequent BSTree lookup
// ----------------------------------------------------------------------------
void Comedy::setSearchKey(std::istream& in) {
    in.get(); // skip leading space
    getline(in, title, ',');
    title = trimStr(title);
    in >> year;
}

// -------------------------------- operator<() --------------------------------
// Less-than comparison used for BSTree insertion and traversal ordering.
// preconditions:  rhs is a Comedy (dynamic_cast assumed valid by caller)
// postconditions: returns true if this comedy sorts before rhs by title, then year
// ----------------------------------------------------------------------------
bool Comedy::operator<(const Movie& rhs) const {
    const Comedy& r = dynamic_cast<const Comedy&>(rhs);
    if (title != r.title) return title < r.title;
    return year < r.year;
}

// ------------------------------- operator==() --------------------------------
// Equality check used by BSTree for stock merging and find.
// preconditions:  none
// postconditions: returns true if rhs is a Comedy with same title and year
// ----------------------------------------------------------------------------
bool Comedy::operator==(const Movie& rhs) const {
    const Comedy* r = dynamic_cast<const Comedy*>(&rhs);
    if (!r) return false;
    return title == r->title && year == r->year;
}

// --------------------------------- display() ---------------------------------
// Outputs the full inventory line for this comedy.
// preconditions:  none
// postconditions: writes "F stock director, title, year" to out; out unchanged
// ----------------------------------------------------------------------------
void Comedy::display(std::ostream& out) const {
    out << genre << " " << stock << " " << director << ", " << title << ", " << year;
}

// ------------------------------ displayBrief() -------------------------------
// Outputs an abbreviated line used in customer history.
// preconditions:  none
// postconditions: writes "F title, year" to out; out unchanged
// ----------------------------------------------------------------------------
void Comedy::displayBrief(std::ostream& out) const {
    out << genre << " " << title << ", " << year;
}
