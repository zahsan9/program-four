#pragma once
#include "movie.h"

class Drama : public Movie {
public:
    Drama();
    bool operator<(const Movie& rhs) const override;
    bool operator==(const Movie& rhs) const override;
    void setData(std::istream& in) override;
    void setSearchKey(std::istream& in) override;
    void display(std::ostream& out) const override;
    void displayBrief(std::ostream& out) const override;
};
