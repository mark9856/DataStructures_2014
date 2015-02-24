#include <iostream>
#include <cassert>
#include <vector>
#include <string>


// ==================================================================
// ==================================================================
// A tiny all-public helper class to record a 2D board position

class Position {
    public:
        // the coordinate (-1,-1) is invalid/unitialized
        Position(int r=-1,int c=-1) : row(r),col(c) {}
        int row,col;
};

// convenient functions to print and equality compare Positions
std::ostream& operator<<(std::ostream &ostr, const Position &p);
bool operator==(const Position &a, const Position &b);
bool operator!=(const Position &a, const Position &b);


// ==================================================================
// ==================================================================
// A tiny all-public helper class to store the position & label of a
// robot.  A robot label must be a capital letter.

class Robot {
    public:
        Robot(Position p, char w) : pos(p), which(w), goalReach(false) { 
            assert (isalpha(w) && isupper(w)); }
        Position pos;
        char which;
        bool goalReach;
};


// ==================================================================
// ==================================================================
// A tiny all-public helper class to store the position & label of a
// goal.  A goal label must be an upper case letter or '?' indicating
// that any robot can occupy this goal to solve the puzzle.

class Goal {
    public:
        Goal(Position p, char w) : pos(p), which(w), robotReach(false){ 
            assert (w == '?' || (isalpha(w) && isupper(w))); 
        }
        Position pos;
        char which;
        bool robotReach;
};


// ==================================================================
// ==================================================================
// A class to hold information about the puzzle board including the
// dimensions, the location of all walls, the current position of all
// robots, the goal location, and the robot (if specified) that must
// reach that position

class Board {
    public:

        // CONSTRUCTOR
        Board(int num_rows, int num_cols);

        // ACCESSORS related the board geometry
        int getRows() const { return rows; }
        int getCols() const { return cols; }
        bool getHorizontalWall(double r, int c) const;
        bool getVerticalWall(int r, double c) const;

        // ACCESSORS related to the robots and their current positions
        unsigned int numRobots() const { return robots.size(); }
        char getRobot(int i) const { assert (i >= 0 && i < (int)numRobots()); return robots[i].which; }
        int getRobotNo(char a);
        Position getRobotPosition(int i) const { assert (i >= 0 && i < (int)numRobots()); return robots[i].pos; }
        void setGoalRobot(int i) {robots[i].goalReach = true;}
        bool RobotReachGoal(int i) const { assert (i >= 0 && i < (int)numRobots()); return robots[i].goalReach;}

        // ACCESSORS related to the overall puzzle goals
        unsigned int numGoals() const { return goals.size(); }
        // (if any robot is allowed to reach the goal, this value is '?')
        char getGoalRobot(int i) const { assert (i >= 0 && i < (int)numGoals()); return goals[i].which; }
        Position getGoalPosition(int i) const { assert (i >= 0 && i < (int)numGoals()); return goals[i].pos; }

        // MODIFIERS related to board geometry
        void addHorizontalWall(double r, int c);
        void addVerticalWall(int r, double c);

        // MODIFIERS related to robot position
        // initial placement of a new robot
        void placeRobot(const Position &p, char a);
        // move an existing robot
        bool moveRobot(int i, const std::string &direction);
        // set new position for robots
        void setRobot(const Position &p, int &i);
        // reset spot
        void setSpot(const Position &p, char a) {setspot(p, a); }

        // MODIFIER related to puzzle goals
        void addGoal(const std::string &goal_robot, const Position &p);

        // PRINT
        void print();

        // mimic the movement
        void visualizeMove(int &primeRobot, int max_moves, std::vector<std::vector<char> > &visualizeMap, int count);

        // Print the visualizeMap
        void printVMap(std::vector<std::vector<char> > &visualizeMap);

        // come out with the moves
        void reachGoal(int max_moves, int count, std::vector<std::vector<std::pair<int, std::string> > > &moves, std::vector<std::pair<int ,std::string> > move);

        // reset back the goals and robots
        void resetGoalRobot();

    private:

        // private helper functions
        char getspot(const Position &p) const;
        void setspot(const Position &p, char a);
        char isGoal(const Position &p) const;

        // REPRESENTATION

        // the board geometry
        int rows;
        int cols;
        std::vector<std::vector<char> > board;
        std::vector<std::vector<bool> > vertical_walls;
        std::vector<std::vector<bool> > horizontal_walls;

        // the names and current positions of the robots
        std::vector<Robot> robots;

        // the goal positions & the robots that must reach them
        std::vector<Goal> goals;
};
