#pragma once
#include <iostream>
#include <string>

class Movie {
public:
    Movie();
    virtual ~Movie() = default;

    virtual bool operator<(const Movie& rhs) const = 0;
    virtual bool operator==(const Movie& rhs) const = 0;
    virtual void setData(std::istream& in) = 0;
    virtual void setSearchKey(std::istream& in) = 0;
    virtual void display(std::ostream& out) const = 0;
    virtual void displayBrief(std::ostream& out) const = 0;

    bool borrow();
    bool returnCopy();

    char getGenre() const { return genre; }
    int getStock() const { return stock; }
    std::string getTitle() const { return title; }
    std::string getDirector() const { return director; }
    int getYear() const { return year; }
    void addStock(int n) { stock += n; }

protected:
    char genre;
    int stock;
    std::string director;
    std::string title;
    int year;
};
