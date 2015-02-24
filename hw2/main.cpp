#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <string>

// include two self-created header
#include "team.h"
#include "player.h"

// use this function to find the location of the team in the vector of Team
// by the team name
int findTeam(std::string teamName, std::vector <Team> & teams){
    for(int i = 0; i < teams.size(); ++ i){
        if(teams[i].getName() == teamName){
            return i;
        }
    }
    teams.push_back(Team(teamName));
    // return the location of new added team
    return teams.size() - 1;
}

// use this function to identify the location of the player in the vector of Player
// by the player name and team name
int findPlayer(std::string playerName, std::string teamName, std::vector <Player> & players){
    for(int i = 0; i < players.size(); ++ i){
        if(players[i].getName() == playerName && players[i].getTeamName() == teamName){
            return i;
        }
    }
    players.push_back(Player(playerName, teamName));
    // return the location of new added player
    return players.size() - 1;
}

// read the infile and store in vector of Team and Player
void read(std::ifstream & in_str, std::vector <Team> & teams, std::vector <Player> & players){
    std::string day, month, date, year;
    // ifstream data, month, day and year
    while(in_str >> date >> month >> day >> year){
        std::string awayTeam, homeTeam, where;
        // ifstream awayTeam, at and homeTeam
        in_str >> awayTeam >> where >> homeTeam;
        // find the location of awayTeam in vector of Team
        int awayTeamId = findTeam(awayTeam, teams);
        // find the location of homeTeam in vector of Team
        int homeTeamId = findTeam(homeTeam, teams);
        // set up the total goal
        int awayTeamGoals = 0;
        int homeTeamGoals = 0;
        // make sure is at or vs.
        assert (where == "at" || where == "vs.");
        std::string type;
        // ifstream type, which should be PERIOD or FINAL
        while(in_str >> type){
            // when type is PERIOD
            if(type == "PERIOD"){
                // ifstream next word, which should be number 1, 2 or 3
                in_str >> type;    
            }
            // if type contain the mark of ":", which means time
            else if(type.find(":") != std::string::npos){
                std::string teamName;
                // ifstream the team name
                in_str >> teamName;
                // find the location of the team in the vector of Team
                int teamId = findTeam(teamName, teams);
                // make sure the team id is the same with the away or home team id
                assert (teamId == awayTeamId || teamId == homeTeamId);
                std::string kind;
                // ifstream the next word, which should be penalty or goal
                while(in_str >> kind){
                    // if the word is penalty
                    if(kind == "penalty"){
                        std::string playerName, penaltyTime, penaltyReason;
                        // add penalty to the team
                        teams[teamId].addPenalty();
                        // ifstream Player name, penalty Time and penalty Reason
                        in_str >> playerName >> penaltyTime >> penaltyReason;
                        // make sure the player name is not "BENCH"
                        if(playerName != "BENCH"){
                            // use the player name, team name to find
                            // the player location in vector of Player
                            int playerId = findPlayer(playerName, teamName, players);
                            // add penalty to the player
                            players[playerId].addPenalty();
                        }
                        // if the player name happens to be "BENCH"
                        else{
                            // do nothing

                        }
                        break;
                    }
                    else{
                        // make sure the word should be "goal"
                        assert(kind == "goal");
                        // add goal to the team
                        teams[teamId].addGoal();
                        // when the team is away team
                        if(teamId == awayTeamId){
                            // add goal to away team
                            awayTeamGoals++;
                        }
                        else{
                            // else add goal to home team
                            homeTeamGoals++;
                        }
                        std::string playerName;
                        // read player name
                        in_str >> playerName;
                        // find the player location in the vector of Player
                        int playerId = findPlayer(playerName, teamName, players);
                        // add goal to player
                        players[playerId].addGoal();
                        std::string mark;
                        // read the "("
                        in_str >> mark;
                        // make sure is "("
                        assert(mark == "(");
                        // read the next word
                        while(in_str >> mark){
                            // if the next word is not ")"
                            if(mark == ")"){
                                // jump out
                                break;
                            }
                            else{
                                // else find the player id
                                int playerId = findPlayer(mark, teamName, players);
                                // add assist to this player
                                players[playerId].addAssist();
                            }
                        }
                        break;
                    }
                }
            }
            // when the word is "FINAL"
            else if(type == "FINAL"){
                std::string t1, t2, s1, s2;
                // read the teams and scores
                in_str >> t1 >> s1 >> t2 >> s2;
                break;
            }
        }

        // identify which team win 
        // and add win, loss and tie
        if(awayTeamGoals < homeTeamGoals){
            teams[homeTeamId].addWin();
            teams[awayTeamId].addLoss();

            teams[homeTeamId].addHomeWin();
            teams[awayTeamId].addAwayLoss();
        }
        else if (awayTeamGoals > homeTeamGoals){
            teams[homeTeamId].addLoss();
            teams[awayTeamId].addWin();

            teams[homeTeamId].addHomeLoss();
            teams[awayTeamId].addAwayWin();
        }
        else if (awayTeamGoals == homeTeamGoals){
            teams[homeTeamId].addTie();
            teams[awayTeamId].addTie();

            teams[homeTeamId].addHomeTie();
            teams[awayTeamId].addAwayTie();
        }
    }
}

// use this function to find the max length of team name
int getMax(const std::vector <Team> teams){
    int maxLength = 0;
    for(int i = 0; i < teams.size(); ++ i){
        int tmp = teams[i].getName().size();
        maxLength = std::max(maxLength,tmp);
    }
    return maxLength;
}

// use this function to find the max length of player name
int getMax(const std::vector <Player> players){
    int maxLength = 0;
    for(int i = 0; i < players.size(); ++ i){
        int tmp = players[i].getName().size();
        maxLength = std::max(maxLength, tmp);
    }
    return maxLength;
}

// use this function to find the max length of team name
int getTeamMax(const std::vector <Player> players){
    int maxLength = 0;
    for(int i = 0; i < players.size(); ++ i){
        int tmp = players[i].getTeamName().size();
        maxLength = std::max(maxLength, tmp);
    }
    return maxLength;
}

// output the team performance
void outputTeam(const std::vector <Team> teams, std::ofstream & out_str){
    // get the maxLength of team name
    int maxLength = getMax(teams);
    // set up title
    const std::string header = "Team Name" + std::string(maxLength - 9 + 4, ' ')
        + "W   " + "L   " + "T   " + "Win%  " + "Goals  " + "Penalties";
    // output the header
    // std::cout << header << std::endl;
    out_str << header << std::endl;
    for(int i = 0; i < teams.size(); ++ i){
        /*
        std::cout << teams[i].getName() 
            << std::string(maxLength - teams[i].getName().size() + 1, ' ')
            << std::setw(4) << teams[i].getWins() 
            << std::setw(4) << teams[i].getLosses()
            << std::setw(4) << teams[i].getTies()
            << std::setw(7) << std::setprecision(2) 
            << std::fixed << teams[i].getWinPercent()
            << std::setw(7) << teams[i].getGoals()
            << std::setw(11) << teams[i].getPenalties() << std::endl;
            */
        out_str << teams[i].getName() 
            << std::string(maxLength - teams[i].getName().size() + 1, ' ')
            << std::setw(4) << teams[i].getWins() 
            << std::setw(4) << teams[i].getLosses()
            << std::setw(4) << teams[i].getTies()
            << std::setw(7) << std::setprecision(2) 
            << std::fixed << teams[i].getWinPercent()
            << std::setw(7) << teams[i].getGoals()
            << std::setw(11) << teams[i].getPenalties() << std::endl;

    }
}

// output player performance
void outputPlayer(const std::vector <Player> players, std::ofstream & out_str){
    // get the maxLength of player name 
    int maxLength = getMax(players);
    // get the max length of the player's team name
    int maxTeamLength = getTeamMax(players);
    const std::string header = "Player Name" + std::string(maxLength - 11 + 2, ' ')
        + "Team" + std::string(maxTeamLength - 4 + 3,' ') + "Goals  Assists  Penalties";
    // std::cout << header << std::endl;
    out_str << header << std::endl;
    for(int i = 0; i < players.size(); ++ i){
        /*
        std::cout << players[i].getName()
            << std::string(maxLength - players[i].getName().size() + 2, ' ')
            << players[i].getTeamName() 
            << std::string(maxTeamLength - players[i].getTeamName().size() + 3,' ')
            << std::setw(5) << std::right << players[i].getGoals()
            << std::setw(9) << players[i].getAssists()
            << std::setw(11) << players[i].getPenalties()
            << std::endl;
            */
        out_str << players[i].getName()
            << std::string(maxLength - players[i].getName().size() + 2, ' ')
            << players[i].getTeamName() 
            << std::string(maxTeamLength - players[i].getTeamName().size() + 3,' ')
            << std::setw(5) << std::right << players[i].getGoals()
            << std::setw(9) << players[i].getAssists()
            << std::setw(11) << players[i].getPenalties()
            << std::endl;
    }
}

// output the win percent home and away, and compare each other
void outputWinP(const std::vector <Team> teams, std::ofstream & out_str){
    // get the max length of team name
    int maxLength = getMax(teams);
    // std::cout << "For the team with more than 20 goals" << std::endl;
    out_str << "For the team with more than 20 goals" << std::endl;
    const std::string header = "Team Name" + std::string(maxLength - 9 + 4, ' ')
        + "Win%  " +"Home_Win%  " + "Away_Win%  " + "Home_Field_Advantage";
    // std::cout << header << std::endl;
    out_str << header << std::endl;
    for(int i = 0; i < teams.size(); ++ i){
        // use the teams which has goals more than 20
        if(teams[i].getGoals() > 20){
            // indicator of whether own Home Field Advantage
            std::string FieldBetter = "No";
            // set indicator to be "Yes"
            if(teams[i].getHomeWinPercent() > teams[i].getAwayWinPercent()){
                FieldBetter = "Yes";
            }
            /*
            std::cout << teams[i].getName() 
                << std::string(maxLength - teams[i].getName().size() + 1, ' ')
                << std::setw(7) << std::setprecision(2) << std::fixed << teams[i].getWinPercent()
                << std::setw(11) << std::setprecision(2) << std::fixed << teams[i].getHomeWinPercent()
                << std::setw(11) << std::setprecision(2) << std::fixed << teams[i].getAwayWinPercent()
                << std::setw(12) << FieldBetter
                << std::endl;
                */
            out_str << teams[i].getName() 
                << std::string(maxLength - teams[i].getName().size() + 1, ' ')
                << std::setw(7) << std::setprecision(2) << std::fixed << teams[i].getWinPercent()
                << std::setw(11) << std::setprecision(2) << std::fixed << teams[i].getHomeWinPercent()
                << std::setw(11) << std::setprecision(2) << std::fixed << teams[i].getAwayWinPercent()
                << std::setw(12) << FieldBetter
                << std::endl;
        }
    }
}

// calculate the Home Field Advantage percent
void outputFieldAv(const std::vector <Team> & teams, std::ofstream & out_str){
    int total = 0;
    int betterTotal = 0;
    for(int i = 0; i < teams.size(); ++ i){
        // use the teams with more than 20 goals
        if(teams[i].getGoals() > 20){
            // increase total number of teams
            total ++;
            if(teams[i].getHomeWinPercent() > teams[i].getAwayWinPercent()){
                // increase the number of team with Home Field Advantage
                betterTotal ++;
            }
        }
    }
    // calculate the percent of team with Home Field Advantage
    float finalBetter = float(betterTotal)/float(total);
    // std::cout << "The percent of teams with Home Field Advantage " << std::endl
    //    << "among the teams with more than 20 goals is: " 
    //    << std::setprecision(2) << finalBetter << std::endl;
    out_str << "The percent of teams with Home Field Advantage " << std::endl
        << "among the teams with more than 30 goals is: " 
        << std::setprecision(2) << finalBetter << std::endl;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        std::cerr << "Usage:\n " << argv[0] << " infile-games outfile-rankings\n";
        return 1;
    }
    std::ifstream in_str(argv[1]);
    if(!in_str){
        std::cerr << "Could not open " << argv[1] << " to read\n";
        return 1;
    }
    std::ofstream out_str(argv[2]);
    if(!out_str){
        std::cerr << "Could not open " << argv[2] << " to write\n";
        return 1;
    }

    std::vector <Team> teams;
    std::vector <Player> players;
    // use read function to read ifstream
    read(in_str, teams, players);

    // sort the teams
    std::sort(teams.begin(), teams.end());
    // output teams
    outputTeam(teams, out_str);

    // std::cout << std::endl;
    out_str << std::endl;

    // sort the players
    std::sort(players.begin(), players.end());
    // output players
    outputPlayer(players, out_str);

    // std::cout << std::endl;
    out_str << std::endl;

    // std::cout << "< ** YOUR STATISTIC GOES HERE ** >" << std::endl;
    out_str << "< ** YOUR STATISTIC GOES HERE ** >" << std::endl;

    // output the win percent home and away, and compare each other
    outputWinP(teams, out_str);

    // std::cout << std::endl;
    out_str << std::endl;

    // calculate the Home Field Advantage percent
    outputFieldAv(teams, out_str);
    return 0;
}

