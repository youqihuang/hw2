#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std; 
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product(category, name,
price, qty) {
    size_ = size; 
    brand_ = brand;
}

Clothing::~Clothing() {
    
}

std::string Clothing::getSize() const {
    return size_;
}

std::string Clothing::getBrand() const{
    return brand_;
}

void Clothing::dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
} 

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keywords;
    std::string b = convToLower(brand_);
    std::set<std::string> brandWords = parseStringToWords(b);
    std::set<std::string>::iterator it_b; 
    for (it_b = brandWords.begin(); it_b != brandWords.end(); ++it_b) {
        keywords.insert(*it_b);
    }
    std::string n = convToLower(name_);
    std::set<std::string> nameWords = parseStringToWords(n);
    std::set<std::string>::iterator it_n; 
    for (it_n = nameWords.begin(); it_n != nameWords.end(); ++it_n) {
        keywords.insert(*it_n);
    }
    return keywords;
}

std::string Clothing::displayString() const {
    std::string s = name_ + "\nSize: " +  size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) +" left. \n"; 
    return s;
}

/* 
<name>
Size: <size> Brand: <brand>
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