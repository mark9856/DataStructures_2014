#include <iostream>

int main(){
    std::string name;
    std::cout << "What is your first name?" << std::endl;
    std::cin >> name;
    unsigned int leng = name.size();
    std::string border( leng + 4, '*' );
    std::string sec1("*");
    std::string sec2( leng + 2,' ');
    std::string sec = sec1 + sec2 + sec1;
    
    std::cout << border << std::endl;
    std::cout << sec << std::endl;

    for(unsigned int i = 0; i < leng; ++ i){
        std::cout << "*";
        std::string sec3( i + 1,' ');
        std::string sec4( leng - i, ' ');
        std::cout << sec3 << name[i] << sec4;
        std::cout << "*" << std::endl;
    }

    std::cout << sec << std::endl;
    std::cout << border << std::endl;
    return 0;
}
