void print_cars(const std::map<Car, std::vector<std::string> > &cars){
    std::sort(cars);
    for(std::map<Car, std::vector<std::string> >::iterator itr = cars.begin(); itr != cars.end(); ++ itr){
       std::cout << "People who drive a " << itr -> first.getColor() << " " << itr -> first.getMaker() << std::endl;
        for(int i = 0; i < itr -> second.size(); ++ i){
            std::cout << "      " << itr -> second[i] << std::endl;
        }
    }
}


bool remove_car(const std::map<Car, std:vector<std::string> > &cars, const std::string guest, const std::string &color, const std::string &maker){
    for(std::map<Car, std::vector<std::string> >::iterator itr = cars.begin(); itr != cars.end(); ++ itr){
        if(itr -> first.getColor() == color && itr -> first.getMaker() == maker){
            for(int i = 0; i < itr -> second.size(); ++ i){
                if(itr -> second[i] == guest){
                    for(; i < itr -> second.size() - 1; ++ i){
                        itr -> second[i] = itr -> second[i + 1];
                    }
                    itr -> second.pop_back();
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}
