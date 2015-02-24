#include <iostream>
#include <cmath>

void compute_squares(uintptr_t  a[], uintptr_t  b[], uintptr_t n){
    uintptr_t * p;
    uintptr_t * q;
    q = b;
    for(p = a; p < a + n; ++ p){
        *(q + (p - a)) = sqrt(*p);
    }
    for(p = b; p < b + n; ++ p){
        std::cout << *p << std::endl;
    }
}

int main(){
    uintptr_t n;
    std::cout << "Please input the number you want: ";
    std::cin >> n;
    uintptr_t a[n];
    uintptr_t b[n];
    uintptr_t * p;
    uintptr_t input;
    for(p = a; p < a + n; ++ p){
        std::cout << "Please input the " << p - a + 1<< " uintptr_t:";
        std::cin >> input;
        *p = input;
    }
    compute_squares(a, b, n);
    return 0;
}
