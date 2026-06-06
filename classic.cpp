#include "classic.h"

static std::string trimStr(const std::string& s) {
    size_t a = s.find_first_not_of(" \t");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t");
    return s.substr(a, b - a + 1);
}

Classic::Classic() : month(0) { genre = 'C'; }

// Inventory format after genre char: ", stock, director, title, FirstLast month year"
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
    // remainder: " FirstName LastName month year"
    std::string first, last;
    in >> first >> last >> month >> year;
    majorActor = first + " " + last;
}

// Command format: "month year FirstName LastName"
void Classic::setSearchKey(std::istream& in) {
    std::string first, last;
    in >> month >> year >> first >> last;
    majorActor = first + " " + last;
}

bool Classic::operator<(const Movie& rhs) const {
    const Classic& r = dynamic_cast<const Classic&>(rhs);
    if (year != r.year) return year < r.year;
    if (month != r.month) return month < r.month;
    return majorActor < r.majorActor;
}

bool Classic::operator==(const Movie& rhs) const {
    const Classic* r = dynamic_cast<const Classic*>(&rhs);
    if (!r) return false;
    return year == r->year && month == r->month && majorActor == r->majorActor;
}

void Classic::display(std::ostream& out) const {
    out << genre << " " << stock << " " << month << " " << year
        << " " << majorActor << ", " << title << ", " << director;
}

void Classic::displayBrief(std::ostream& out) const {
    out << genre << " " << month << " " << year << " " << majorActor
        << ", " << title;
}
