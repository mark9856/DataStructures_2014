// File: player.h
// Purpose: Header of declaration of player record class and associated functions

#ifndef __player_h_
#define __player_h_

#include <iostream>
#include <string>
class Player{
    public:
        Player(const std::string n, const std::string t);

        // ACCESSORS
        std::string getName() const {return name;}
        std::string getTeamName() const {return teamName;}
        int getGoals() const {return goals;}
        int getAssists() const {return assists;}
        int getPenalties() const {return penalties;}

        // MODIFIERS
        void addGoal() {goals ++;}
        void addAssist() {assists ++;}
        void addPenalty() {penalties ++;}

    private:
        std::string name;
        std::string teamName;
        int goals;
        int assists;
        int penalties;
};

// use this for sorting 
bool operator< (const Player & p1, const Player & p2);
#endif
