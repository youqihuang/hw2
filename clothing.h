#include <set>
#include <string>
#include "product.h"

class Clothing : public Product{
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand); 
    ~Clothing();
    std::string getSize() const;
    std::string getBrand() const;
    std::set<std::string> keywords() const;
    void dump(std::ostream& os) const;
    std::string displayString() const; 
private:
    std::string size_; 
    std::string brand_;
};