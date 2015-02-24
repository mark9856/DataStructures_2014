#include "customer.h"
#include <fstream>

customer::customer() {
    //num_movies = 0;
    MAX_MOVIES = 3;
}

customer::customer(std::string& first_name, std::string& last_name, int movies, std::list<std::string>& preference) {
    this->first_name = first_name;
    this->last_name = last_name;
    //num_movies = movies;
    preference_list = preference;
    MAX_MOVIES = 3;
}

customer::customer(std::string& name, int movies, std::list<std::string>& preference) {
    customer_name = name;
    //num_movies = movies;
    preference_list = preference;
    MAX_MOVIES = 3;
}

void customer::add_preference(int movies, std::list<std::string>& added_preference) {
    for (std::list<std::string>::iterator itr = added_preference.begin(); itr != added_preference.end(); itr++) {
        preference_list.push_back(*itr);
    }
    //num_movies += movies;
}

void customer::add_one_preference(std::string& one_movie) {
    preference_list.push_back(one_movie);
    //num_movies++;
}

bool customer::has_max_num_movies() {
    if (has_movies_list.size() == MAX_MOVIES) return true;
    else return false;
}

bool customer::has_movie(std::string one_movie) {
    for (std::list<std::string>::iterator itr = has_movies_list.begin(); itr != has_movies_list.end(); itr++) {
        if ((*itr) == one_movie) return true;
    }
    return false;
}

bool customer::preference_list_empty() {
    if (preference_list.size() == 0) return true;
    else return false;
}

void customer::receives(const std::string& one_movie) {
    has_movies_list.push_back(one_movie);
    preference_list.erase(find_movie(one_movie));
    //ostr << "  " <<customer_name <<" receives "<< one_movie <<"\n";
}

const std::string customer::return_oldest() {
    std::string oldest_movie = has_movies_list.front();
    has_movies_list.pop_front();
    //ostr << customer_name <<" returns "<< oldest_movie <<"\n";
    std::cout<<oldest_movie<<"\n";
    return oldest_movie;
}

const std::string customer::return_newest() {
    std::string newest_movie = has_movies_list.back();
    //std::string newest_movie="aa";
    has_movies_list.pop_back();
    //ostr << customer_name <<" returns "<< newest_movie <<"\n";
    return newest_movie;
}

const std::list<std::string>::iterator customer::find_movie(const std::string& movie_name) {
    for (std::list<std::string>::iterator itr = preference_list.begin(); itr != preference_list.end(); itr++) {
        if (movie_name == (*itr)) return itr;
    }
    return preference_list.end();
}

const std::list<std::string> customer::get_preferences() const {
    return preference_list;
}

const std::string customer::get_first_name () const { return first_name;}
                   
const std::string customer::get_last_name () const {return last_name;}
                   
const std::string customer::get_name () const { return customer_name;}

const int customer::get_has_movies() const { return has_movies_list.size();}

const std::list<std::string> customer::get_movies() const { return has_movies_list;}
