#include <iostream>
#include <vector>

#include "Snowfall.h"

int main(){
    Snowfall troy("Troy", 8, 1.0);
    Snowfall hartford("Hartford", 15, 2.5);
    Snowfall nyc("NYC", 10, 2.0);
    Snowfall boston("Boston", 12, 2.0);

    
    hartford.setSnowInHour(0, 1.0);
    boston.setSnowInHour(4, 2.5);
    troy.setSnowInHour(6, 0.0);
    troy.setSnowInHour(7, 0.0);

    std::vector<Snowfall> cities;
    cities.push_back(troy);
    cities.push_back(boston);
    cities.push_back(hartford);
    cities.push_back(nyc);

    std::sort(cities.begin(),cities.end(),by_total_snowfall);
    for (int i = 0; i < cities.size(); i++) {
        std::cout << "total snowfall in " << cities[i].getCityName()
            << ": " << cities[i].getTotal() << " inches" << std::endl;
    }
    
    return 0;
}
