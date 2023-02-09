#include <set>
#include <string>
#include "product.h"

class Book : public Product{
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
    ~Book();
    std::string getISBN() const;
    std::string getAuthor() const;
    std::set<std::string> keywords() const;
    void dump(std::ostream& os) const;
    std::string displayString() const; 
private:
    std::string isbn_; 
    std::string author_;
};