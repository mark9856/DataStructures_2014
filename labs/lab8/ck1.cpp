#include <iostream>

int path(int x, int y){
    int result = 0;
    if(x == 0 && y == 0){
        return 0;
    }
    if(x == 1 && y == 0){
        return 1;
    }
    if(x == 0 && y == 1){
        return 1;
    }
    if(x != 0 && y != 0){
        result += path(x - 1, y) + path(x, y - 1);
    }
    else if(x != 0 && y == 0){
        result += path(x - 1, y);
    }
    else if(x == 0 && y != 0){
        result += path(x, y - 1);
    }
    return result;
}

int main(){
    int x, y;
    std::cout << "Please input the values of x and y: " << std::endl;
    std::cin >> x >> y;
    int z = path(x, y);
    std::cout << "The path number is: " << z << std::endl;
    return 0;
}
