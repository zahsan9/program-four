// --------------------------------- drama.cpp ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Drama genre subclass. Parses movie data, defines
//          sort and equality by director then title, and formats output.
// ----------------------------------------------------------------------------

#include "drama.h"

static std::string trimStr(const std::string& s) {  // strip leading/trailing whitespace
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

// ---------------------------------- Drama() ----------------------------------
// Default constructor.
// preconditions:  none
// postconditions: genre set to 'D'; all inherited fields at Movie defaults
// ----------------------------------------------------------------------------
Drama::Drama() { genre = 'D'; }

// --------------------------------- setData() ---------------------------------
// Parses one inventory line after the genre character.
// preconditions:  in holds ", stock, director, title, year"
// postconditions: stock, director, title, and year populated from stream
// ----------------------------------------------------------------------------
void Drama::setData(std::istream& in) {
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
// preconditions:  in holds " director, title," (trailing comma present)
// postconditions: director and title populated for subsequent BSTree lookup
// ----------------------------------------------------------------------------
void Drama::setSearchKey(std::istream& in) {
    in.get(); // skip leading space
    getline(in, director, ',');
    director = trimStr(director);
    getline(in, title, ',');
    title = trimStr(title);
}

// -------------------------------- operator<() --------------------------------
// Less-than comparison used for BSTree insertion and traversal ordering.
// preconditions:  rhs is a Drama (dynamic_cast assumed valid by caller)
// postconditions: returns true if this drama sorts before rhs by director, then title
// ----------------------------------------------------------------------------
bool Drama::operator<(const Movie& rhs) const {
    const Drama& r = dynamic_cast<const Drama&>(rhs);
    if (director != r.director) return director < r.director;
    return title < r.title;
}

// ------------------------------- operator==() --------------------------------
// Equality check used by BSTree for stock merging and find.
// preconditions:  none
// postconditions: returns true if rhs is a Drama with same director and title
// ----------------------------------------------------------------------------
bool Drama::operator==(const Movie& rhs) const {
    const Drama* r = dynamic_cast<const Drama*>(&rhs);
    if (!r) return false;
    return director == r->director && title == r->title;
}

// --------------------------------- display() ---------------------------------
// Outputs the full inventory line for this drama.
// preconditions:  none
// postconditions: writes "D stock director, title, year" to out; out unchanged
// ----------------------------------------------------------------------------
void Drama::display(std::ostream& out) const {
    out << genre << " " << stock << " " << director << ", " << title << ", " << year;
}

// ------------------------------ displayBrief() -------------------------------
// Outputs an abbreviated line used in customer history.
// preconditions:  none
// postconditions: writes "D director, title" to out; out unchanged
// ----------------------------------------------------------------------------
void Drama::displayBrief(std::ostream& out) const {
    out << genre << " " << director << ", " << title;
}
