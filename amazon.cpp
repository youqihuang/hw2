#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "mydatastore.h"
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore* ds = new MyDataStore();



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], *ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds -> search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds -> search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds -> dump(ofile);
                    ofile.close();
                }
                done = true;
            } else if (cmd == "ADD") {
                string username; 
                size_t hit_result_index; 
                ss >> username; 
                std::map<std::string, User*> u = ds -> getUsers();
                if (ss.fail() || u.find(username) ==u.end()) {
                    cout << "Invalid request" << endl;
                } else {
                    ss >> hit_result_index;
                    if (ss.fail() || hit_result_index < 0 || hit_result_index > ds -> getLastSearch().size()) {
                        cout << "Invalid request" << endl;
                    } else {
                        ds -> addToCart(username, hit_result_index);
                    }
                }
            } else if (cmd == "VIEWCART") {
                string username; 
                ss >> username; 
                std::map<std::string, User*> u = ds -> getUsers();
                if (ss.fail() || u.find(username) == u.end()) {
                    cout << "Invalid username" << endl;
                } else {
                    ds -> viewCart(username);
                }
            } else if (cmd == "BUYCART") {
                string username; 
                ss >> username; 
                std::map<std::string, User*> u = ds -> getUsers();
                if (ss.fail() ||u.find(username) == u.end()) {
                    cout << "Invalid username" << endl;
                } else {
                    ds -> buyCart(username);
                }
            }
	    /* Add support for other commands here */

        //ADD: invalid request if no/invalid username or hit_result_index
        //VIEW: invalid request if username provided is invalid
        //BUY: invalid request if username provided is invalid

            else {
                cout << "Unknown command" << endl;
            }
        }
    }
    delete ds;
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
