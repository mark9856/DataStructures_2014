#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include "dvd.h"
#include "customer.h"

// several type defs to keep things neat
// (hint, these are STL lists)
typedef /* FILL IN */ std::list<DVD> inventory_type;
typedef /* FILL IN */std::list<customer> customers_type;
typedef /* FILL IN */std::list<std::string> preference_type;


// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);
customers_type::iterator find_customer(customers_type& customer, const std::string& customer_name);
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
      std::cout << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
      std::cout << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
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
      std::string copy_str="copies";
      istr >> copies;
        DVD new_dvd(dvd_name,copies);
        if (copies == 1) {
            copy_str = "copy";
        }
        //if there is al
        if (find_DVD(inventory,dvd_name) != inventory.end()) {
            find_DVD(inventory,dvd_name)->add_copies(copies);
            ostr << copies <<" "<<copy_str<<" of " << dvd_name << " added\n";
            continue;
        }
        inventory.push_back(new_dvd);
        ostr << copies <<" "<<copy_str<<" of " << dvd_name << " added\n";
    }
    else if (token == "customer") {
        std::string customer_name = read_customer_name(istr);
        int num_movies;
        istr >> num_movies;
        std::string copy_str="copies";
        if (num_movies == 1) {
            copy_str = "copy";
        }
        preference_type preference_list;
        for (int i = 0; i < num_movies; i++) {
            std::string dvd_name = read_dvd_name(istr);
            preference_type::iterator itr = preference_list.begin();
            for (; itr != preference_list.end(); itr++) {
                if ((*itr) == dvd_name) break;
            }
            if (itr != preference_list.end()) {
                ostr << "WARNING: Duplicate movie "<<dvd_name<<" on preference list!\n";
                continue;
            }
            if (find_DVD(inventory,dvd_name) == inventory.end()) {
                ostr << "WARNING: No movie named "<<dvd_name<<" in the inventory\n";
                continue;
            }
            preference_list.push_back(dvd_name);
            
        }
        if (find_customer(customers,customer_name) != customers.end()) {
            //find_customer(customers,customer_name)->add_preference(num_movies,preference_list);
            //continue;
            ostr << "WARNING: Already have a customer named " << customer_name<<std::endl;
            continue;
        }
        customer new_customer(customer_name, num_movies, preference_list);
        customers.push_back(new_customer);
        ostr << "new customer: " << customer_name << std::endl;
    }

    else if (token == "ship") {
        //ostr << "Ship DVDs\n";
        /*
        for (inventory_type::iterator itr = inventory.begin(); itr != inventory.end(); itr++) {
            std::cout <<itr->get_availables()<<"\n";
        }
         */
        shipping_algorithm(inventory,customers,ostr);
        
    }
    else if (token == "return_oldest") {
        std::string customer_name = read_customer_name(istr);
        customers_type::iterator customer_itr = find_customer(customers, customer_name);
        if (customer_itr == customers.end()) {
            ostr << "WARNING: No customer named "<< customer_name<<std::endl;
            continue;
        }
        if (customer_itr->get_has_movies() == 0) {
            ostr << "WARNING: "<<customer_name<<" has no DVDs to return!\n";
            continue;
        }
        std::string one_movie = customer_itr->return_oldest();
        ostr << customer_name <<" returns "<< one_movie <<"\n";
        inventory_type::iterator inventory_itr = find_DVD(inventory,one_movie);
        if (inventory_itr == inventory.end()) {
            ostr << "WARNING: No movie" <<one_movie<< " in the inventory.\n";
            continue;
        }
        inventory_itr->return_one();
        
    }
    else if (token == "return_newest") {
        std::string customer_name = read_customer_name(istr);
        customers_type::iterator customer_itr = find_customer(customers, customer_name);
        if (customer_itr == customers.end()) {
            ostr << "WARNING: No customer named "<< customer_name<<std::endl;
            continue;
        }
        if (customer_itr->get_has_movies() == 0) {
            ostr << "WARNING: "<<customer_name<<" has no DVDs to return!\n";
            continue;
        }
        std::string one_movie = customer_itr->return_newest();
        ostr << customer_name <<" returns "<< one_movie <<"\n";
        inventory_type::iterator inventory_itr = find_DVD(inventory,one_movie);
        if (inventory_itr == inventory.end()) {
            ostr << "WARNING: No movie" <<one_movie<< " in the inventory.\n";
            continue;
        }
        inventory_itr->return_one();
        
    }
      
    else if (token == "print_customer") {
        std::string customer_name = read_customer_name(istr);
        customers_type::iterator customer_itr = find_customer(customers, customer_name);
        if (customer_itr == customers.end()) {
            ostr << "WARNING: No customer named "<<customer_name<<"\n";
            continue;
        }
        ostr << customer_itr->get_name() << " has ";
        if (customer_itr->get_has_movies() == 0) {
            ostr << "no movies\n";
        }
        else ostr << customer_itr->get_has_movies() << " movies:\n";
        std::list<std::string> movie_list = customer_itr->get_movies();
        for (preference_type::iterator movie_itr = movie_list.begin(); movie_itr != movie_list.end(); movie_itr++) {
            ostr << "    " << (*movie_itr)<<std::endl;
        }
        if ((customer_itr->get_preferences()).size() != 0) {
            ostr << "  preference list:\n";
            preference_type preference_list = customer_itr->get_preferences();
            for (preference_type::iterator preference_itr = preference_list.begin(); preference_itr != preference_list.end(); preference_itr++)
                ostr << "    " << (*preference_itr) << "\n";
        }
        /* YOU MUST FINISH THIS IMPLEMENTATION */
    }
    else if (token == "print_dvd") {
        std::string dvd_name = read_dvd_name(istr);
        inventory_type::iterator inventory_itr = find_DVD (inventory, dvd_name);
        if (inventory_itr == inventory.end()) {
            ostr << "WARNING: No movie named "<<dvd_name<<" in the inventory"<<"\n";
            continue;
        }
        ostr << inventory_itr->get_name() << ":\n  ";
        int checkouts = inventory_itr->get_checkouts();
        int availables = inventory_itr->get_availables();
        if (checkouts == 1) {
            ostr << checkouts<<" copy checked out";
        }
        else if (checkouts > 1) {
            ostr <<checkouts<< " copies checked out";
        }
        if (checkouts !=0 && availables != 0) {
            ostr << " and ";
        }
        if (availables > 1) {
            ostr << availables << " copies available";
        }
        else if (availables == 1) {
            ostr << availables << " copy available";
        }
        ostr<<"\n";
        
    }
    else if (token == "add_preference") {
        std::string customer_name = read_customer_name(istr);
        customers_type::iterator check_customer_itr = find_customer(customers,customer_name);
        if (check_customer_itr == customers.end()) {
            ostr << "WARNING: No customer named "<< customer_name<<std::endl;
            read_dvd_name(istr);
            continue;
        }
        std::string dvd_name = read_dvd_name(istr);
        inventory_type::iterator check_dvd_itr = find_DVD(inventory,dvd_name);
        if (check_dvd_itr == inventory.end()) {
            ostr << "WARNING: No movie named "<<dvd_name<<" in the inventory\n";
            continue;
        }
        std::list<std::string> one_preference_list = check_customer_itr->get_preferences();
        preference_type::iterator check_preference_itr = one_preference_list.begin();
        for (; check_preference_itr != one_preference_list.end(); check_preference_itr++) {
            if ((*check_preference_itr) == dvd_name) break;
        }
        if (check_preference_itr != one_preference_list.end()) {
            ostr << "WARNING: "<<customer_name<<" already has "<<dvd_name<<" on his/her preference list!\n";
            continue;
        }
        if (check_customer_itr->has_movie(dvd_name)) {
            ostr << "WARNING: "<<customer_name << " currently has " << dvd_name <<"!\n";
            continue;
        }
        check_customer_itr->add_one_preference(dvd_name);
        /* YOU MUST FINISH THIS IMPLEMENTATION */
    }
    else {
        ostr << "ERROR: Unknown token " << token << std::endl;
        exit(1);
    }

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
  for (inventory_type::iterator inventory_itr = inventory.begin(); 
       inventory_itr != inventory.end(); inventory_itr++) {
    if (inventory_itr->get_name() == dvd_name) {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}

customers_type::iterator find_customer(customers_type& customer, const std::string& customer_name) {
    for (customers_type::iterator customer_itr = customer.begin();
         customer_itr != customer.end(); customer_itr++) {
        if (customer_itr->get_name() == customer_name) {
            return customer_itr;
        }
    }
    // if the customer is not found, return the .end() iterator
    return customer.end();
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
    //ostr<<(customer_itr != customers.end())<<"\n";
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
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {
      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);
      if (inventory_itr != inventory.end() && inventory_itr->available()) { 

        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->get_name() << " receives " << *preferences_itr << std::endl;
        inventory_itr->shipped();
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
