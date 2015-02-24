// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
//    This file provides the code for ASCII art printing of trains.
//    You should implement all of the functions prototyped in
//    "traincar_prototypes.h" in this file.
//
// =======================================================================


#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>
#include "traincar.h"
#include <cmath>

// =======================================================================
// =======================================================================

// This helper function checks that the forward and backward pointers
// in a doubly-linked structure are correctly and consistently assigned.
void SanityCheck(TrainCar* train) {
    // an empty train is valid
    if (train == NULL) return;
    assert (train->prev == NULL);
    TrainCar *tmp = train;
    while (tmp->next != NULL) {
        // the next train better point back to me
        assert (tmp->next->prev == tmp);
        tmp = tmp->next;
    }
}


// This helper function prints one of the 5 rows of the TrainCar ASCII art
void PrintHelper(TrainCar* t, int which_row) {
    if (t == NULL) {
        // end of the line
        std::cout << std::endl;
        return;
    }

    if (which_row == 0) {
        // the top row only contains "smoke" for engine traincars
        if (t->isEngine()) {
            std::cout << "     ~~~~";
        } else {
            std::cout << "         ";
        }
    } else if (which_row == 1) {
        // the 2nd row only contains the smoke stack for engine traincars
        if (t->isEngine()) {
            std::cout << "    ||   ";
        } else {
            std::cout << "         ";
        }
    } else if (which_row == 2) {
        // the 3rd row contains the ID for each traincar
        // (and engine traincars are shaped a little differently)
        if (t->isEngine()) {
            std::cout << "   " << std::setw(6) << std::setfill('-') << t->getID();
        } else {
            std::cout << std::setw(9) << std::setfill('-') << t->getID();
        }
        std::cout << std::setfill(' ');
    } else if (which_row == 3) {
        // the 4th row is different for each TrainCar type
        if (t->isEngine()) {
            std::cout << " / ENGINE";
        } else if (t->isFreightCar()) {
            // freight cars display their weight
            std::cout << "|" << std::setw(5) << t->getWeight() << "  |";
        } else if (t->isPassengerCar()) {
            // passenger cars are simple empty boxes
            std::cout << "|       |";
        } else if (t->isDiningCar()) {
            std::cout << "|  dine |";
        } else {
            assert (t->isSleepingCar());
            std::cout << "| sleep |";
        }
    } else if (which_row == 4) {
        // final row is the same for all cars, just draw the wheels
        std::cout << "-oo---oo-";
    }

    // between cars display the '+' link symbol on the 5th row 
    // (only if there is a next car)
    if (t->next != NULL) {
        if (which_row == 4) {
            std::cout << " + ";
        } else {
            std::cout << "   ";
        }
    }

    // recurse to print the rest of the row
    PrintHelper(t->next, which_row);
}


void PrintTrain(TrainCar* train) {

    if (train == NULL) { 
        std::cout << "PrintTrain: empty train!" << std::endl; 
        return; 
    }

    // Print each of the 5 rows of the TrainCar ASCII art
    PrintHelper(train, 0);
    PrintHelper(train, 1);
    PrintHelper(train, 2);
    PrintHelper(train, 3);
    PrintHelper(train, 4);

    // UNCOMMENT THESE ADDITIONAL STATISTICS AS YOU WORK
    int total_weight = 0;
    int num_engines = 0;
    int num_freight_cars = 0;
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
    CountEnginesAndTotalWeight
        (train, total_weight,
         num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    int total_cars = num_engines+num_freight_cars+num_passenger_cars+num_dining_cars+num_sleeping_cars;
    float speed = CalculateSpeed(train);
    std::cout << "#cars = " << total_cars;
    std::cout << ", total weight = " << total_weight;
    std::cout << ", speed on 2% incline = " << std::setprecision(1) << std::fixed << speed;

    // If there is at least one passenger car, print the average
    // distance to dining car statistic
    if (num_passenger_cars > 0) {
        float dist_to_dining = AverageDistanceToDiningCar(train);
        if (dist_to_dining < 0) {
            // If one or more passenger cars are blocked from accessing the
            // dining car (by an engine car) then the distance is infinity!
            std::cout << ", avg distance to dining = inf";
        } else {
            std::cout << ", avg distance to dining = " << std::setprecision(1) << std::fixed << dist_to_dining;
        }
    }

    // If there is at least one sleeping car, print the closest engine
    // to sleeper car statistic
    if (num_sleeping_cars > 0) {
        int closest_engine_to_sleeper = ClosestEngineToSleeperCar(train);
        std::cout << ", closest engine to sleeper = " << closest_engine_to_sleeper;
    }

    std::cout << std::endl;
}


// =======================================================================
// =======================================================================

// push back new traincar to a traincar
void PushBack(TrainCar * & simple, TrainCar * back){
    // if there is not TrainCar existing
    if(simple == NULL){
        simple = back;
    }
    else{
        // if there is only a TrainCar there, just simply add the TrainCar after the existing TrainCar
        if(simple -> next == NULL){
            simple -> next = back;
            back -> prev = simple;
        }
        // if there are more than one TrainCar, add new TrainCar after the end of the existing TrainCar
        else{
            TrainCar * tmp = NULL;
            tmp = simple;
            // lead to the end of the existing TrainCar
            while(tmp -> next != NULL){
                tmp = tmp -> next;
            }
            tmp -> next = back;
            back -> prev = tmp;
        }
    }
}

// Delete all the TrainCar
void DeleteAllCars(TrainCar * & simple){
    // if not TrainCar there, return
    if(simple == NULL){
        return;
    }
    else{
        TrainCar * current = simple;
        // delete current TrainCar till not TrainCar existing
        if(current -> next != NULL){
            current = current -> next;
            delete (current -> prev);
            // use recursion
            DeleteAllCars(current);
        }
        else{
            // delete the only one TrainCar left
            delete current;
        }
    }
}

// count the number of each type of TrainCar
void CountEnginesAndTotalWeight(TrainCar * train, int & total_weight, int & num_engines, 
        int & num_freight_cars, int & num_passenger_cars, int & num_dining_cars, int & num_sleeping_cars){
    total_weight = 0;
    num_engines = 0;
    num_freight_cars = 0;
    num_passenger_cars = 0;
    num_dining_cars = 0;
    num_sleeping_cars = 0;
    // make sure there is at least one TrainCar
    if(train == NULL){
    }
    else{
        TrainCar * track = train;
        while(track != NULL){
            // add up total_weight
            total_weight += track -> getWeight();
            // found engine
            if(track -> isEngine() == 1){
                num_engines ++;
            }
            // found freight car
            else if(track -> isFreightCar() == 1){
                num_freight_cars ++;
            }
            // found Passenger car
            else if(track -> isPassengerCar() == 1){
                num_passenger_cars ++;
            }
            // found dining car
            else if(track -> isDiningCar() == 1){
                num_dining_cars ++;
            }
            // found sleeping car
            else if(track -> isSleepingCar() == 1){
                num_sleeping_cars ++;
            }
            // move forward
            track = track -> next;
        }
        if(track == NULL){
            return;
        }

    }
}

// calculate the speed of the TrainCar list
float CalculateSpeed(TrainCar * & train){
    int total_weight = 0;
    int num_engines = 0;
    int num_freight_cars = 0;
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
    CountEnginesAndTotalWeight
        (train, total_weight,
         num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    float speed1 = 500.0 * num_engines * 550.0 * 9.0;
    float speed2 = 88.0 * total_weight;
    float speed = speed1/speed2;
    return speed;
}

// calculate the average distance from each Passenger car to the dinning car
float AverageDistanceToDiningCar(TrainCar * & train){
    int total_weight = 0;
    int num_engines = 0;
    int num_freight_cars = 0;
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
    // calculate the number of each type of TrainCar
    CountEnginesAndTotalWeight
        (train, total_weight,
         num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    int total_dist = 0;
    int backCount = 0;
    int forwardCount = 0;
    TrainCar * track = train;
    TrainCar * back;
    TrainCar * forward;
    while(track != NULL){
        // track on the Passenger Car
        if(track -> isPassengerCar() == 1){
            // set up back track and forward track
            back = track;
            forward = track;
            // keep back tracking till reach engine or end of train
            while(back -> prev != NULL){
                if(back -> isDiningCar() == 1 || back -> isEngine() == 1){
                    break;
                }
                back = back -> prev;
                backCount ++;
                // break when reach dinner car
            }
            // if didn't reach dinner car, set backCount to be 0
            if(back -> isEngine() == 1 || back -> prev == NULL){
                backCount = 0;
            }
            // keep forward tracking till reach engine or end of train
            while( forward -> next != NULL){
                if(forward -> isDiningCar() == 1 || forward -> isEngine() == 1){
                    break;
                }
                forward = forward -> next;
                forwardCount ++;
                // break when reach dinner car
            }
            // if didn't reach dinner car, set forward to be 0
            if(forward -> isEngine() == 1 || forward -> next == NULL){
                forwardCount = 0;
            }
            // if both direction didn't reach dinner car, return -1
            if(backCount == 0 && forwardCount == 0){
                return -1.0;
            }
            else{
                // choose the smallest one when both are bigger than 0
                if(forwardCount > 0 && backCount > 0){
                    total_dist += std::min(forwardCount, backCount);
                }
                // choose backCount when forwardCount is 0
                else if(forwardCount == 0){
                    total_dist += backCount;
                }
                // choose forwardCount when backCount is 0
                else if(backCount == 0){
                    total_dist += forwardCount;
                }
                // reset to be 0
                forwardCount = 0;
                backCount = 0;
            }
        }
        // move track to next position
        track = track -> next;
    }
    return float(total_dist)/float(num_passenger_cars);
}

// calculate the closest distance from sleep car to the engine
int ClosestEngineToSleeperCar(TrainCar * & train){
    TrainCar * track = train;
    TrainCar * back;
    TrainCar * forward;
    int backCount = 0;
    int forwardCount = 0;
    int closestDist = 0;
    int tmp = 0;
    while(track != NULL){
        // found the sleeping car
        if(track -> isSleepingCar() == 1){
            back = track;
            forward = track;
            // move the back backward to the begining of the TrainCar list
            while(back -> prev != NULL){
                back = back -> prev;
                // record the distance
                backCount ++;
                // found the engine, break
                if(back -> isEngine() == 1){
                    break;
                }
            }
            // if already reach begining and the begining is not a engine
            if(back -> prev == NULL && back -> isEngine() != 1){
                backCount = 0;
            }
            // move the forward forward to the begining of the TrainCar list
            while(forward -> next != NULL){
                forward = forward -> next;
                // record the distance
                forwardCount ++;
                // found the engine, break
                if(forward -> isEngine() == 1){
                    break;
                }
            }
            // if already reach ending and the begining is not a engine
            if(forward -> next == NULL && forward -> isEngine() != 1){
                forwardCount = 0;
            }
            // if reach engine both side, keep the smallest one
            if(backCount > 0 && forwardCount > 0){
                tmp = std::min(backCount, forwardCount);
            }
            // if there is reach engine forward, keep the count of forward
            else if(backCount == 0 && forwardCount > 0){
                tmp = forwardCount;
            }
            // if there is reach engine backward, keep the count of backCount
            else if(backCount > 0 && forwardCount == 0){
                tmp = backCount;
            }
            // if can't reach engine in both side
            else if(backCount == 0 && forwardCount == 0){
                return 0;
            }
            // keep the smallest one
            if(closestDist == 0){
                closestDist = tmp;
            }
            // keep the smallest one
            else{
                closestDist = std::min(tmp, closestDist);
            }
        }
        // moving forward the track pointer
        track = track -> next;
    }
    return closestDist;
}



// find out way to ship freight
std::vector<TrainCar*> ShipFreight(TrainCar * & all_engines, TrainCar * & all_freight, 
        float miniSpeed, int maxCars){
    std::vector<TrainCar*> newTrains;
    TrainCar * freight = all_freight;
    TrainCar * newTrain = NULL;
    TrainCar * newEngine = all_engines;
    int totalWeight = 0;
    int numEngines = 0;
    // make sure not reach the null pointer
    while(freight != NULL){
        // start the engine from 1 till find the proper one
        numEngines ++;
        // add up other freight car till the TrainCar list is full
        for(int i = 0; i < maxCars - numEngines; ++ i){
            // add up all the weight
            if(freight != NULL){
                totalWeight += freight -> getWeight();
                freight = freight -> next;
            }
        }
        // if the TrainCar can't reach the miniSpeed
        if((9 * 125 * 25 * numEngines) / (150 * numEngines + totalWeight) < miniSpeed ){
            // re-initialize the values
            freight = all_freight;
            totalWeight = 0;
        }
        // if reach miniSpeed
        else{
            // move the engines to the proper location preparing for unlink
            for(int i = 0; i < numEngines; ++ i){
                if(newEngine != NULL){
                    newEngine = newEngine -> next;
                }
            }
            // unlink the new engine from the all_engines
            if(newEngine != NULL){
                newEngine -> prev -> next = NULL;
                newEngine -> prev = NULL;
                // PushBack the newEngine into a newTrain
                PushBack(newTrain, all_engines);
                all_engines = newEngine;
            }

            // unlink the new freight from the all_freight
            if(freight != NULL){
                freight -> prev -> next = NULL;
                freight -> prev = NULL;
                // PushBack the newfreigh car into newTrain
                PushBack(newTrain, all_freight);
                all_freight = freight;
                newTrains.push_back(newTrain);
                // re-initialize the values
                newTrain = NULL;
                numEngines = 0;
                totalWeight = 0;
            }
            // if there is not train left in the all_freight list
            else if(freight == NULL){
                // PushBack all the left train to the newTrain
                PushBack(newTrain, all_freight);
                // re-initialize the values
                all_freight = NULL;
                newTrains.push_back(newTrain);
                newTrain = NULL;
                numEngines = 0;
                totalWeight = 0;
                break;
            }
        }
    }
    return newTrains;
}



/*
   std::vector<TrainCar*> ShipFreight(TrainCar * & all_engines, TrainCar * & all_freight, 
   float miniSpeed, int maxCars){
   TrainCar * freight = all_freight;
   TrainCar * newTrain;
   TrainCar * newEngine;
   int totalWeight = 0;
   while(all_freight != NULL){
   for(int i = 0; i < maxCars / 2; ++ i){
   if(freight -> next != NULL){
   totalWeight += freight -> getWeight();
   freight = freight -> next;
   }
   }
   if((9 * 125 * 25 * 1)/(150 + totalWeight) >= miniSpeed){
   newEngine = all_engines -> next;
   all_engines -> next = NULL;
   newEngine -> prev = NULL;
   PushBack(newTrain, all_engines);
   all_engines = newEngine;
   for(int i = 0; i < (maxCars / 2) - 1; ++ i){
   if(freight -> next != NULL){
   total_weight += freight -> getWeight();
   if((9 * 125 * 25 * 1)/(150 + totalWeight) < miniSpeed){
   TrainCar * freightPrev = freight -> prev;
   freightPrev -> next = NULL;
   freight -> prev = NULL;
   PushBack(newTrain, all_freight);
   all_freight = freight;
   break;
   }
   freight = freight -> next;
   }
   }
   }
   else{
   newEngine = all_freight -> next -> next;
   all_engines -> next -> next = NULL;
   newEngine -> prev = NULL;
   PushBack(newTrain, all_engines);
   all_engines = newEngine;
   for(int i = 0; i < (maxCars / 2) - 1; ++ i){

   }
   }
   }
   }

   std::vector<TrainCar*> ShipFreight(TrainCar * & all_engines, TrainCar * & all_freight, 
   float miniSpeed, int maxCars){
   TrainCar * freight;
   TrainCar * engineTmp;
   TrainCar * engineTmp2;
   engineTmp = all_engines;
   engineTmp2 = all_engines -> next;
   engineTmp -> next = NULL;
   engineTmp2 -> prev = NULL;
   PushBack(freight, engineTmp);
   all_engines = engineTmp2;

   TrainCar * tmp = all_freight;
   TrainCar * tmp2 = tmp -> next;
   for(int i = 0; i < maxCars / 2 - 1; ++ i){
   if(tmp2 != NULL){
   tmp -> next = NULL;
   tmp2 -> prev = NULL;
   PushBack(freight, tmp);
   all_freight = tmp2;
   tmp = all_freight;
   tmp2 = tmp -> next;
   }
}
if(CalculateSpeed(freight) > miniSpeed){
    for(int i = 0; i < maxCars / 2; ++ i){
        if(tmp2 != NULL){
            tmp -> next = NULL;
            tmp2 -> prev = NULL;
            PushBack(freight, tmp);
            if(CalculateSpeed(freight) <= miniSpeed){
                TrainCars * last = freight;
                while(last != NULL){

                }

            }
            all_freight = tmp2;
            tmp = all_freight;
            tmp2 = tmp -> next;
        }
    }
}
else{
}
}
*/

// Separate the TrainCar into two TrainCars
void Separate(TrainCar * & train1, TrainCar * & train2, TrainCar * & train3){
    int total_weight = 0;
    int num_engines = 0;
    int num_freight_cars = 0;
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
    // calculate the numbers of each type of TrainCar
    CountEnginesAndTotalWeight(train1, total_weight,
            num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    // get the total number of TrainCar
    int num_total = num_engines + num_passenger_cars + num_dining_cars + num_sleeping_cars;

    //int s_e1 = 0; 
    //int s_o1 = 0;

    // if there is only two engines in the TrainCar
    if(num_engines == 2){
        TrainCar * track = train1;
        int count = 0;
        int num_count = 0;
        // there are even number TrainCars
        if(num_total%num_engines == 0){
            // first TrainCar's number
            num_count = num_total/num_engines - 1;
        }
        // there are odd number TrainCar
        else{
            // first TrainCar's number
            num_count = num_total/num_engines;
        }

        for(int i = 0; i < num_count ; ++ i){
            // record the engine number
            if(track -> isEngine() == 1){
                count ++;
            }
            // break and stay the location when there are two engines in the first half train
            if(count == 2){
                break;
            }
            track = track -> next;
        }
        // if there is only one engine in the first half train
        if(count == 1){
            // if the type of TrainCar the track in is not a engine, 
            // directly unlink the TrainCar after this track
            if(track -> isEngine() != 1){
                train3 = track -> next;
                track -> next -> prev = NULL;
                track -> next = NULL;
                train2 = train1;
                train1 = NULL;
            }
            // if the type of TrainCar the track in is a engine, directly unlink the TrainCar before this track
            else{
                track -> prev -> next = NULL;
                track -> prev = NULL;
                train2 = train1;
                train1 = NULL;
                train3 = track;

            }
        }
        // if there is two engines in the first half train
        else if(count == 2){
            TrainCar * tmp = train1;
            // find out the place to place the second engine
            for(int i = 0; i < num_count + 2; ++ i){
                tmp = tmp -> next;
            }
            // place the second engine in the place
            track -> prev -> next = track -> next;
            track -> next -> prev = track -> prev;
            track -> next = tmp;
            track -> prev = NULL;
            tmp -> prev -> next = NULL;
            tmp -> prev = track;
            train2 = train1;
            train3 = track;
            train1 = NULL;
        }
        // if there is not engine in the first half train
        else if(count == 0){
            // if the type of TrainCar the track in is not a engine, 
            if(track -> isEngine() != 1){
                TrainCar * tmp = track;
                for(int i = 0; i < num_count; ++ i){
                    track = track -> next;
                    // find the first engine in the second half train
                    if(track -> isEngine() == 1){
                        break;
                    }
                }
                // put the first engine back to the first half train
                track -> prev -> next = track -> next;
                track -> next -> prev = track -> prev;
                tmp -> prev -> next = track;
                track -> prev = tmp -> prev;
                track -> next = NULL;
                tmp -> prev = NULL;
                train2 = train1;
                train1 = NULL;
                train3 = tmp;
                tmp = NULL;
            }
            // if the type of TrainCar the track in is a engine, 
            else{
                // directly unlink the train to two part
                train3 = track -> next;
                track -> next -> prev = NULL;
                track -> next = NULL;
                train2 = train1;
                train1 = NULL;
            }
        }

    }

}
/*
void computer_separate(int num_engines, int num_total, int & s_e1, int & s_o1){
    int separate_engines1 = s_e1;
    int separate_others1 = s_o1;
    if(num_engines % 2 != 0){
        separate_engines1 = num_engines / 2 + 1;
        s_e1 = num_engines / 2 + 1;
    }
    else{
        separate_engines1 = num_engines / 2;
        s_e1 = num_engines / 2;
    }
    
    int left = (separate_engines1 * (num_total - num_engines)) % num_engines ;
    if(left == 0){
        separate_others1 = (separate_engines1 * (num_total - num_engines)) / num_engines;
        s_o1 = separate_others1;
    }
    else{
        separate_others1 = (separate_engines1 * (num_total - num_engines)) / num_engines;
        int tmp = separate_others1 + 1;
        float speed1 = (9 * 125 * 25 * separate_engines1) / (150 * separate_engines1 + 50 * separate_others1);
        float speed2 = (9 * 125 * 25 * separate_engines1) / (150 * separate_engines1 + 50 * tmp);
        float speedOriginal = (9 * 125 * 25 * num_engines) / (150 * num_engines + 50 * num_total);
        if(speedOriginal - speed2 < speed1 - speedOriginal){
            separate_others1 = tmp;
            s_o1 = tmp;
        }
    }

}
*/

/*
void Separate(TrainCar * & train1, TrainCar * & train2, TrainCar * & train3){
    int total_weight = 0;
    int num_engines = 0;
    int num_freight_cars = 0;
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
    CountEnginesAndTotalWeight(train1, total_weight,
            num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
    int num_total = num_engines + num_passenger_cars + num_dining_cars + num_sleeping_cars;
    int separate_engines1 = 0;
    int separate_others1 = 0;
    computer_separate(num_engines, num_total, separate_engines1, separate_others1);

}
*/
