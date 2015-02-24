#include <iostream>

int main(){
    std::string a = "Kim";
    std::string b = "Tom";
    a[0] = b[0];
    std::cout << a << std::endl;
    return 0;
}
