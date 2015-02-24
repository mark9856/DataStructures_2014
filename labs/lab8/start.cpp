// Starting code for Checkpoints 2 and 3.  This includes
// functions to read the grid and to output it.

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;


// A simple class to represent a point location.  It only has a
// constructor and a two public member variables.  This is one of the
// few times that you are allowed to use non-private member variables.

class Point {
    public:
        Point(int x0, int y0) : x(x0), y(y0) {}
        int x,y;
};


// Input the grid and the start location.  The input is a sequence of
// x y locations, terminated by x==0 and y==0.  The last input, which
// follows 0 0 input, is the start location.
//
// The grid is represented as a 2d vector of bools, with each location
// that is blocked --- meaning that no path can go through --- being
// represented by the value "true".  The grid is large enough to
// include all blocked points and include the starting location.  The
// first coordinate of the vector of vectors is the x coordinate, and
// the second is the y coordinate.  The format of the input is
// specified in the lab handout.

void read_grid(istream& istr, vector<vector<bool> > & blocked_grid,
        int & start_x, int & start_y) {

    // Read the x y locations into a list of Points.  Keep track of the
    // max x and max y values so that the size of the grid can be
    // determined.
    int x, y;
    int max_x = 0, max_y = 0;  // keep track of the max coordinate values
    list<Point> blocked_points;
    while ((istr >> x >> y) && ! (x==0 && y==0)) {
        blocked_points.push_back(Point(x,y));
        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
    }

    // Now that a 0 0 location has been read, read the start location.
    // If this is beyond the max x or y value then update these values.
    istr >> start_x >> start_y;
    if (start_x > max_x) max_x = start_x;
    if (start_y > max_y) max_y = start_y;

    // Make a vector of vectors with all entries marked false.   
    vector<bool> one_row_of_ys(max_y+1, false);
    vector<vector<bool> > empty_grid(max_x+1, one_row_of_ys);
    blocked_grid = empty_grid;

    // For Point in the list, mark the location in the list as blocked.
    list<Point>::iterator p;
    for (p = blocked_points.begin(); p != blocked_points.end(); ++p) {
        blocked_grid[p->x][p->y] = true;
    }
}


// Output the grid to cout.  The form of the output is explained in
// the cout statement below.

void print_grid(vector<vector<bool> > const& blocked_grid, int start_x, int start_y) {

    cout << "Here is the grid with the origin in the upper left corner, x increasing \n"
        << "horizontally and y increasing down the screen.  An 'X' represents a blocked\n"
        << "location and the 'S' represents the starting location.\n\n";

    for (int y=0; y<blocked_grid[0].size(); ++y) {
        for (int x=0; x<blocked_grid.size(); ++x) {
            if (x == start_x && y == start_y)
                cout << " S";
            else if (blocked_grid[x][y])
                cout << " X";
            else 
                cout << " .";
        }
        cout << '\n';
    }
}

void print_point(Point point){
    std::cout << " (" << point.x << " ," << point.y << ") ";
}

void find_path(vector<vector<Point> > & paths, vector<Point> path, 
        const vector<vector<bool> > & blocked_grid, const int & x, const int & y){
    if(x == 0 && y == 0){
        path.push_back(Point(x, y));
        paths.push_back(path);
        return;
    }else if(x == 0 && y > 0){
        if(blocked_grid[0][y - 1] == true){
            return;
        }
        else{
            path.push_back(Point(x, y));
            find_path(paths, path, blocked_grid, x, y - 1);
        }
    }else if(x > 0 && y == 0){
        if(blocked_grid[x - 1][y] == true){
            return;
        }
        else{
            path.push_back(Point(x, y));
            find_path(paths, path, blocked_grid, x - 1, y);
        }
    }else if(x > 0 && y > 0){
        if(blocked_grid[x - 1][y] == true){
            if(blocked_grid[x][y - 1] == true){
                return;
            }
            else{
                path.push_back(Point(x, y));
                find_path(paths, path, blocked_grid, x, y - 1);
            }
        }
        if(blocked_grid[x][y - 1] == true && blocked_grid[x - 1][y] == false){
            path.push_back(Point(x, y));
            find_path(paths, path, blocked_grid, x - 1, y);
        }
        if(blocked_grid[x][y - 1] == false && blocked_grid[x - 1][y] == false){
            path.push_back(Point(x, y));
            find_path(paths, path, blocked_grid, x - 1, y);
            find_path(paths, path, blocked_grid, x, y - 1);
        }
    }
}

void find_paths(vector<vector<Point> > & paths, const vector<vector<bool> > & blocked_grid, 
        const int & start_x, const int & start_y){
    vector<Point> path;
    find_path(paths, path, blocked_grid, start_x, start_y);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " grid-file\n";
        return 1;
    }
    ifstream istr(argv[1]);
    if (!istr) {
        cerr << "Could not open " << argv[1] << endl;
        return 1;
    }

    vector<vector<bool> > blocked_grid;
    int start_x, start_y;
    read_grid(istr, blocked_grid, start_x, start_y);
    print_grid(blocked_grid, start_x, start_y);

    // Start here with your code...

    vector<vector<Point> > paths;

    find_paths(paths, blocked_grid, start_x, start_y);
    std::cout << paths.size() << std::endl;
    for(int i = 0; i < paths.size(); ++ i){
        for(int j = 0; j < paths[i].size(); ++ j){
            print_point(paths[i][j]);
        }
        std::cout << std::endl;
    }
    return 0;
}

