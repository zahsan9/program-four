// ---------------------------------- drama.h ----------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the Drama genre subclass. Dramas are sorted by director
//          ascending, then title ascending. Genre code: 'D'.
// ----------------------------------------------------------------------------

#pragma once
#include "movie.h"

class Drama : public Movie {
public:
    Drama();
    bool operator<(const Movie& rhs) const override;    // sort: director, then title
    bool operator==(const Movie& rhs) const override;   // equal if director and title match
    void setData(std::istream& in) override;             // parse inventory line
    void setSearchKey(std::istream& in) override;        // parse "director, title," from command
    void display(std::ostream& out) const override;      // full inventory format
    void displayBrief(std::ostream& out) const override; // short format for history
};
