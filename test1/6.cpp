#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int count_partial_matches(std::vector <std::string> & sentence, std::string word, int n){
    int total = 0;
    for(int i = 0; i < sentence.size(); ++ i){
        if(sentence[i].size() == word.size()){
            int unMatch = 0;
            for(int j = 0; j < sentence[i].size(); ++ j){
                if(sentence[i][j] != word[j]){
                    unMatch ++;
                }
            }
            if(unMatch <= n){
                total ++;
                std::cout << sentence[i] << std::endl;
            }
            unMatch = 0;
        }
    }
    return total;
}

int main(){
    std::vector <std::string> sentence;
    std::ifstream istr("6.txt");
    std::string word;
    while(istr >> word){
        sentence.push_back(word);
    }
    /*
    for(int i = 0; i < sentence.size(); ++ i){
        std::cout << sentence[i] << std::endl;
    }
    */
    std::string mWord;
    std::cout << "Please type in a match word" << std::endl;
    std::cin >> mWord;

    int n;
    std::cout << "Please type in the number" << std::endl;
    std::cin >> n;

    std::cout << count_partial_matches(sentence, mWord, n) << std::endl;
    return 0;
}
