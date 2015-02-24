#include <iostream>
#include <vector>

#include "Snowfall.h"

Snowfall::Snowfall(std::string cityName, int durationHour, float snowAmount){
    city = cityName;
    duration = durationHour;
    for(int i = 0; i < duration; ++ i){
        snows.push_back(snowAmount);
    }
}

std::string Snowfall::getCityName() const{
    return city;
}

float Snowfall::getTotal() const{
    float total = 0;
    for(int i = 0; i < duration; ++ i){
        total += snows[i];
    }
    return total;
}

void Snowfall::setSnowInHour(int sHour, float snowAmount){
    snows[sHour] = snowAmount;
}

bool by_total_snowfall(const Snowfall s1, const Snowfall s2){
    if(s1.getTotal() > s2.getTotal()){
        return true;
    }
    else return false;
}
