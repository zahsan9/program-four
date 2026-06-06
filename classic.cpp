// -------------------------------- classic.cpp --------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Classic genre subclass. Parses movie data including
//          the major actor and release month, defines sort and equality by
//          year/month/actor, and formats output.
// ----------------------------------------------------------------------------

#include "classic.h"

static std::string trimStr(const std::string& s) {  // strip leading/trailing whitespace
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

// --------------------------------- Classic() ---------------------------------
// Default constructor.
// preconditions:  none
// postconditions: genre set to 'C', month set to 0; inherited fields at defaults
// ----------------------------------------------------------------------------
Classic::Classic() : month(0) { genre = 'C'; }

// --------------------------------- setData() ---------------------------------
// Parses one inventory line after the genre character.
// preconditions:  in holds ", stock, director, title, FirstName LastName month year"
// postconditions: stock, director, title, majorActor, month, and year populated
// ----------------------------------------------------------------------------
void Classic::setData(std::istream& in) {
    char ch;
    in >> ch;       // ','
    in >> stock;
    in >> ch;       // ','
    in.get(ch);     // ' '
    getline(in, director, ',');
    director = trimStr(director);
    getline(in, title, ',');
    title = trimStr(title);
    std::string first, last;
    in >> first >> last >> month >> year;
    majorActor = first + " " + last;
}

// ----------------------------- setSearchKey() --------------------------------
// Parses the search key fields from a borrow or return command.
// preconditions:  in holds " month year FirstName LastName"
// postconditions: month, year, and majorActor populated for BSTree lookup
// ----------------------------------------------------------------------------
void Classic::setSearchKey(std::istream& in) {
    std::string first, last;
    in >> month >> year >> first >> last;
    majorActor = first + " " + last;
}

// -------------------------------- operator<() --------------------------------
// Less-than comparison used for BSTree insertion and traversal ordering.
// preconditions:  rhs is a Classic (dynamic_cast assumed valid by caller)
// postconditions: returns true if this classic sorts before rhs by year,
//                 then month, then majorActor
// ----------------------------------------------------------------------------
bool Classic::operator<(const Movie& rhs) const {
    const Classic& r = dynamic_cast<const Classic&>(rhs);
    if (year != r.year) return year < r.year;
    if (month != r.month) return month < r.month;
    return majorActor < r.majorActor;
}

// ------------------------------- operator==() --------------------------------
// Equality check used by BSTree find. Two Classics with the same title but
// different actors are never equal, so they are stored as separate nodes.
// preconditions:  none
// postconditions: returns true if rhs is a Classic with same year, month, actor
// ----------------------------------------------------------------------------
bool Classic::operator==(const Movie& rhs) const {
    const Classic* r = dynamic_cast<const Classic*>(&rhs);
    if (!r) return false;
    return year == r->year && month == r->month && majorActor == r->majorActor;
}

// --------------------------------- display() ---------------------------------
// Outputs the full inventory line for this classic.
// preconditions:  none
// postconditions: writes "C stock month year majorActor, title, director" to out
// ----------------------------------------------------------------------------
void Classic::display(std::ostream& out) const {
    out << genre << " " << stock << " " << month << " " << year
        << " " << majorActor << ", " << title << ", " << director;
}

// ------------------------------ displayBrief() -------------------------------
// Outputs an abbreviated line used in customer history.
// preconditions:  none
// postconditions: writes "C month year majorActor, title" to out
// ----------------------------------------------------------------------------
void Classic::displayBrief(std::ostream& out) const {
    out << genre << " " << month << " " << year << " " << majorActor
        << ", " << title;
}
