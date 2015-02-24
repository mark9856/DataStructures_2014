#include <iostream>
#include "hotel.h"

void Hotel::check_in(int floor, int room) {
    assert (floor >= 0 && floor < num_floors);
    assert (room >= 0 && room < num_rooms_per_floor[floor]);
    assert (occupancy_per_floor[floor][room] == false);
    occupancy_per_floor[floor][room] = true;
}

void Hotel::check_out(int floor, int room) {
    assert (floor >= 0 && floor < num_floors);
    assert (room >= 0 && room < num_rooms_per_floor[floor]);
    assert (occupancy_per_floor[floor][room] == true);
    occupancy_per_floor[floor][room] = false;
}

int Hotel::num_available_rooms() const {
    int answer = 0;
    for (int i = 0; i < num_floors; i++) {
        for (int j = 0; j < num_rooms_per_floor[i]; j++) {
            if (occupancy_per_floor[i][j] == false) { answer++; }
        } 
    }
    return answer;
}

Hotel::~Hotel(){
    for(int i = 0; i < num_floors; ++ i){
        delete [] occupancy_per_floor[i];
    }
    delete [] occupancy_per_floor;
    delete [] num_rooms_per_floor;
}


const Hotel& operator=(const Hotel& h){
    this -> num_floors = h.num_floors;
    this -> num_rooms_per_floor = new int[num_floors];
    for(int i = 0; i < num_floors; ++ i){
        this -> num_rooms_per_floor[i] = h.num_rooms_per_floor[i];
    }
    this -> occupancy_per_floor = new bool*[num_floors];
    for(int i = 0; i < num_floors; ++ i){
        this -> occupancy_per_floor[i] = new bool[num_rooms_per_floor[i]];
        for(int j = 0; j < num_rooms_per_floor[i]; ++ j){
            occupancy_per_floor[i][j] = false;
        }
    }
}
