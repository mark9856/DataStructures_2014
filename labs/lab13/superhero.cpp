
#include <iostream>
#include "superhero.h"


const std::string Superhero::getName() const{
    return name;
}

const std::string Superhero::getPower() const{
    return power;
}

bool Superhero::operator== (std::string const& id)const{
    return(id == identity);
}

bool Superhero::operator!= (std::string const& id)const{
    return(id != identity);
}

void Superhero::changeGood(){
    if(good){
        good = false;
    }
    else {
        good = true;
    }
}


// "Superhero Elastigirl has power Flexible"
std::ostream& operator<< (std::ostream& ostr, Superhero const& s){
    if(s.isGood()){
        ostr << "Superhero " << s.getName() << " has power " << s.getPower() << std::endl;
    }
    else{
        ostr << "Supervillain " << s.getName() << " has power " << s.getPower() << std::endl;
    }
    return ostr;
}

void operator- (Superhero & s){
    s.changeGood();
}


bool Superhero::operator> (Superhero & s2){
    if(getPower() == "Fire"){
        if(s2.getPower() == "Wood"){
            return true;
        }
        else if(s2.getPower() == "Water"){
            return false;
        }
    }
    else if(getPower() == "Water"){
        if(s2.getPower() == "Fire"){
            return true;
        }
        else if(s2.getPower() == "Wood"){
            return false;
        }
    }
    else if(getPower() == "Wood"){
        if(s2.getPower() == "Fire"){
            return false;
        }
        else if(s2. getPower() == "Water"){
            return true;
        }
    }
    return false;
}

/*
bool operator> (Superhero & s1, Superhero & s2){
    if(s1.getPower() == "fire"){
        if(s2.getPower() == "wood"){
            return true;
        }
        else if(s2.getPower() == "water"){
            return false;
        }
    }
    else if(s1.getPower() == "water"){
        if(s2.getPower() == "fire"){
            return true;
        }
        else if(s2.getPower() == "wood"){
            return false;
        }
    }
    else if(s1.getPower() == "wood"){
        if(s2.getPower() == "fire"){
            return false;
        }
        else if(s2. getPower() == "water"){
            return true;
        }
    }
}
*/
