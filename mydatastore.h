#include "datastore.h"
#include <map>
#include <vector>
#include <set>
#include <deque>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string username, int hit_result_index);
    void viewCart(std::string username);
    void buyCart(std::string username);
    std::vector<Product*> getProducts();
    std::map<std::string, User*> getUsers();
    std::map<std::string, std::set<Product*>> getKeywordMap();
    std::vector<Product*> getLastSearch();
    std::map<std::string, std::deque<Product*>*> getCarts();

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*>> keywordMap_;
    std::vector<Product*> lastSearch_;
    std::map<std::string, std::deque<Product*>*> carts_;
};