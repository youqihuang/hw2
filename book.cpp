#include "book.h" 
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std; 

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : Product(category, name,
price, qty) {
    isbn_ = isbn; 
    author_ = author;
}

Book::~Book() {
    
}

std::string Book::getISBN() const{
    return isbn_;
}

std::string Book::getAuthor() const{
    return author_;
}

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keywords; 
    keywords.insert(isbn_);
    std::string a = convToLower(author_);
    std::set<std::string> authorWords = parseStringToWords(a);
    std::set<std::string>::iterator it_a; 
    for (it_a = authorWords.begin(); it_a != authorWords.end(); ++it_a) {
        keywords.insert(*it_a);
    }
    std::string n = convToLower(name_);
    std::set<std::string> nameWords = parseStringToWords(n);
    std::set<std::string>::iterator it_n; 
    for (it_n = nameWords.begin(); it_n != nameWords.end(); ++it_n) {
        keywords.insert(*it_n);
    }
    return keywords;
}

std::string Book::displayString() const {
    std::string s = name_ + "\nAuthor: " +  author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.\n"; 
    return s;
}

/* 
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