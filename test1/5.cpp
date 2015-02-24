# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <iomanip>

int main() {
    std::ifstream istr("little_engine_that_could.txt");
    std::string word;
    int num_chars = 0;
    int num_words = 0;
    int num_sentences = 0;
    while (istr >> word) {
        num_words++;
        num_chars += word.size();
        if(word.find(".") != std::string::npos 
                || word.find("!") != std::string::npos 
                || word.find("?") != std::string::npos){
            num_sentences++;
            num_chars -= 1;
            double avrLength = double(num_chars)/num_words;

            std::cout << "sentence " << num_sentences << " #words=" 
                << std::setw(3)
                << num_words << " avg chars/word= "
                << std::setprecision(2) << std::fixed <<avrLength << std::endl;

            num_words = 0;
            num_chars = 0;
        }

        /*
        std::vector <std::string> sent;
        sent.push_back(word);
        // std::vector <std::vector <std::string> > sents;
        if(word.find(".") != std::string::npos 
                || word.find("!") != std::string::npos 
                || word.find("?") != std::string::npos){
            num_sentences ++;
            // sents.push_back(sent);
            for(int i = 0; i < sent.size(); ++ i){
                std::cout << "sent.size()" << sent.size() << "  ";
                num_chars += sent[i].size();
            }
            double avrLength = num_chars/sent.size();
            std::cout << "sentence " << num_sentences << " #words= " 
                << sent.size() << " avg chars/word= "
                << std::setprecision(1) <<avrLength << std::endl;
            num_chars = 0;
            sent.clear();
            continue;
        }
        
        for (int i = 0; i < sent.size(); ++ i){
            std::cout << sent[i] << std::endl;
        }
        

        */


    }
    return 0;
}
