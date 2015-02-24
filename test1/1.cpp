#include <iostream>
#include <vector>

void output(std::vector <std::string> words){
    for(int i = 0; i < words.size(); ++ i){
        std::cout << words[i] << std::endl;
    }
    std::cout << std::endl;
}

bool secondSort(std::string & wordOne, std::string & wordSecond ){
    if(wordOne.size() < wordSecond.size()){
        return true;
    }
    else if(wordOne.size() == wordSecond.size()){
        if(wordOne[0] > wordSecond[0]){
            return true;
        }
        else return false;
    }
    else return false;
}

int main(){
    std::vector <std::string> words;
    words.push_back("dog");
    words.push_back("snake");
    words.push_back("cat");
    words.push_back("ferret");
    words.push_back("gorilla");
    words.push_back("bird");
    words.push_back("jaguar");

    sort(words.begin(), words.end());
    output(words);

    sort(words.begin(), words.end(), secondSort);
    output(words);
    return 0;
}
