// File: team.cpp
// Purpose: Implementation file for the Team class.

#include <iostream>
#include <string>
#include "team.h"

Team::Team(const std::string n){
    name = n;
    wins = 0;
    losses = 0;
    ties = 0;
    goals = 0;
    penalties = 0;

    homeWins = 0;
    homeLosses = 0;
    homeTies = 0;
    awayWins = 0;
    awayLosses = 0;
    awayTies = 0;
}

float Team::getWinPercent() const{
    float WinP = (wins + 0.5 * ties)/(wins + ties + losses);
    return WinP;
}

float Team::getHomeWinPercent() const{
    float WinP = (homeWins + 0.5 * homeTies)/(homeWins + homeTies + homeLosses);
    return WinP;
}

float Team::getAwayWinPercent() const{
    float WinP = (awayWins + 0.5 * awayTies)/(awayWins + awayTies + awayLosses);
    return WinP;
}

bool operator< (const Team & t1, const Team & t2){
    if (t1.getWinPercent() > t2.getWinPercent()){
        return true;
    }
    else if (t1.getWinPercent() < t2.getWinPercent()){
        return false;
    }
    else if (t1.getWinPercent() == t2.getWinPercent()){
        if(t1.getGoals() > t2.getGoals()){
            return true;
        }
        else if (t1.getGoals() < t2.getGoals()){
            return false;
        }
        else if (t1.getGoals() == t2.getGoals()){
            return t1.getName() > t2.getName();
        }
    }
}
