#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_

#include <string>
#include <iostream>
#include <list>

class Superhero {

    public:

        friend class Team;
        Superhero(std::string n, std::string id, std::string p): name(n), identity(id), power(p), good(true){}

        // accessor function
        const std::string getName() const;
        const std::string getPower() const;

        bool operator== (std::string const& id)const;
        bool operator!= (std::string const& id)const;

        bool isGood() const{
            return good;
        }

        void changeGood();

        std::string getTrueIdentity() const{
            return identity;
        }

        bool operator> (Superhero & s2);
    private:

        // REPRESENATION
        std::string name;
        std::string identity;
        std::string power;
        bool good;
};

std::ostream& operator<< (std::ostream& ostr, Superhero const& s);
void operator- (Superhero & s);

#endif
