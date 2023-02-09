#include "mydatastore.h"
#include "product.h"
#include "util.h"
#include <fstream>

using namespace std;

MyDataStore::MyDataStore() : products_(), users_(), keywordMap_(), lastSearch_(), carts_() {
}

MyDataStore::~MyDataStore() {
    for(size_t i = 0; i < products_.size(); i++) {
        delete products_[i];
    }
    std::map<std::string, User*>::iterator it_u;
    for (it_u = users_.begin(); it_u != users_.end(); ++it_u) {
        delete (*it_u).second;
    }
    std::map<std::string, std::deque<Product*>*>::iterator it_c; 
    for (it_c = carts_.begin(); it_c != carts_.end(); ++it_c) {
        delete (*it_c).second;
    }
}

void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
    std::set<std::string> keywords = p -> keywords ();
    std::set<std::string>::iterator it_k; 
    for (it_k = keywords.begin(); it_k != keywords.end(); ++it_k) {
        if (keywordMap_.find(*it_k) != keywordMap_.end()) {
            keywordMap_[*it_k].insert(p);
        } else {
            std::set<Product*> s;
            s.insert(p);
            keywordMap_.insert(make_pair(*it_k, s));
        }
    }
}

void MyDataStore::addUser(User* u) {
    users_.insert(make_pair(u -> getName(), u));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    // std::map<std::string, std::set<Product*>>::iterator it_k;
    // for(it_k = keywordMap_.begin(); it_k != keywordMap_.end(); ++it_k) {
    //     cout << "keywordMap_ " << (*it_k).first << endl;
    // }

    std::set<Product*> hits;
    //AND
    if (type == 0) { 
        std::vector<std::string>::iterator it; 
        for (it = terms.begin(); it != terms.end(); ++it) {
            std::map<std::string, std::set<Product*>>::iterator found = keywordMap_.find(*it); 
            if (found != keywordMap_.end()){
                // cout << "item found" << endl;
                std::set<Product*> itemHits = found -> second;
                if (hits.empty()) {
                    hits = itemHits;
                } else {
                    hits = setIntersection(hits, itemHits);
                }
            }
        }
    //OR
    } else {
        std::vector<std::string>::iterator it; 
        for (it = terms.begin(); it != terms.end(); ++it) {
             std::map<std::string, std::set<Product*>>::iterator found = keywordMap_.find(*it); 
            if (found != keywordMap_.end()){
                std::set<Product*> itemHits = found -> second;
                hits = setUnion(hits, itemHits);
            }
        }
    }
    std::vector<Product*> hitsvector(hits.begin(), hits.end());
    lastSearch_ = hitsvector;
    return hitsvector;
}

void MyDataStore::dump(std::ostream& ofile) {
    std::vector<Product*>::iterator it_p; 
    std::map<std::string, User*>::iterator it_u;
    ofile << "<products>" << endl; 
    for (it_p = products_.begin(); it_p != products_.end(); ++it_p) {
        Product* p; 
        p = *(it_p);
        p -> dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (it_u = users_.begin(); it_u != users_.end(); ++it_u) {
        (*it_u).second -> dump(ofile);
    }
    ofile << "</users>";
}

void MyDataStore::addToCart(std::string username, int hit_result_index) {
    /*
        std::map<std::string, std::deque<Product*>> carts_;
        if (keywordMap_.find(*it_k) != keywordMap_.end()) {
            keywordMap_[*it_k].insert(p);
        } else {
            std::set<Product*> s;
            s.insert(p);
            keywordMap_.insert(make_pair(*it_k, s));
        }
    */

    if (carts_.find(username) != carts_.end()) {
        carts_[username] -> push_back(lastSearch_[hit_result_index-1]);
    } else {
        std::deque<Product*>* d = new std::deque<Product*>(); 
        d -> push_back(lastSearch_[hit_result_index-1]);
        carts_.insert(make_pair(username, d));
    }
}

void MyDataStore::viewCart(std::string username) {
    // if (users_.find(username) == users_.end()) {
    //     cout << "not in users" << endl;
    // }
    std::deque<Product*>* cart = carts_[username];
    // cout << cart -> size() << endl;
    for (size_t i = 0; i < cart -> size(); i++) {
        cout << "Item ";
        cout << i+1 << endl; 
        cout << cart -> at(i) -> displayString() << endl;
    }
}

void MyDataStore::buyCart(std::string username) {
    std::deque<Product*>* cart = carts_[username];
    for (size_t i = 0; i < cart -> size(); i++) {
        Product* p = cart -> at(i); 
        User* u = users_[username];
        cout << p -> getName() << endl;
        if (p -> getQty() > 0 && p -> getPrice() <= u -> getBalance()) {
            cout << "buy" << endl;
            p -> subtractQty(1);
            u -> deductAmount(p -> getPrice());
            cart -> pop_front();
            i--;
        }
    }
}

std::vector<Product*> MyDataStore::getProducts() {
    return products_;
}
std::map<std::string, User*> MyDataStore::getUsers(){
    return users_;
}

std::map<std::string, std::set<Product*>> MyDataStore::getKeywordMap() {
    return keywordMap_;
}

std::vector<Product*> MyDataStore::getLastSearch() {
    return lastSearch_;
}

std::map<std::string, std::deque<Product*>*> MyDataStore::getCarts() {
    return carts_;
}
