#include <iostream>
#include <list>
#include <fstream>

class customer {
public:
    customer();
    customer(std::string& first_name, std::string& last_name, int movies, std::list<std::string>& preference);
    customer(std::string& customer_name, int num_movies, std::list<std::string>& preference);
    void add_preference(int movies, std::list<std::string>& added_preference);
    void add_one_preference(std::string& one_movie);
    bool has_max_num_movies();
    bool preference_list_empty();
    bool has_movie(std::string one_movie);
    void receives(const std::string& one_movie);
    const std::string return_oldest();
    const std::string return_newest();
    const std::string get_first_name () const;
    const std::string get_last_name () const;
    const std::string get_name () const;
    const int get_has_movies() const;
    const std::list<std::string> get_movies() const;
    const std::list<std::string> get_preferences() const;
    const std::list<std::string>::iterator find_movie(const std::string& movie_name);

private:
    std::string first_name;
    std::string last_name;
    std::string customer_name;
    //int num_movies;
    //int has_movies;
    int MAX_MOVIES;
    std::list<std::string> preference_list;
    std::list<std::string> has_movies_list;
    
    
};
