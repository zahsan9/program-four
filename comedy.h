// --------------------------------- comedy.h ----------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the Comedy genre subclass. Comedies are sorted by title
//          ascending, then release year ascending. Genre code: 'F'.
// ----------------------------------------------------------------------------

#pragma once
#include "movie.h"

class Comedy : public Movie {
public:
    Comedy();
    bool operator<(const Movie& rhs) const override;    // sort: title, then year
    bool operator==(const Movie& rhs) const override;   // equal if title and year match
    void setData(std::istream& in) override;             // parse inventory line
    void setSearchKey(std::istream& in) override;        // parse "title, year" from command
    void display(std::ostream& out) const override;      // full inventory format
    void displayBrief(std::ostream& out) const override; // short format for history
};
