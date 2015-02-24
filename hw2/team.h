// File: team.h
// Purpose: Header of declaration of team record class and associated functions

#ifndef __team_h_
#define __team_h_

#include <iostream>
#include <string>

class Team{
    public:
        Team(const std::string n);

        // ACCESSORS
        std::string getName() const {return name;}
        int getWins() const {return wins;}
        int getLosses() const {return losses;}
        int getTies() const {return ties;}
        int getGoals() const {return goals;}
        int getPenalties() const {return penalties;}

        // MODIFIERS
        void addWin() {wins ++;}
        void addLoss() {losses ++;}
        void addTie() {ties ++;}
        void addGoal() {goals ++;}
        void addPenalty() {penalties ++;}

        void addHomeWin() {homeWins ++;}
        void addHomeLoss() {homeLosses ++;}
        void addHomeTie() {homeTies ++;}
        void addAwayWin() {awayWins ++;}
        void addAwayLoss() {awayLosses ++;}
        void addAwayTie() {awayTies ++;}

        // OTHER ASSOCIATION
        float getWinPercent() const;
        float getHomeWinPercent() const;
        float getAwayWinPercent() const;

    private:
        std::string name;
        int wins;
        int losses;
        int ties;
        int goals;
        int penalties;

        int homeWins;
        int homeLosses;
        int homeTies;
        int awayWins;
        int awayLosses;
        int awayTies;
};

// use this for sorting
bool operator< (const Team & t1, const Team & t2);
#endif
