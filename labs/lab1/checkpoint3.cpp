#include <iostream>

int main() {
    unsigned int number;
    std::cout << "Please input the number of total you need: " << std::endl;
    std::cin >> number;
    float f[number];
    // input the whole array
    for (unsigned int i = 0; i < number; ++ i) {
        float ft;
        std::cout << "Please input the " << i + 1 << " float: " << std::endl;
        std::cin >> ft;
        f[i] = ft;
    }
    // get the average
    float total = 0.0;
    for (unsigned int i = 0; i < number; ++ i) {
        total += f[i];
    }
    float ave = total/number;
    std::cout << "The average is " << ave << std::endl;

    // output the numbers that are larger than average
    for (unsigned int i = 0; i < number; ++ i) {
        if(f[i] > ave)
            std::cout << f[i] << " ";
    }
    std::cout << std::endl;
}
