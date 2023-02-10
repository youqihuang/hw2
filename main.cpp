#include "util.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::set<std::string> s = parseStringToWords("Data Abstraction & Problem Solving with C++");  
    std::set<std::string>::iterator it;
    for (it = s.begin(); it != s.end(); ++it) {
        cout << (*it) << endl;
    }
}