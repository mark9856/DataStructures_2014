#ifndef DVD_h_
#define DVD_h_

#include <iostream>

class DVD{
    public:
        // CONSTRUCTUTOR
        DVD(std::string name, int copy);

        int get_checked_out() const{return checked_out_;}
        int get_available() const{return available_;}
        int get_copies() const{return copy_;}
        std::string get_name() const {return name_;}
        void shipped();
        void add_copy(int copies);
        void add_available();
        bool available();
    private:
        std::string name_; 
        int copy_;
        int checked_out_;
        int available_;
};

#endif
