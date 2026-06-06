// ---------------------------------- movie.h ----------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the abstract Movie base class. All genre subclasses
//          (Comedy, Drama, Classic) inherit from this and override the pure
//          virtual methods for sorting, parsing, and display.
// ----------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <string>

class Movie {
public:
    Movie();
    virtual ~Movie() = default;

    virtual bool operator<(const Movie& rhs) const = 0;    // genre-specific ordering
    virtual bool operator==(const Movie& rhs) const = 0;   // genre-specific equality
    virtual void setData(std::istream& in) = 0;            // parse inventory line
    virtual void setSearchKey(std::istream& in) = 0;       // parse command search fields
    virtual void display(std::ostream& out) const = 0;     // full inventory format
    virtual void displayBrief(std::ostream& out) const = 0; // short format for history

    bool borrow();      // decrement stock; returns false if out of stock
    bool returnCopy();  // increment stock; always returns true

    char getGenre() const { return genre; }
    int getStock() const { return stock; }
    std::string getTitle() const { return title; }
    std::string getDirector() const { return director; }
    int getYear() const { return year; }
    void addStock(int n) { stock += n; }  // used by BSTree to merge duplicate entries

protected:
    char genre;           // 'F' Comedy, 'D' Drama, 'C' Classic
    int stock;            // number of copies currently available
    std::string director;
    std::string title;
    int year;             // release year
};
