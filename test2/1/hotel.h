#include <iostream>

class Hotel {
    public:
        Hotel();
        // *** PART 1: 'MUST-HAVE' PROTOTYPES ***
        // ACCESSOR
        Hotel(const Hotel& h);
        const Hotel& operator=(const Hotel& h);
        ~Hotel();
        
        int num_available_rooms() const;
        // MODIFIERS
        void add_floor(int num_rooms);
        void check_in(int floor, int room);
        void check_out(int floor, int room);
    private:
        // REPRESENTATION
        int num_floors;
        int* num_rooms_per_floor;
        bool** occupancy_per_floor;
};
