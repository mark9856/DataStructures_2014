#include <iomanip>
#include <cstdlib>
#include <cmath>

#include "board.h"

// ==================================================================
// ==================================================================
// Implementation of the Position class


// allows a position to be output to a stream
std::ostream& operator<<(std::ostream &ostr, const Position &p) {
    ostr << '(' << p.row << "," << p.col << ')';
    return ostr;
}


// equality and inequality comparision of positions
bool operator==(const Position &a, const Position &b) {
    return (a.row == b.row && a.col == b.col);
}
bool operator!=(const Position &a, const Position &b) {
    return !(a==b);
}


// ==================================================================
// ==================================================================
// Implementation of the Board class


// ===================
// CONSTRUCTOR
// ===================

Board::Board(int r, int c) { 
    // initialize the dimensions
    rows = r; 
    cols = c; 

    // allocate space for the contents of each grid cell
    board = std::vector<std::vector<char> >(rows,std::vector<char>(cols,' '));

    // allocate space for booleans indicating the presense of each wall
    // by default, these are false == no wall
    // (note that there must be an extra column of vertical walls
    //  and an extra row of horizontal walls)
    vertical_walls = std::vector<std::vector<bool> >(rows,std::vector<bool>(cols+1,false));
    horizontal_walls = std::vector<std::vector<bool> >(rows+1,std::vector<bool>(cols,false));

    // initialize the outermost edges of the grid to have walls
    for (int i = 0; i < rows; i++) {
        vertical_walls[i][0] = vertical_walls[i][cols] = true;
    }
    for (int i = 0; i < cols; i++) {
        horizontal_walls[0][i] = horizontal_walls[rows][i] = true;
    }
}


// ===================
// ACCESSORS related to board geometry
// ===================

// Query the existance of a horizontal wall
bool Board::getHorizontalWall(double r, int c) const {
    // verify that the requested wall is valid
    // the row coordinate must be a half unit
    assert (fabs((r - floor(r))-0.5) < 0.005);
    assert (r >= 0.4 && r <= rows+0.6);
    assert (c >= 1 && c <= cols);
    // subtract one and round down because the corner is (0,0) not (1,1)
    return horizontal_walls[floor(r)][c-1];
}

// Query the existance of a vertical wall
bool Board::getVerticalWall(int r, double c) const {
    // verify that the requested wall is valid
    // the column coordinate must be a half unit
    assert (fabs((c - floor(c))-0.5) < 0.005);
    assert (r >= 1 && r <= rows);
    assert (c >= 0.4 && c <= cols+0.6);
    // subtract one and round down because the corner is (0,0) not (1,1)
    return vertical_walls[r-1][floor(c)];
}

int Board::getRobotNo(char a) {
    for(int i = 0; i < robots.size(); ++ i){
        if(a == robots[i].which){
            return i;
        }
    }
    return -1;
}

// ===================
// MODIFIERS related to board geometry
// ===================

// Add an interior horizontal wall
void Board::addHorizontalWall(double r, int c) {
    // verify that the requested wall is valid
    // the row coordinate must be a half unit
    assert (fabs((r - floor(r))-0.5) < 0.005);
    assert (r >= 0 && r <= rows);
    assert (c >= 1 && c <= cols);
    // verify that the wall does not already exist
    assert (horizontal_walls[floor(r)][c-1] == false);
    // subtract one and round down because the corner is (0,0) not (1,1)
    horizontal_walls[floor(r)][c-1] = true;
}

// Add an interior vertical wall
void Board::addVerticalWall(int r, double c) {
    // verify that the requested wall is valid
    // the column coordinate must be a half unit
    assert (fabs((c - floor(c))-0.5) < 0.005);
    assert (r >= 1 && r <= rows);
    assert (c >= 0 && c <= cols);
    // verify that the wall does not already exist
    assert (vertical_walls[r-1][floor(c)] == false);
    // subtract one and round down because the corner is (0,0) not (1,1)
    vertical_walls[r-1][floor(c)] = true;
}


// ===================
// PRIVATE HELPER FUNCTIONS related to board geometry
// ===================

char Board::getspot(const Position &p) const {
    // verify that the requested coordinate is valid
    assert (p.row >= 1 && p.row <= rows);
    assert (p.col >= 1 && p.col <= cols);
    // subtract one from each coordinate because the corner is (0,0) not (1,1)
    return board[p.row-1][p.col-1];
}


void Board::setspot(const Position &p, char a) {
    // verify that the requested coordinate is valid
    assert (p.row >= 1 && p.row <=  rows);
    assert (p.col >= 1 && p.col <= cols);
    // subtract one from each coordinate because the corner is (0,0) not (1,1)
    board[p.row-1][p.col-1] = a;
}

char Board::isGoal(const Position &p) const {
    // verify that the requested coordinate is valid
    assert (p.row >= 1 && p.row <= rows);
    assert (p.col >= 1 && p.col <= cols);
    // loop over the goals, see if any match this spot
    for (unsigned int i = 0; i < goals.size(); i++) {
        if (p == goals[i].pos) { return goals[i].which; }
    }
    // else return space indicating that no goal is at this location
    return ' ';
}


// ===================
// MODIFIERS related to robots
// ===================

// for initial placement of a new robot
void Board::placeRobot(const Position &p, char a) {

    // check that input data is reasonable
    assert (p.row >= 1 && p.row <= rows);
    assert (p.col >= 1 && p.col <= cols);
    assert (getspot(p) == ' ');

    // robots must be represented by a capital letter
    assert (isalpha(a) && isupper(a));

    // make sure we don't already have a robot with the same name
    for (unsigned int i = 0; i < robots.size(); i++) {
        assert (robots[i].which != a);
    }

    // add the robot and its position to the vector of robots
    robots.push_back(Robot(p,a));

    // mark the robot on the board
    setspot(p,a);
}

bool Board::moveRobot(int i, const std::string &direction) {

    //
    //
    // YOU NEED TO WRITE THIS FUNCTION
    //
    //

    Position position = getRobotPosition(i);
    assert(direction == "north" || direction == "south" || direction == "east" || direction == "west");
    if(direction == "north"){
        if(position.row > 1){
            Position position2 (position.row - 1, position.col);
            if(getspot(position2) != ' '){
                return false;
            }
        }

        if(getHorizontalWall(position.row - 0.5, position.col) == true){
            return false;
        }
        else{
            setspot(position, ' ');
            while(position.row > 1){
                Position position2 (position.row - 1, position.col);
                if(getHorizontalWall(position.row - 0.5, position.col) == true 
                        || getspot(position2) != ' '){
                    setspot(position, getRobot(i));
                    setRobot(position, i);
                    return true;
                }
                else{
                    position.row --;
                }
            }
            setspot(position, getRobot(i));
            setRobot(position, i);
            return true;
        }
    }
    else if(direction == "south"){
        if(position.row < getRows()){
            Position position2 (position.row + 1, position.col);
            if(getspot(position2) != ' '){
                return false;
            }
        }

        if(getHorizontalWall(position.row + 0.5, position.col) == true){
            return false;
        }
        else{
            setspot(position, ' ');
            while(position.row < getRows()){
                Position position2(position.row + 1, position.col);
                if(getHorizontalWall(position.row + 0.5, position.col) == true 
                        || getspot(position2) != ' '){
                    setspot(position, getRobot(i));
                    setRobot(position, i);
                    return true;
                }
                else{
                    position.row ++;
                }
            }
            setspot(position, getRobot(i));
            setRobot(position, i);
            return true;
        }
    }
    else if(direction == "east"){
        if(position.col < getCols()){
            Position position2 (position.row, position.col + 1);
            if(getspot(position2) != ' '){
                return false;
            }
        }

        if(getVerticalWall(position.row, position.col + 0.5) == true){
            return false;
        }
        else{
            setspot(position, ' ');
            while(position.col < getCols()){
                Position position2(position.row, position.col + 1);
                if(getVerticalWall(position.row, position.col + 0.5) == true
                        || getspot(position2) != ' '){
                    setspot(position, getRobot(i));
                    setRobot(position, i);
                    return true;
                }
                else {
                    position.col ++;
                }
            }
            setspot(position, getRobot(i));
            setRobot(position, i);
            return true;
        }
    }
    else if(direction == "west"){
        if(position.col > 1 ){
            Position position2 (position.row, position.col - 0.5);
            if(getspot(position2) != ' '){
                return false;
            }
        }

        if(getVerticalWall(position.row, position.col - 0.5) == true){
            return false;
        }
        else{
            setspot(position, ' ');
            while(position.col > 1 ){
                Position position2(position.row, position.col - 1);
                if(getVerticalWall(position.row, position.col - 0.5) == true
                        || getspot(position2) != ' '){
                    setspot(position, getRobot(i));
                    setRobot(position, i);
                    return true;
                }
                else {
                    position.col --;
                }
            }
            setspot(position, getRobot(i));
            setRobot(position, i);
            return true;
        }
    }

    return false;

}

void Board::setRobot(const Position &p, int &i) { 
    robots[i].pos = p; setspot(p, getRobot(i));
}

// ===================
// MODIFIER related to the puzzle goal
// ===================

void Board::addGoal(const std::string &gr, const Position &p) {

    // check that input data is reasonable
    assert (p.row >= 1 && p.row <= rows);
    assert (p.col >= 1 && p.col <= cols);

    char goal_robot;
    if (gr == "any") {
        goal_robot = '?';
    } else {
        assert (gr.size() == 1);
        goal_robot = gr[0];
        assert (isalpha(goal_robot) && isupper(goal_robot));
    }

    // verify that a robot of this name exists for this puzzle
    if (goal_robot != '?') {
        int robot_exists = false;
        for (unsigned int i = 0; i < robots.size(); i++) {
            if (getRobot(i) == goal_robot) 
                robot_exists = true;
        }
        assert (robot_exists);
    }

    // make sure we don't already have a robot at that location
    assert (isGoal(p) == ' ');

    // add this goal label and position to the vector of goals
    goals.push_back(Goal(p,goal_robot));
}


// ==================================================================
// PRINT THE BOARD
// ==================================================================

void Board::print() {
    // print the column headings
    std::cout << " ";
    for (int j = 1; j <= cols; j++) {
        std::cout << std::setw(5) << j;
    }
    std::cout << "\n";
    // for each row
    for (int i = 0; i <= rows; i++) {
        // don't print row 0 (it doesnt exist, the first real row is row 1)
        if (i > 0) {
            // Note that each grid rows is printed as 3 rows of text, plus
            // the separator.  The first and third rows are blank except for
            // vertical walls.  The middle row has the row heading, the
            // robot positions, and the goals.  Robots are always uppercase,
            // goals are always lowercase (or '?' for any).
            std::string first = "  ";
            std::string middle;
            for (int j = 0; j <= cols; j++) {
                if (j > 0) { 
                    // determine if a robot is current located in this cell
                    // and/or if this is the goal
                    Position p(i,j);
                    char c = getspot(p);
                    char g = isGoal(p);
                    if (g != '?') g = tolower(g);
                    first += "    ";
                    middle += " "; 
                    middle += c; 
                    middle += g; 
                    middle += " ";
                }
                // the vertical walls
                if (getVerticalWall(i,j+0.5)) {
                    first += "|";
                    middle += "|";
                } else {
                    first += " ";
                    middle += " ";
                }
            }
            // output the three rows
            std::cout << first << std::endl;
            std::cout << std::setw(2) << i << middle << std::endl;
            std::cout << first << std::endl;
        }
        // print the horizontal walls between rows
        std::cout << "  +";
        for (double j = 1; j <= cols; j++) {
            (getHorizontalWall(i+0.5,j)) ? std::cout << "----" : std::cout << "    ";
            std::cout << "+";
        }
        std::cout << "\n";
    }
}

//visualize(primeRobot, max_moves, visualizeMap);
void Board::visualizeMove(int &primeRobot, int max_moves, std::vector<std::vector<char> > &visualizeMap, int count){
    if(count == 0){
        count ++;
        Position pos = getRobotPosition(primeRobot);

        visualizeMap[pos.row - 1][pos.col - 1] = '0';
    }
    if(count > 0){
        if(count <= max_moves){
            for(int i = 0; i < numRobots(); ++ i){
                Position posOriginal = getRobotPosition(i);
                if(moveRobot(i, "north")){
                    Position pos1 = getRobotPosition(i);
                    if(i == primeRobot){
                        Position pos = getRobotPosition(primeRobot);
                        if(visualizeMap[pos.row - 1][pos.col - 1] == '.' || 
                                count < visualizeMap[pos.row - 1][pos.col - 1] - '0'){
                            visualizeMap[pos.row - 1][pos.col - 1] = count + '0';
                        }
                    }
                    if(count + 1 <= max_moves){
                        visualizeMove(primeRobot, max_moves, visualizeMap, count + 1);
                    }
                    setSpot(pos1, ' ');
                    setRobot(posOriginal, i);
                }

                if(moveRobot(i, "south")){
                    Position pos1 = getRobotPosition(i);
                    if(i == primeRobot){
                        Position pos = getRobotPosition(primeRobot);
                        if(visualizeMap[pos.row - 1][pos.col - 1] == '.'
                                || count < visualizeMap[pos.row - 1][pos.col - 1] - '0'){
                            visualizeMap[pos.row - 1][pos.col - 1] = count + '0';
                        }
                    }
                    if(count + 1 <= max_moves){
                        visualizeMove(primeRobot, max_moves, visualizeMap, count + 1);
                    }
                    setSpot(pos1, ' ');
                    setRobot(posOriginal, i);
                }

                if(moveRobot(i, "east")){
                    Position pos1 = getRobotPosition(i);
                    if(i == primeRobot){
                        Position pos = getRobotPosition(primeRobot);
                        if(visualizeMap[pos.row - 1][pos.col - 1] == '.' 
                                || count < visualizeMap[pos.row - 1][pos.col - 1] - '0'){
                            visualizeMap[pos.row - 1][pos.col - 1] = count + '0';
                        }
                    }
                    if(count + 1 <= max_moves){
                        visualizeMove(primeRobot, max_moves, visualizeMap, count + 1);
                    }
                    setSpot(pos1, ' ');
                    setRobot(posOriginal, i);
                }

                if(moveRobot(i, "west")){
                    Position pos1 = getRobotPosition(i);
                    if(i == primeRobot){
                        Position pos = getRobotPosition(primeRobot);
                        if(visualizeMap[pos.row - 1][pos.col - 1] == '.' 
                                || count < visualizeMap[pos.row - 1][pos.col - 1] - '0'){
                            visualizeMap[pos.row - 1][pos.col - 1] = count + '0';
                        }
                    }
                    if(count + 1 <= max_moves){
                        visualizeMove(primeRobot, max_moves, visualizeMap, count + 1);
                    }
                    setSpot(pos1, ' ');
                    setRobot(posOriginal, i);
                }
            }
        }
    }
}

// Print the visualizeMap
void Board::printVMap(std::vector<std::vector<char> > &visualizeMap){
    for(int i = 0; i < visualizeMap.size(); ++ i){
        for(int j = 0; j < visualizeMap[i].size(); ++ j){
            std::cout << "  " << visualizeMap[i][j];
        }
        std::cout << std::endl;
    }
}

void Board::resetGoalRobot(){
    for(int i = 0; i < robots.size(); ++ i){
        robots[i].goalReach = false;
    }
    for(int j = 0; j < goals.size(); ++ j){
        goals[j].robotReach = false;
    }
}

void Board::reachGoal(int max_moves, int count, std::vector<std::vector<std::pair<int, std::string> > > &moves, std::vector<std::pair<int ,std::string> > move){
    if(count == 0){
        count ++;
    }
    if(count > 0){
        if(count <= max_moves){
            for(int i = 0; i < numRobots(); ++ i){
                //std::cout << "RobotReachGoal(" << i << ") is " << RobotReachGoal(i) << std::endl;
                if(robots[i].goalReach == false){
                    Position posOriginal = getRobotPosition(i);
                    if(moveRobot(i, "north")){

                        move.push_back(std::make_pair(i, "north"));
                        //std::cout << i << " north " << std::endl;
                        Position pos1 = getRobotPosition(i);
                        for(int j = 0; j < numGoals(); ++ j){
                            if(getRobot(i) == toupper(getGoalRobot(j)) || getGoalRobot(j) == '?'){
                                if(getRobotPosition(i) == getGoalPosition(j)){
                                    robots[i].goalReach = true;
                                    goals[j].robotReach = true;
                                }
                                //std::cout << "Push back North" << std::endl;
                            }
                        }
                        if(count + 1 <= max_moves){
                            reachGoal(max_moves, count + 1, moves, move);
                        }
                        bool all_reach = true;
                        for(int j = 0; j < numGoals(); ++ j){
                            //std::cout << "goalReach(" << j << ") is " << goals[j].robotReach << std::endl;
                            if(goals[j].robotReach == false){
                                all_reach = false;
                            }
                        }
                        if(all_reach == true){
                            moves.push_back(move);
                            //std::cout << "push_back" << std::endl<< std::endl<< std::endl<< std::endl;
                            resetGoalRobot();
                        }
                        if(count == max_moves){
                            resetGoalRobot();
                            //std::cout << "round end" << std::endl;
                        }
                        setSpot(pos1, ' ');
                        setRobot(posOriginal, i);
                        //std::cout << std::endl;
                        //move.clear();
                        move.pop_back();
                    }

                    if(moveRobot(i, "south")){
                        move.push_back(std::make_pair(i, "south"));
                        //std::cout << i << " south " << std::endl;
                        Position pos1 = getRobotPosition(i);
                        for(int j = 0; j < numGoals(); ++ j){
                            if(getRobot(i) == toupper(getGoalRobot(j)) || getGoalRobot(j) == '?'){
                                if(getRobotPosition(i) == getGoalPosition(j)){
                                    robots[i].goalReach = true;
                                    goals[j].robotReach = true;
                                }
                            }
                            //std::cout << "Push back south" << std::endl;
                        }
                        if(count + 1 <= max_moves){
                            reachGoal(max_moves, count + 1, moves, move);
                        }
                        bool all_reach = true;
                        for(int j = 0; j < numGoals(); ++ j){
                            //std::cout << "goalReach(" << j << ") is " << goals[j].robotReach << std::endl;
                            if(goals[j].robotReach == false){
                                all_reach = false;
                            }
                        }
                        if(all_reach == true){
                            moves.push_back(move);
                            //std::cout << "push_back" << std::endl<< std::endl<< std::endl<< std::endl;
                            resetGoalRobot();
                        }
                        if(count == max_moves){
                            resetGoalRobot();
                            //std::cout << "round end" << std::endl;
                        }
                        setSpot(pos1, ' ');
                        setRobot(posOriginal, i);
                        //std::cout << std::endl;
                        //move.clear();
                        move.pop_back();
                    }

                    if(moveRobot(i, "east")){
                        move.push_back(std::make_pair(i, "east"));
                        //std::cout << i << " east " << std::endl;
                        Position pos1 = getRobotPosition(i);
                        for(int j = 0; j < numGoals(); ++ j){
                            if(getRobot(i) == toupper(getGoalRobot(j)) || getGoalRobot(j) == '?'){
                                if(getRobotPosition(i) == getGoalPosition(j)){
                                    robots[i].goalReach = true;
                                    goals[j].robotReach = true;
                                }
                            }
                            //std::cout << "Push back east" << std::endl;
                        }
                        if(count + 1 <= max_moves){
                            reachGoal(max_moves, count + 1, moves, move);
                        }
                        bool all_reach = true;
                        for(int j = 0; j < numGoals(); ++ j){
                            //std::cout << "goalReach(" << j << ") is " << goals[j].robotReach << std::endl;
                            if(goals[j].robotReach == false){
                                all_reach = false;
                            }
                        }
                        if(all_reach == true){
                            moves.push_back(move);
                            //std::cout << "push_back" << std::endl<< std::endl<< std::endl<< std::endl;
                            resetGoalRobot();
                        }
                        if(count == max_moves){
                            resetGoalRobot();
                            //std::cout << "round end" << std::endl;
                        }
                        setSpot(pos1, ' ');
                        setRobot(posOriginal, i);
                        //std::cout << std::endl;
                        //move.clear();
                        move.pop_back();
                    }

                    if(moveRobot(i, "west")){
                        move.push_back(std::make_pair(i, "west"));
                        //std::cout << i << " west " << std::endl;
                        Position pos1 = getRobotPosition(i);
                        for(int j = 0; j < numGoals(); ++ j){
                            if(getRobot(i) == toupper(getGoalRobot(j)) || getGoalRobot(j) == '?'){
                                if(getRobotPosition(i) == getGoalPosition(j)){
                                    robots[i].goalReach = true;
                                    goals[j].robotReach = true;
                                }
                            }
                            //std::cout << "Push back west" << std::endl;
                        }
                        if(count + 1 <= max_moves){
                            reachGoal(max_moves, count + 1, moves, move);
                        }
                        bool all_reach = true;
                        for(int j = 0; j < numGoals(); ++ j){
                            //std::cout << "goalReach(" << j << ") is " << goals[j].robotReach << std::endl;
                            if(goals[j].robotReach == false){
                                all_reach = false;
                            }
                        }
                        if(all_reach == true){
                            moves.push_back(move);
                            //std::cout << "push_back" << std::endl<< std::endl<< std::endl<< std::endl;
                            resetGoalRobot();
                        }
                        if(count == max_moves){
                            resetGoalRobot();
                            //std::cout << "round end" << std::endl;
                        }
                        setSpot(pos1, ' ');
                        setRobot(posOriginal, i);
                        //std::cout << std::endl;
                        //move.clear();
                        move.pop_back();
                    }
                    }
                }
            }
        }
    }


    // ==================================================================
    // ==================================================================
