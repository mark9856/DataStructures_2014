#ifndef Customer_h_
#define Customer_h_

#include <iostream>
#include <list>

#include "dvd.h"

class Customer{
    public:
        // CONSTRUCTUTOR
        Customer(std::string name);

        void add_preference(std::string movie);
        void receives(std::string dvd);
        std::string get_name() const{return name_;}
        void set_name(std::string name);
        std::list<std::string> get_preferences();
        std::list<std::string> get_receives();
        bool has_max_num_movies();
        bool preference_list_empty();
        void return_oldest(std::ostream &ostr);
        void return_newest(std::ostream &ostr);
        std::string receives_begin() {return *receives_.begin();}
        std::string receives_end() {return *(--receives_.end());}
        int nReceives() const{return receives_.size();}
        int nPreferences() const{return preferences_.size();}
        void print_receives(std::ostream &ostr);
        void print_preferences(std::ostream &ostr);

    private:
        std::string name_;
        std::list<std::string> preferences_;
        std::list<std::string> receives_;
};
#endif
