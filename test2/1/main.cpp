#include <iostream>
#include "hotel.h"

int main(){
    Hotel bellvue;
    bellvue.add_floor(5);  bellvue.add_floor(5);  bellvue.add_floor(5);  bellvue.add_floor(2);
    assert (bellvue.num_available_rooms() == 17);
    bellvue.check_in(0,3);  bellvue.check_in(2,3);  bellvue.check_in(3,1);
    assert (bellvue.num_available_rooms() == 14);
    Hotel ambassador(bellvue);
    assert (ambassador.num_available_rooms() == 17);
    ambassador.check_in(0,3);
    assert (ambassador.num_available_rooms() == 16);
    return 0;
}
