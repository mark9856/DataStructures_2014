#include "dvd.h"

DVD::DVD() {
    copies = 0;
    checkouts = 0;
    availables = 0;
}

DVD::DVD(std::string &dvd_name, int dvd_copies) {
    name = dvd_name;
    copies = dvd_copies;
    checkouts = 0;
    availables = dvd_copies;
}

void DVD::set_name(std::string dvd_name) { name=dvd_name;}

void DVD::set_copies(int dvd_copies) { copies = dvd_copies;}

void DVD::add_copies(int dvd_copies) {
    copies += dvd_copies;
    availables += dvd_copies;
}

void DVD::shipped() {
    //std::cout << name <<"\n";
    checkouts++;
    availables--;
}

void DVD::return_one() {
    checkouts--;
    availables++;
}

const std::string DVD::get_name () const { return name;}

const int DVD::get_copies() const { return copies;}

const int DVD::get_checkouts() const {
    return checkouts;
}

const int DVD::get_availables() const {
    return availables;
}

const bool DVD::available() const {
    if(availables > 0) return true;
    else return false;
}