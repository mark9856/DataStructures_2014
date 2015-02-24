#include <iostream>
#include <list>

void reverse_list(std::list<int> &l){
    std::list<int>::reverse_iterator ri;
    std::list<int>::iterator itr;
    itr = l.begin();
    unsigned int cout = 0;
    int tmp = 0;

    if(l.size() == 0){
        std::cout << "There is no element in this array.";
    }
    for(ri = l.rbegin(); ri != l.rend(); ++ ri){
        tmp = *itr;
        *itr = *ri;
        *ri = tmp;
        itr ++;
        cout ++;
        if(cout == l.size()/2){
            break;
        }
    }
}

void print(std::list<int> l){
    for(std::list<int>::iterator itr = l.begin(); itr != l.end(); ++ itr){
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::list<int> a;
    unsigned int i;
    for(i = 1; i < 1; ++ i){
        a.push_back(i * i);
    }
    print(a);
    reverse_list(a);
    print(a);
    return 0;
}
