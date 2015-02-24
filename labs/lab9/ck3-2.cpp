#include <iostream>
#include <map>
#include <string>
#include <vector>

// O(log n)
void add(std::map<long, std::string> &phonebook, const long &number, const std::string &name){
    if(phonebook.find(number) == phonebook.end()){
        phonebook.insert(std::make_pair(number, name));
    }
}

// O(log n)
void identify(std::map<long, std::string> &phonebook, const long &number){
    if(phonebook.find(number) == phonebook.end()){
        std::cout << "unknown caller!" << std::endl;
    }
    else{
        std::cout << (phonebook.find(number)) -> second << " is calling" << std::endl;
    }
}

int main() {
    // create the phonebook; initially all numbers are unassigned
    // O(1)
    std::map<long, std::string> phonebook;

    // add several names to the phonebook
    add(phonebook, 1111, "fred");
    add(phonebook, 2222, "sally");
    add(phonebook, 3333, "george");
    add(phonebook, 5555, "peter");
    add(phonebook, 5555555, "Jpeter");

    // test the phonebook
    identify(phonebook, 2222);
    identify(phonebook, 5555555);
    identify(phonebook, 4444);
}
