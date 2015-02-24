#include <iostream>
#include <vector>

void reverse_vector(std::vector<int> &v){
    int tmp = 0;
    for(int i = 0; i < v.size()/2; ++i){
        tmp = v[i];
        v[i] = v[v.size() - 1 -i];
        v[v.size() - 1 - i] = tmp;
    }
}

// Helper function to print array
void printArray(std::vector<int> v){
    if(v.size() == 0){
        std::cout << "There is no element in this array.";
    }
    for(int i = 0; i < v.size(); ++ i){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    //v1.push_back(4);
    printArray(v1);
    reverse_vector(v1);
    printArray(v1);
    return 0;
}
