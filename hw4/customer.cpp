// File: customer.cpp
// Purpose: Implementation file for customer class

#include <iostream>
#include <string>
#include <list>

#include "customer.h"

Customer::Customer(std::string name){
    name_ = name;
    // preferences_ = NULL;
    // receives_ = NULL;
}

void Customer::add_preference(std::string movie){
    preferences_.push_back(movie);
}

// O(p)
void Customer::receives(std::string dvd){
    receives_.push_back(dvd);
    for(std::list<std::string>::iterator itr = preferences_.begin(); itr != preferences_.end(); ++ itr){
        if(*itr == dvd){
            itr = preferences_.erase(itr);
        }
    }
}

std::list<std::string> Customer::get_preferences(){
    return preferences_;
}
std::list<std::string> Customer::get_receives(){
    return receives_;
}

bool Customer::has_max_num_movies(){
    if(receives_.size() == 3) return true;
    else return false;
}

bool Customer::preference_list_empty(){
    if(preferences_.size() == 0) return true;
    else return false;
}

void Customer::return_oldest(std::ostream &ostr){
    // std::cout << name_ << " returns " << *receives_.begin() << std::endl;
    ostr << name_ << " returns " << *receives_.begin() << std::endl;
    receives_.pop_front();
}

void Customer::return_newest(std::ostream &ostr){
    // std::cout << name_ << " returns " << *(--receives_.end()) << std::endl;
    ostr << name_ << " returns " << *(--receives_.end()) << std::endl;
    receives_.pop_back();
}
// O(3)
void Customer::print_receives(std::ostream &ostr){
    for(std::list<std::string>::iterator itr = receives_.begin(); itr != receives_.end(); ++ itr){
        // std::cout << "    " << *itr << "" << std::endl;
        ostr<< "    " << *itr << "" << std::endl;
    }
}

void Customer::print_preferences(std::ostream &ostr){
    for(std::list<std::string>::iterator itr = preferences_.begin(); itr != preferences_.end(); ++ itr){
        // std::cout << "    " << *itr << "" << std::endl;
        ostr<< "    " << *itr << "" << std::endl;
    }
}
