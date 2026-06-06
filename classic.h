#pragma once
#include "movie.h"

class Classic : public Movie {
public:
    Classic();
    bool operator<(const Movie& rhs) const override;
    bool operator==(const Movie& rhs) const override;
    void setData(std::istream& in) override;
    void setSearchKey(std::istream& in) override;
    void display(std::ostream& out) const override;
    void displayBrief(std::ostream& out) const override;

    std::string getMajorActor() const { return majorActor; }
    int getMonth() const { return month; }

private:
    std::string majorActor;
    int month;
};
