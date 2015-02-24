#include <iostream>
#include "time.h"

Time::Time(){
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond){
    // check hour
    if(aHour > 23 || aHour < 1){
        std::cout << "Please type in correct hour";
    }
    // check minute
    if(aMinute > 59 || aMinute < 1){
        std::cout << "Please type in correct minute";
    }
    // check second
    if(aSecond > 59 || aSecond < 1){
        std::cout << "Please type in correct second";
    }

    hour = aHour;
    minute = aMinute;
    second = aSecond;
}

// ACCESSORS
int Time::getHour() const{
    return hour;
}
int Time::getMinute() const{
    return minute;
}
int Time::getSecond() const{
    return second;
}

// MODIFIERS
void Time::setHour(int aHour){
    // check hour
    if(aHour > 23 || aHour < 1){
        std::cout << "Please type in correct hour";
    }
    hour = aHour;
}
void Time::setMinute(int aMinute){
    // check minute
    if(aMinute > 59 || aMinute < 1){
        std::cout << "Please type in correct minute";
    }
    minute = aMinute;
}
void Time::setSecond(int aSecond){
    // check second
    if(aSecond > 59 || aSecond < 1){
        std::cout << "Please type in correct second";
    }
    second = aSecond;
}
void Time::PrintAmPm(){
    // check if is PM;
    if(hour > 12){
        hour = hour - 12;
        pm = true;
    }
    else{
        pm = false;
    }
    // when hour is 0, change it to 12 PM
    if(hour == 0){
        hour = 12;
        pm = true;
    }

    // check if minute is lower than 10 
    if(minute < 10){
        std::cout << hour << ":0" << minute;
    }
    else {
        std::cout << hour << ":" << minute;
    }

    // check if second is lower than 10
    if(second < 10){
        std::cout << ":0" << second;
    }
    else {
        std::cout << ":" << second;
    }

    if(pm == true){
        std::cout << " PM" << std::endl;
    }
    else{
        std::cout << " AM" << std::endl;
    }
}

bool IsEarlierThan(const Time & t1, const Time & t2){
    if(t1.getHour() <= t2.getHour()){
        if(t1.getHour() < t2.getHour()){
            return true;
        }
        else if(t1.getHour() == t2.getHour()){
            if(t1.getMinute() < t2.getMinute()){
                return true;
            }
            else if (t1.getMinute() == t2.getMinute()){
                if(t1.getSecond() < t2.getSecond())
                    return true;
            }
        }
    }
    else{
        return false;
    }
}
/*
bool IsEarlierThan(const Time t1, const Time t2){
    if(t1.getHour() <= t2.getHour()){
        if(t1.getHour() < t2.getHour()){
            return true;
        }
        else if(t1.getHour() == t2.getHour()){
            if(t1.getMinute() < t2.getMinute()){
                return true;
            }
            else if (t1.getMinute() == t2.getMinute()){
                if(t1.getSecond() < t2.getSecond())
                    return true;
            }
        }
    }
    else{
        return false;
    }
}
*/
