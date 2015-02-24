#include <iostream>

int main(){
    char** a;
    char b = 'P';
    char* c;
    char** d;

    a = & c;
    c = new char;
    *c = 'I';
    d = new char*;
    *d = new char;
    **d = 'R';

    std::cout << **d << std::endl;
    std::cout << b << std::endl;
    std::cout << *c << std::endl;

    delete *d;
    delete d;
    delete c;
    return 0;
}
