#include "drama.h"

static std::string trimStr(const std::string& s) {
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

Drama::Drama() { genre = 'D'; }

// Inventory format after genre char: ", stock, director, title, year"
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

// Command format: "director, title,"  (trailing comma present)
void Drama::setSearchKey(std::istream& in) {
    in.get(); // skip space
    getline(in, director, ',');
    director = trimStr(director);
    getline(in, title, ',');
    title = trimStr(title);
}

bool Drama::operator<(const Movie& rhs) const {
    const Drama& r = dynamic_cast<const Drama&>(rhs);
    if (director != r.director) return director < r.director;
    return title < r.title;
}

bool Drama::operator==(const Movie& rhs) const {
    const Drama* r = dynamic_cast<const Drama*>(&rhs);
    if (!r) return false;
    return director == r->director && title == r->title;
}

void Drama::display(std::ostream& out) const {
    out << genre << " " << stock << " " << director << ", " << title << ", " << year;
}

void Drama::displayBrief(std::ostream& out) const {
    out << genre << " " << director << ", " << title;
}
