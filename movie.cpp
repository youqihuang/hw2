#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category, name,
price, qty) {
    genre_ = genre; 
    rating_ = rating;
}

Movie::~Movie() {
    
}

std::string Movie::getGenre() const {
    return genre_;
}

std::string Movie::getRating() const {
    return rating_;
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
} 

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keywords;
    std::string g = convToLower(genre_);
    std::set<std::string> genreWords = parseStringToWords(g);
    std::set<std::string>::iterator it_g; 
    for (it_g = genreWords.begin(); it_g != genreWords.end(); ++it_g) {
        keywords.insert(*it_g);
    }
    keywords.insert(convToLower(genre_));
    std::string n = convToLower(name_);
    std::set<std::string> nameWords = parseStringToWords(n);
    std::set<std::string>::iterator it_n; 
    for (it_n = nameWords.begin(); it_n != nameWords.end(); ++it_n) {
        keywords.insert(*it_n);
    }
    return keywords;
}

std::string Movie::displayString() const {
    std::string s = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_)  + " left. \n";
    return s;
}

/* 
<name>
Genre: <genre> Rating: <rating>
<price> <quantity> left.

    "Item 1\n"
    "Hidden Figures DVD         \n"
    "Genre: Drama Rating: PG\n"
    "17.99  1 left.\n"

    "Item 1\n"
    "Data Abstraction & Problem Solving with C++         \n"
    "Author: Carrano and Henry ISBN: 978-013292372-9\n"
    "79.99 19 left.\n" 
    
    "Men's Fitted Shirt         \n"
    "Size: Medium Brand: J. Crew\n"
    "39.99 25 left.\n"
*/