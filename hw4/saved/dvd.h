#include <iostream>
#include <list>

class DVD {
public:
    //TYPEDEFS
    //typedef DVD* iterator;
    DVD();
    DVD(std::string &dvd_name, int dvd_copies);
    void set_name(std::string dvd_name);
    void set_copies(int dvd_copies);
    void add_copies(int dvd_copies);
    void shipped();
    void return_one();
    const std::string get_name () const;
    const int get_copies() const;
    const int get_checkouts() const;
    const int get_availables() const;
    const bool available() const;
private:
    std::string name;
    int copies;
    int checkouts;
    int availables;
};