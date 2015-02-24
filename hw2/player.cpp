// File: player.cpp
// Purpose: Implementation file for player class

#include <iostream>
#include <string>
#include "player.h"

Player::Player(const std::string n, const std::string t){
    name = n;
    teamName = t;
    goals = 0;
    assists = 0;
    penalties = 0;
}

bool operator< (const Player & p1, const Player & p2){
    if(p1.getGoals() + p1.getAssists() > p2.getGoals() + p2.getAssists()){
        return true;
    }
    else if(p1.getGoals() + p1.getAssists() < p2.getGoals() + p2.getAssists()){
        return false;
    }
    else if(p1.getGoals() + p1.getAssists() == p2.getGoals() + p2.getAssists()){
        if(p1.getPenalties() < p2.getPenalties()){
            return true;
        }
        else if(p1.getPenalties() > p2.getPenalties()){
            return false;
        }
        else if(p1.getPenalties() == p2.getPenalties()){
            return p1.getName() < p2.getName();
        }
    }
}    


