// --------------------------------- classic.h ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the Classic genre subclass. Classics are sorted by release
//          year, then month, then major actor name. Each unique actor-date
//          combination is a separate BSTree node with its own stock.
//          Genre code: 'C'.
// ----------------------------------------------------------------------------

#pragma once
#include "movie.h"

class Classic : public Movie {
public:
    Classic();
    bool operator<(const Movie& rhs) const override;    // sort: year, month, majorActor
    bool operator==(const Movie& rhs) const override;   // equal if year, month, actor match
    void setData(std::istream& in) override;             // parse inventory line
    void setSearchKey(std::istream& in) override;        // parse "month year First Last" from command
    void display(std::ostream& out) const override;      // full inventory format
    void displayBrief(std::ostream& out) const override; // short format for history

    std::string getMajorActor() const { return majorActor; }
    int getMonth() const { return month; }

private:
    std::string majorActor; // full name "FirstName LastName"
    int month;              // release month (1-12)
};
