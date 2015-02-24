#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(){
    int i;
    std::map<int, int> counters;

    std::vector<int> v1;
    v1.push_back(19);
    v1.push_back(83);
    v1.push_back(-12);
    v1.push_back(83);
    v1.push_back(65);
    v1.push_back(19);
    v1.push_back(45);
    v1.push_back(-12);
    v1.push_back(45);
    v1.push_back(19);
    v1.push_back(45);

    
    for(std::vector<int>::iterator v_itr = v1.begin(); v_itr != v1.end(); ++ v_itr){
        if(counters.find(*v_itr) == counters.end()){
            counters.insert(std::make_pair(*v_itr, 1));
        }
        else{
            ++ (counters.find(*v_itr) -> second);
        }
    }

    std::map<int, int>::const_iterator it;
    for(it = counters.begin(); it != counters.end(); ++ it){
        std::cout << it -> first << "\t" << it -> second << std::endl;
    }

    int mode_number = 0;
    for(it = counters.begin(); it != counters.end(); ++ it){
        if(it -> second > mode_number){
            mode_number = it -> second;
        }
    }
    std::cout << "The modes are "; 
    for(it = counters.begin(); it != counters.end(); ++ it){
        if(it -> second == mode_number){
            std::cout << it -> first << " ";
        }
    }
    std::cout << std::endl;
}
