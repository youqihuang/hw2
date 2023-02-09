#include <set>
#include <string>
#include "product.h"

class Movie : public Product{
public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
    ~Movie();
    std::string getGenre() const;
    std::string getRating() const;
    std::set<std::string> keywords() const;
    void dump(std::ostream& os) const;
    std::string displayString() const; 
private:
    std::string genre_; 
    std::string rating_;
};