// File: dvd.cpp
// Purpose: Implementation file for DVD class

#include <iostream>
#include <string>
#include <list>

#include "dvd.h"


DVD::DVD(std::string name, int copy){
    name_ = name;
    copy_ = copy;
    checked_out_ = 0;
    available_ = copy;
}

void DVD::shipped(){
    checked_out_ ++;
    available_ --;
}

void DVD::add_copy(int copies){
    copy_ += copies;
    available_ += copies;
}

void DVD::add_available(){
    checked_out_ --;
    available_ ++;
}

bool DVD::available(){
    if(available_ > 0) return true;
    else return false;
}
