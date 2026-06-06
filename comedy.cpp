#include "comedy.h"

static std::string trimStr(const std::string& s) {
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

Comedy::Comedy() { genre = 'F'; }

// Inventory format after genre char: ", stock, director, title, year"
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

// Command format: "title, year"
void Comedy::setSearchKey(std::istream& in) {
    in.get(); // skip space
    getline(in, title, ',');
    title = trimStr(title);
    in >> year;
}

bool Comedy::operator<(const Movie& rhs) const {
    const Comedy& r = dynamic_cast<const Comedy&>(rhs);
    if (title != r.title) return title < r.title;
    return year < r.year;
}

bool Comedy::operator==(const Movie& rhs) const {
    const Comedy* r = dynamic_cast<const Comedy*>(&rhs);
    if (!r) return false;
    return title == r->title && year == r->year;
}

void Comedy::display(std::ostream& out) const {
    out << genre << " " << stock << " " << director << ", " << title << ", " << year;
}

void Comedy::displayBrief(std::ostream& out) const {
    out << genre << " " << title << ", " << year;
}
