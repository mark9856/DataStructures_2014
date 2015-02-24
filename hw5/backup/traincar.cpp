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

void PushBack(TrainCar * & simple, TrainCar * back){
    if(simple == NULL){
        simple = back;
    }
    else{
        if(simple -> next == NULL){
            simple -> next = back;
            back -> prev = simple;
        }
        else{
            TrainCar * tmp = simple;
            while(tmp -> next != NULL){
                tmp = tmp -> next;
            }
            tmp -> next = back;
            back -> prev = tmp;
        }
    }
}


void DeleteAllCars(TrainCar * & simple){
    if(simple == NULL){
        return;
    }
    else{
        TrainCar * current = simple;
        if(current -> next != NULL){
            current = current -> next;
            delete (current -> prev);
            DeleteAllCars(current);
        }
        else{
            delete current;
        }
    }
}

void CountEnginesAndTotalWeight(TrainCar * train, int & total_weight, int & num_engines, 
        int & num_freight_cars, int & num_passenger_cars, int & num_dining_cars, int & num_sleeping_cars){
    if(train == NULL){
    }
    else{
        TrainCar * track = train;
        while(track != NULL){
            total_weight += track -> getWeight();
            if(track -> isEngine() == 1){
                num_engines ++;
            }
            else if(track -> isFreightCar() == 1){
                num_freight_cars ++;
            }
            else if(track -> isPassengerCar() == 1){
                num_passenger_cars ++;
            }
            else if(track -> isDiningCar() == 1){
                num_dining_cars ++;
            }
            else if(track -> isSleepingCar() == 1){
                num_sleeping_cars ++;
            }
            track = track -> next;
        }
        if(track == NULL){
            return;
        }

    }
}

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

float AverageDistanceToDiningCar(TrainCar * & train){
    int total_weight = 0;
    int num_engines = 0;
    int num_freight_cars = 0;
    int num_passenger_cars = 0;
    int num_dining_cars = 0;
    int num_sleeping_cars = 0;
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


int ClosestEngineToSleeperCar(TrainCar * & train){
    TrainCar * track = train;
    TrainCar * back;
    TrainCar * forward;
    int backCount = 0;
    int forwardCount = 0;
    int closestDist = 0;
    int tmp = 0;
    while(track != NULL){
        if(track -> isSleepingCar() == 1){
            back = track;
            forward = track;
            while(back -> prev != NULL){
                back = back -> prev;
                backCount ++;
                if(back -> isEngine() == 1){
                    break;
                }
            }
            if(back -> prev == NULL && back -> isEngine() != 1){
                backCount = 0;
            }
            while(forward -> next != NULL){
                forward = forward -> next;
                forwardCount ++;
                if(forward -> isEngine() == 1){
                    break;
                }
            }
            if(forward -> next == NULL && forward -> isEngine() != 1){
                forwardCount = 0;
            }
            if(backCount > 0 && forwardCount > 0){
                tmp = std::min(backCount, forwardCount);
            }
            else if(backCount == 0 && forwardCount > 0){
                tmp = forwardCount;
            }
            else if(backCount > 0 && forwardCount == 0){
                tmp = backCount;
            }
            else if(backCount == 0 && forwardCount == 0){
                return 0;
            }
            if(closestDist == 0){
                closestDist = tmp;
            }
            else{
                closestDist = std::min(tmp, closestDist);
            }
        }
        track = track -> next;
    }
    return closestDist;
}



std::vector<TrainCar*> ShipFreight(TrainCar * & all_engines, TrainCar * & all_freight, 
        float miniSpeed, int maxCars){
    std::vector<TrainCar*> newTrains;
    TrainCar * freight = all_freight;
    TrainCar * newTrain = NULL;
    TrainCar * newEngine = all_engines;
    int totalWeight = 0;
    int numEngines = 0;
    while(freight != NULL){
        //while((9 * 125 * 25 * numEngines)/ miniSpeed < (150 * numEngines + totalWeight) || totalWeight == 0){
        numEngines ++;
        for(int i = 0; i < maxCars - numEngines; ++ i){
            if(freight != NULL){
                totalWeight += freight -> getWeight();
                freight = freight -> next;
            }
        }
        if((9 * 125 * 25 * numEngines) / (150 * numEngines + totalWeight) < miniSpeed ){
            freight = all_freight;
            totalWeight = 0;
        }
        //else if((9 * 125 * 25 * numEngines)/(150 * numEngines + totalWeight) >= miniSpeed){
        else{
            for(int i = 0; i < numEngines; ++ i){
                if(newEngine != NULL){
                    newEngine = newEngine -> next;
                }
            }
            if(newEngine != NULL){
                newEngine -> prev -> next = NULL;
                newEngine -> prev = NULL;
                PushBack(newTrain, all_engines);
                //DeleteAllCars(all_engines);
                all_engines = newEngine;
            }

            if(freight != NULL){
                freight -> prev -> next = NULL;
                freight -> prev = NULL;
                PushBack(newTrain, all_freight);
                //DeleteAllCars(all_freight);
                all_freight = freight;
                newTrains.push_back(newTrain);
                //DeleteAllCars(newTrain);
                newTrain = NULL;
                numEngines = 0;
                totalWeight = 0;
            }
            else if(freight == NULL){
                PushBack(newTrain, all_freight);
                //DeleteAllCars(all_freight);
                all_freight = NULL;
                newTrains.push_back(newTrain);
                // DeleteAllCars(newTrain);
                newTrain = NULL;
                numEngines = 0;
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
    if(num_engines == 2){
        TrainCar * track = train1;
        int count = 0;
        int num_count = 0;
        if(num_total%num_engines == 0){
            num_count = num_total/num_engines - 1;
        }
        else{
            num_count = num_total/num_engines;
        }


        for(int i = 0; i < num_count ; ++ i){
            if(track -> isEngine() == 1){
                count ++;
            }
            if(count == 2){
                break;
            }
            track = track -> next;
        }
        if(count == 1){
            if(track -> isEngine() != 1){
                train3 = track -> next;
                track -> next -> prev = NULL;
                track -> next = NULL;
                train2 = train1;
                train1 = NULL;
            }
            else{
                track -> prev -> next = NULL;
                track -> prev = NULL;
                train2 = train1;
                train1 = NULL;
                train3 = track;

            }
        }
        else if(count == 2){
            TrainCar * tmp = train1;
            for(int i = 0; i < num_count + 2; ++ i){
                tmp = tmp -> next;
            }
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
        else if(count == 0){
            if(track -> isEngine() != 1){
                TrainCar * tmp = track;
                for(int i = 0; i < num_count; ++ i){
                    track = track -> next;
                    if(track -> isEngine() == 1){
                        break;
                    }
                }
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
            else{
                train3 = track -> next;
                track -> next -> prev = NULL;
                track -> next = NULL;
                train2 = train1;
                train1 = NULL;
            }
        }

    }

}
