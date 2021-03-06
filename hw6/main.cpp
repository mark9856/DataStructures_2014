#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <map>

#include "board.h"

// ==================================================================================
// ==================================================================================

// This function is called if there was an error with the command line arguments
bool usage(const std::string &executable_name) {
    std::cerr << "Usage: " << executable_name << " <puzzle_file>" << std::endl;
    std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#>" << std::endl;
    std::cerr << "       " << executable_name << " <puzzle_file> -all_solutions" << std::endl;
    std::cerr << "       " << executable_name << " <puzzle_file> -visualize <which_robot>" << std::endl;
    std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -all_solutions" << std::endl;
    std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -visualize <which_robot>" << std::endl;
    exit(0);
}

// ==================================================================================
// ==================================================================================

// load a Ricochet Robots puzzle from the input file
Board load(const std::string &executable, const std::string &filename) {

    // open the file for reading
    std::ifstream istr (filename.c_str());
    if (!istr) {
        std::cerr << "ERROR: could not open " << filename << " for reading" << std::endl;
        usage(executable);
    }

    // read in the board dimensions and create an empty board
    // (all outer edges are automatically set to be walls
    int rows,cols;
    istr >> rows >> cols;
    assert (rows > 0 && cols > 0);
    Board answer(rows,cols);

    // read in the other characteristics of the puzzle board
    std::string token;
    while (istr >> token) {
        if (token == "robot") {
            char a;
            int r,c;
            istr >> a >> r >> c;
            answer.placeRobot(Position(r,c),a);
        } else if (token == "vertical_wall") {
            int i;
            double j;
            istr >> i >> j;
            answer.addVerticalWall(i,j);
        } else if (token == "horizontal_wall") {
            double i;
            int j;
            istr >> i >> j;
            answer.addHorizontalWall(i,j);
        } else if (token == "goal") {
            std::string which_robot;
            int r,c;
            istr >> which_robot >> r >> c;
            answer.addGoal(which_robot,Position(r,c));
        } else {
            std::cerr << "ERROR: unknown token in the input file " << token << std::endl;
            exit(0);
        }
    }

    // return the initialized board
    return answer;
}
    // ==================================================================================
    // ==================================================================================

    int main(int argc, char* argv[]) {

        // There must be at least one command line argument, the input puzzle file
        if (argc < 2) {
            usage(argv[0]);
        }

        // By default, the maximum number of moves is unlimited
        int max_moves = -1;

        // By default, output one solution using the minimum number of moves
        bool all_solutions = false;

        // By default, do not visualize the reachability
        char visualize = ' ';   // the space character is not a valid robot!

        // Read in the other command line arguments
        for (int arg = 2; arg < argc; arg++) {
            if (argv[arg] == std::string("-all_solutions")) {
                // find all solutions to the puzzle that use the fewest number of moves
                all_solutions = true;
            } else if (argv[arg] == std::string("-max_moves")) {
                // the next command line arg is an integer, a cap on the  # of moves
                arg++;
                assert (arg < argc);
                max_moves = atoi(argv[arg]);
                assert (max_moves > 0);
            } else if (argv[arg] == std::string("-visualize")) {
                // As a first step towards solving the whole problem, with this
                // option, let's visualize where the specified robot can move
                // and how many steps it takes to get there
                arg++;
                assert (arg < argc);
                std::string tmp = argv[arg];
                assert (tmp.size() == 1);
                visualize = tmp[0];
                assert (isalpha(visualize) && isupper(visualize));
                visualize = toupper(visualize);
            } else {
                std::cout << "unknown command line argument" << argv[arg] << std::endl;
                usage(argv[0]);
            }
        }

        // Load the puzzle board from the input file
        Board board = load(argv[0],argv[1]);

        //
        //
        // YOUR CODE STARTS HERE
        //
        //

        // For visualize only
        if(visualize != ' '){
            // create a board
            Board boardCopy = board;
            //boardCopy.print();
            std::cout << "Reachable by robot " << visualize << ":" << std::endl;
            int primeRobot = boardCopy.getRobotNo(visualize);
            assert(primeRobot >= 0);
            std::vector<std::vector<char> > visualizeMap;
            // create a map
            visualizeMap = std::vector<std::vector<char> >(boardCopy.getRows(), 
                    std::vector<char>(boardCopy.getCols(),'.'));
            int count = 0;
            boardCopy.visualizeMove(primeRobot, max_moves, visualizeMap, count);
            // print out the map
            boardCopy.printVMap(visualizeMap);
        }

        // For max_moves and not visualize
        if(max_moves != -1 && visualize == ' '){
            assert(max_moves >= 0);
            // create a board
            Board boardCopy = board;
            boardCopy.print();
            int try_moves = 1;
            bool found = false;
            while(try_moves <= max_moves){
                // create a storage to store moves
                std::vector<std::vector<std::pair<int, std::string> > > moves;
                // create a single move
                std::vector<std::pair<int, std::string> > move;
                int count = 0;
                // come up with moves
                boardCopy.reachGoal(try_moves, count, moves, move);

                // if there is answer
                if(moves.size() != 0){
                    found = true;
                    // all_solutions
                    if(all_solutions == true){
                        std::cout << moves.size() << " different " << try_moves << " move solutions: " << std::endl;
                        std::cout << std::endl;
                        for(int i = 0; i < moves.size(); ++ i){
                            for(int j = 0; j < moves[i].size(); ++ j){
                                std::cout << "robot " << boardCopy.getRobot(moves[i][j].first) 
                                    << " moves " << moves[i][j].second << std::endl;
                            }
                            std::cout << "All goals are satisfied after " << try_moves << " moves " << std::endl;
                            std::cout << std::endl;
                        }
                        break;
                    }
                    // only one solution
                    else{
                        for(int i = 0; i < moves[0].size(); ++ i){
                            std::cout << "robot " << boardCopy.getRobot(moves[0][i].first) 
                                << " moves " << moves[0][i].second << std::endl;
                            boardCopy.moveRobot(moves[0][i].first, moves[0][i].second);
                            boardCopy.print();
                        }
                        std::cout << "All goals are satisfied after " << try_moves << " moves " << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                }
                else {
                    // increase max_moves for each
                    try_moves++;
                    //std::cout << "increase to " << try_moves << std::endl;
                }
            }
            if(!found){
                std::cout << "no solutions with " << max_moves << " or fewer moves" << std::endl;
            }
        }

        // For all_solutions only
        if(all_solutions == true && max_moves == -1){
            Board boardCopy = board;
            int try_moves = 1;
            int max_moves = 2;
            // boundary of the max_moves
            while(try_moves <= max_moves){
                std::vector<std::vector<std::pair<int, std::string> > > moves;
                std::vector<std::pair<int, std::string> > move;
                int count = 0;
                boardCopy.reachGoal(try_moves, count, moves, move);

                if(moves.size() != 0){
                    if(all_solutions == true){
                        std::cout << moves.size() << " different " << try_moves << " move solutions: " << std::endl;
                        std::cout << std::endl;
                        for(int i = 0; i < moves.size(); ++ i){
                            for(int j = 0; j < moves[i].size(); ++ j){
                                std::cout << "robot " << boardCopy.getRobot(moves[i][j].first) 
                                    << " moves " << moves[i][j].second << std::endl;
                            }
                            std::cout << "All goals are satisfied after " << try_moves << " moves " << std::endl;
                            std::cout << std::endl;
                        }
                        break;
                    }
                    else{
                        for(int i = 0; i < moves[0].size(); ++ i){
                            std::cout << "robot " << boardCopy.getRobot(moves[0][i].first) 
                                << " moves " << moves[0][i].second << std::endl;
                            boardCopy.moveRobot(moves[0][i].first, moves[0][i].second);
                            boardCopy.print();
                        }
                        std::cout << "All goals are satisfied after " << try_moves << " moves " << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                }
                else {
                    // compare different maps with different max_moves, if there is no different means no solutions
                    Board boardCopy1 = board;
                    bool available = false;
                    for(int i = 0; i < boardCopy1.numRobots(); ++ i){
                        std::vector<std::vector<char> > visualizeMap;
                        visualizeMap = std::vector<std::vector<char> >(boardCopy.getRows(), 
                                std::vector<char>(boardCopy.getCols(),'.'));
                        std::vector<std::vector<char> > visualizeMap1;
                        visualizeMap1 = std::vector<std::vector<char> >(boardCopy.getRows(), 
                                std::vector<char>(boardCopy.getCols(),'.'));
                        int count = 0;
                        boardCopy1.visualizeMove(i, max_moves, visualizeMap, count);
                        boardCopy1.visualizeMove(i, max_moves - 1, visualizeMap1, count);
                        
                        // compare with maps
                        for(int i = 0; i < visualizeMap.size(); ++ i){
                            for(int j = 0; j < visualizeMap.size(); ++ j){
                                if(visualizeMap1[i][j] != visualizeMap[i][j]){
                                    available = true;
                                }
                            }
                        }
                    }
                    if(available == true){
                        try_moves++;
                        max_moves++;
                    }
                    else{
                        std::cout << "no solutions" << std::endl;
                        break;
                    }
                }
            }
        }
        // for now...  an example of how to use the board print function
        //board.print();

    }
    // ================================================================
    // ================================================================
