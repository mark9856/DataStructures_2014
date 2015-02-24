// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <stdlib.h>

#include "dvd.h"
#include "customer.h"

// several type defs to keep things neat
// (hint, these are STL lists)
typedef std::list<DVD> inventory_type;
typedef std::list<Customer> customers_type;
typedef std::list<std::string> preference_type;

// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
    std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
    std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
    std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
    exit(1);
}


int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 5) {
        usage(argv[0]);
    }

    // open input and output file streams
    std::ifstream istr(argv[1]);
    if (!istr) {
        std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
        usage(argv[0]); 
    }
    std::ofstream ostr(argv[2]);
    if (!ostr) {
        std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
        usage(argv[0]); 
    }

    // optional parameters for extra credit
    bool use_improved_algorithm = false;
    bool print_analysis = false;
    for (int i = 3; i < argc; i++) {
        if (std::string(argv[i]) == "--improved") {
            use_improved_algorithm = true;
        } else if (std::string(argv[i]) == "--analysis") {
            print_analysis = true;
        } else {
            usage(argv[0]);
        }
    }


    // stores information about the DVDs
    inventory_type inventory;
    // stores information about the customers
    customers_type customers;


    // read in and handle each of the 8 keyword tokens
    std::string token;
    while (istr >> token) {
        if (token == "dvd") {
            std::string dvd_name = read_dvd_name(istr);
            int copies;
            istr >> copies;
            // set up a signal found
            bool found = false;
            // find out whether there is already a record exist in this inventory
            // O(d)
            for(inventory_type::iterator itr = inventory.begin(); itr != inventory.end(); ++ itr){
                // if already exist
                if((*itr).get_name() == dvd_name){
                    // add copies to this one
                    (*itr).add_copy(copies);
                    // set found to be true
                    found = true;
                }
            }
            // if can't find this movie, add this movie into the inventory
            if(!found){
                // create a new one
                DVD movie(dvd_name, copies);
                // push_back this new movie to inventory
                inventory.push_back(movie);
            }
            // print out the copies
            ostr <<  copies;
            // when copies is one print copy
            if(copies == 1){
                // std::cout << " copy of ";
                ostr << " copy of ";
            }
            else {
                // std::cout << " copies of ";
                ostr << " copies of ";

            }

            // std::cout << (*(--inventory.end())).get_name() << " added" << std::endl;
            ostr << dvd_name << " added" << std::endl;
            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "customer") {
            std::string customer_name = read_customer_name(istr);
            int num_movies;
            istr >> num_movies;
            // whether the customer is already in the list
            bool existCustomer = false;
            // warning of existCustomer
            // O(c)
            for(customers_type::iterator itr = customers.begin(); itr != customers.end(); ++ itr){
                if((*itr).get_name() == customer_name){
                    ostr << "WARNING: Already have a customer named " << customer_name << std::endl;
                    existCustomer = true;
                }
            }
            if(existCustomer == false){
                // create a new Customer
                Customer consumer(customer_name);

                preference_type preferences;
                // O(p)
                for (int i = 0; i < num_movies; i++) {
                    std::string dvd_name = read_dvd_name(istr);
                    // whether the movie is in the inventory
                    bool found = false;
                    // O(d)
                    for(inventory_type::iterator itr = inventory.begin(); itr != inventory.end(); ++ itr){
                        if((*itr).get_name() == dvd_name){
                            found = true;
                        }
                    }
                    // Warning of not in the inventory
                    if(!found){
                        ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
                        continue;
                    }
                    // O(p)
                    for(preference_type::iterator itr = preferences.begin(); itr != preferences.end(); ++itr){
                        if(*itr == dvd_name){
                            // warning of Duplicate movie in the preference list
                            ostr << "WARNING: Duplicate movie " << dvd_name 
                                << " on preference list!" << std::endl;
                            continue;
                        }
                    }
                    // push_back new dvd
                    preferences.push_back(dvd_name);
                    // add movie to customer's preference list
                    consumer.add_preference(dvd_name);
                }
                // push_back new customer
                customers.push_back(consumer);

                ostr << "new customer: " << (*(--customers.end())).get_name() << std::endl;
            }
            else{
                for (int i = 0; i < num_movies; i++) {
                    std::string dvd_name = read_dvd_name(istr);
                }
            }

            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "ship") {

           // ship movie base on algorithm 
            shipping_algorithm(inventory,customers,ostr);
            

        } else if (token == "return_oldest") {
            std::string customer_name = read_customer_name(istr);
            // whether the customer is in the customers list
            bool found = false;
            // O(c)
            for(customers_type::iterator itr = customers.begin(); itr != customers.end(); ++ itr){
                // found the customer
                if((*itr).get_name() == customer_name){
                    found = true;
                    // if the customer has more than one receives
                    if((*itr).nReceives() != 0){
                        // O(d)
                        for(inventory_type::iterator iitr = inventory.begin(); iitr != inventory.end(); ++ iitr){
                            // add available copies to this movie
                            if((*iitr).get_name() == (*itr).receives_begin() ){
                                (*iitr).add_available();
                            }
                        }
                        // return the oldest movie
                        (*itr).return_oldest(ostr);
                    }
                    else{
                        // Warning of no movie in list
                        ostr << "WARNING: " << customer_name << " has no DVDs to return!" << std::endl;
                    }
                }
            }
            if(!found){
                // WARNING of no such customer exist
                ostr << "WARNING: No customer named " << customer_name << std::endl;
            }
            

            
            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "return_newest") {
            std::string customer_name = read_customer_name(istr);
            
            // whether the customer exist
            bool found = false;
            // O(c)
            for(customers_type::iterator itr = customers.begin(); itr != customers.end(); ++ itr){
                //found the customer in list
                if((*itr).get_name() == customer_name){
                    found = true;
                    // if customer has more than one movie received
                    if((*itr).nReceives() != 0){
                        // O(d)
                        for(inventory_type::iterator iitr = inventory.begin(); iitr != inventory.end(); ++ iitr){
                            if((*iitr).get_name() == (*itr).receives_end() ){
                                // add available to this movie
                                (*iitr).add_available();
                            }
                        }
                        // return the newest movie the customer received
                        (*itr).return_newest(ostr);
                    }
                    else{
                        // warning of no dvd to return
                        ostr << "WARNING: " << customer_name << " has no DVDs to return!" << std::endl;
                    }
                }
            }
            if(!found){
                // WARNING of no such customer
                ostr << "WARNING: No customer named " << customer_name << std::endl;
            }
            

            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "print_customer") {
            std::string customer_name = read_customer_name(istr);

            // whether the customer is exist
            bool found = false;
            // O(c)
            for(customers_type::iterator itr = customers.begin(); itr != customers.end(); ++ itr){
                // found this customer
                if((*itr).get_name() == customer_name){
                    found = true;
                    // the customer has more than one copy
                    if((*itr).nReceives() > 0){
                        // print out the receives the customer have
                        ostr << (*itr).get_name() << " has " 
                            << (*itr).nReceives() << " movies:" << std::endl;
                        // print what the customer receives
                        (*itr).print_receives(ostr);
                        // if there is more than one preference
                        if(!(*itr).preference_list_empty()){
                            ostr << "  preference list:" << std::endl;
                            (*itr).print_preferences(ostr);
                        }
                    }
                    else{
                        ostr << (*itr).get_name() << " has no movies" << std::endl;
                        // if there is more than one preference
                        if(!(*itr).preference_list_empty()){
                            ostr << "  preference list:" << std::endl;
                            (*itr).print_preferences(ostr);
                        }
                    }
                }
            }
            if(!found){
                // warning of no such customer
                ostr << "WARNING: No customer named " << customer_name << std::endl;
            }
            


            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "print_dvd") {
            std::string dvd_name = read_dvd_name(istr);
            // whether the customer exist
            bool found = false;
            // O(d)
            for(inventory_type::iterator itr = inventory.begin(); itr != inventory.end(); ++ itr){
                // found this customer
                if((*itr).get_name() == dvd_name){
                    ostr << (*itr).get_name() << ":" << std::endl;
                    ostr << "  ";
                    // when this only one copy check out
                    if((*itr).get_checked_out() == 1){
                        ostr << (*itr).get_checked_out() << " copy checked out";
                        // if there is available one exist
                        if((*itr).get_available() > 0){
                            ostr << " and ";
                        }
                    }
                    // if there is more copy check out print "copies"
                    else if ((*itr).get_checked_out() > 1){
                        ostr << (*itr).get_checked_out() << " copies checked out";
                        // if there is available one exist
                        if((*itr).get_available() > 0){
                            ostr << " and ";
                        }
                    }
                    else{
                    }

                    // if there is only one available
                    if((*itr).get_available() == 1){
                        ostr << (*itr).get_available() << " copy available" << std::endl;
                    }
                    // if there are more than one available
                    else if((*itr).get_available() > 1){
                        ostr << (*itr).get_available() << " copies available" << std::endl;
                    }
                    else{
                        ostr << std::endl;
                    }

                    found = true;
                }
            }
            // if can't find this movie in the inventory print WARNING
            if(found == false){
                ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
            }
            

                /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else if (token == "add_preference") {
            std::string customer_name = read_customer_name(istr);
            std::string dvd_name = read_dvd_name(istr);
            // whether the customer is exist
            bool found = false;

            // whether the movie exist in the inventory
            bool inventory_found = false;
            // O(d)
            for(inventory_type::iterator itr = inventory.begin(); itr != inventory.end(); ++ itr){
                if((*itr).get_name() == dvd_name){
                    inventory_found = true;
                }
            }
            // if can't find this movie in the inventory, print warning
            if(!inventory_found){
                ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
                continue;
            }

            // O(c)
            for(customers_type::iterator itr = customers.begin(); itr != customers.end(); ++ itr){
                if((*itr).get_name() == customer_name){
                    // recognize whether there is already one copy in the receives
                    const preference_type &receives = itr->get_receives();
                    bool found1 = false;
                    // O(1)
                    for(preference_type::const_iterator itr = receives.begin(); 
                            itr != receives.end(); ++ itr){
                        if(*itr == dvd_name){
                            found1 = true;
                            ostr << "WARNING: " << customer_name << " currently has " 
                                << dvd_name << "!" << std::endl;
                        }
                    }
                    // recognize whether this dvd is already in the preferences_itr

                    const preference_type &preferences = itr->get_preferences();
                    bool found2 = false;
                    // O(p)
                    for(preference_type::const_iterator itr = preferences.begin(); 
                            itr != preferences.end(); ++ itr){
                        if(*itr == dvd_name){
                            ostr << "WARNING: " << customer_name << " already has " 
                                << dvd_name << " on his/her preference list!" << std::endl;
                            found2 = true;
                        }
                    }
                    //if(!found2 && !found1){
                    if(found2 == false && found1 == false){
                        (*itr).add_preference(dvd_name);
                    }
                    found = true;
                }
            }
            if(!found){
                ostr << "WARNING: No customer named " << customer_name << std::endl;
            }

            /* YOU MUST FINISH THIS IMPLEMENTATION */

        } else {
            std::cerr << "ERROR: Unknown token " << token << std::endl;
            exit(1);
        }
    }
    
    if(use_improved_algorithm == true){
        
    }
    if(print_analysis == true){

    }
}


// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
    std::string first, last;
    istr >> first >> last;
    return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
    std::string token;
    istr >> token;
    assert (token[0] == '"');
    std::string answer = token;
    while (answer[answer.size()-1] != '"') {
        istr >> token;
        answer += " " + token;
    }
    return answer;
}


// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
    // O(d)
    for (inventory_type::iterator inventory_itr = inventory.begin(); 
            inventory_itr != inventory.end(); inventory_itr++) {
        if (inventory_itr->get_name() == dvd_name) {
            return inventory_itr;
        }
    }
    // if the DVD is not found, return the .end() iterator
    return inventory.end();
}


// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr) {

    /*
        ********************************************************
        UNCOMMENT THIS WHEN YOU ARE READY TO WORK ON INTEGRATION
        ********************************************************
        */

        ostr << "Ship DVDs" << std::endl;

    // Loop over the customers in priority order
    //
    // Note that we edit the customers list as we go, to add customers
    // to the back of the list if they receive a DVD.  This allows a
    // customer to receive multiple DVDs in one shipment cycle, but only
    // after all other customers have had a chance to receive DVDs.
    //
    customers_type::iterator customer_itr = customers.begin();
    while (customer_itr != customers.end()) {

        // skip this customer if they already have 3 movies or if their
        // preference list is empty (no outstanding requests)
        if (customer_itr->has_max_num_movies() || customer_itr->preference_list_empty()) {
            // move on to the next customer
            customer_itr++;
            continue;
        }

        // a helper flag variable
        bool sent_dvd = false;

        // loop over the customer's preferences
        const preference_type &preferences = customer_itr->get_preferences();
        // O(p)
        for (preference_type::const_iterator preferences_itr = preferences.begin(); 
                preferences_itr != preferences.end(); preferences_itr++) {

            // locate this DVD in the inventory
            // O(d)
            inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);
            if (inventory_itr != inventory.end() && inventory_itr->available()) { 

                // if the DVD is available, ship it to the customer!
                ostr << "  " << customer_itr->get_name() << " receives " << *preferences_itr << std::endl;
                inventory_itr->shipped();
                // O(p)
                customer_itr->receives(*preferences_itr);

                // move this customer to the back of the priority queue
                // they will get a chance to receive another DVD, but only
                // after everyone else gets a chance
                customers.push_back(*customer_itr);
                customer_itr = customers.erase(customer_itr);

                // after setting the flag to true, leave the iteration over preferences
                sent_dvd = true;        
                break;
            }
        }

        // if no DVD was sent to this customer, then we move on to the next customer 
        // (do not change this customer's priority for tomorrow's shipment)
        if (!sent_dvd) {
            customer_itr++;
        }
    }

}

// ==================================================================
