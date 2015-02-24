#include <iostream>
#include <algorithm>
#include <vector>
#include "time.h"

int main(){
    std::vector<Time> times;
    Time t1(5, 30, 59);
    Time t2;
    Time t3(10, 40, 47);
    Time t4(13, 30, 28);
    Time t5(5, 30, 58);
    Time t6(14, 5, 4);
    t1.PrintAmPm();
    times.push_back(t1);
    times.push_back(t2);
    times.push_back(t3);
    times.push_back(t4);
    times.push_back(t5);
    times.push_back(t6);
    sort(times.begin(), times.end(), IsEarlierThan);
    for(int i = 0; i < times.size(); ++ i){
        std::cout << "The times[" << i << "] is " << std::endl;
        times[i].PrintAmPm();
        std::cout << std::endl;
    }
    return 0;
}
