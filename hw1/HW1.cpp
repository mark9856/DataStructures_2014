#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>

// Thinking: problem may be is the single word is as long as the limitation

// read the words from the txt document and store in the words vector
void read_words(std::vector<std::string> & words, std::ifstream & words_str, int leng){
    std::string x;
    while(words_str >> x){
        // if the word length is longer than limitation
        // seperate the long words into several smaller pieces of words with " - "
        if( x.size() > leng ){
            int i = 0;
            std::string sWord;
            while( i < x.size() ){
                // deal words besides the last part
                if(x.end() > x.begin() + i + leng - 1){ 
                    sWord.append(x.begin() + i, x.begin() + i + leng - 1);
                    sWord.append("-");
                }
                else{
                    // deal with the last part of the long word
                    sWord.append(x.begin() + i, x.end());
                }
                words.push_back(sWord);
                i = i + leng - 1;
                sWord.clear();
            }
        }

        else{
            words.push_back(x);
        }
    }
}

// set up a vector of string lines to store each string for each line
void getLines(std::vector<std::string> & lines, int leng, const std::vector<std::string> & words){
    int i = 0;
    int sum = 0;
    int track = 0;
    std::string line;
    while( i < words.size()){
        sum += words[i].size();
        i ++;
        // once the sum of the words and slots exceed the length of limitation
        if(sum + i - 2 - track >= leng){
            for(int j = track; j < i - 2; ++ j){
                line.append(words[j]);
                line.append(" ");
            }
            // deal with the last words without the whitespace
            line.append(words[i - 2]);
            lines.push_back(line);
            line.clear();
            i --;
            // use track to locate the begin of new line
            track = i;
            sum = 0;
        }
    }
    // deal with the last line 
    std::string last;
    // if the track doesn't locate in last word
    if(track < words.size() - 1){
        for(int j = track; j < words.size() - 1; ++ j){
            last.append(words[j]);
            last.append(" ");
        }
        last.append(words[words.size() - 1]);
        lines.push_back(last);
    }
    // if the track located in last word
    else if (track == words.size() - 1){
        last.append(words[words.size() - 1]);
        lines.push_back(last);
    }
}
// flush_left function
void flush_left(const std::vector<std::string> & words, int leng, std::ofstream & out_str){
    std::vector<std::string> lines;

    getLines(lines, leng, words);

    for (unsigned int m = 0; m < lines.size(); ++ m) {
        // compute the empty whitespace to add after each line of string
        std::string empty( leng - lines[m].size(),' ');
        // std::cout << "| " << lines[m] << empty << " |" << std::endl;
        out_str << "| " << lines[m] << empty << " |" << std::endl;
    }
}
// flush_right function
void flush_right(const std::vector<std::string> & words, int leng, std::ofstream & out_str){
    std::vector<std::string> lines;

    getLines(lines, leng, words);

    for (unsigned int m = 0; m < lines.size(); ++ m){
        // compute the empty whitespace to add before each line of string
        std::string empty( leng - lines[m].size(), ' ');
        // std::cout << "| " << empty << lines[m] << " |" << std::endl;
        out_str << "| " << empty << lines[m] << " |" << std::endl;
    }
}
// full_justify function
void full_justify(const std::vector<std::string> & words, int leng, std::ofstream & out_str){
    std::vector<std::string> lines;
    // emptySpace is the whitespace besides slots that need to be insert between words
    int emptySpace;
    // addSpace is the normal whitespace that need to be insert between words
    int addSpace;
    // extraSpace is the extra whitespace that need to be insert between words in the begining part
    int extraSpace;

    int i = 0;
    int sum = 0;
    int track = 0;
    int total = 0;
    std::string line;
    while( i < words.size()){
        sum += words[i].size();
        i ++;
        // once the sum of words and whitespaces between words exceed the limitation
        if(sum + i - 2 - track >= leng){
            // if the size of last word is smaller than limitation
            if(words[i - 2].size() < leng){
                // if there are more than one word in this line
                if(track != i - 2){
                    // calculate the total sum of size of the words in this lines
                    for(int k = track; k < i - 1; ++ k){
                        total += words[k].size();
                    }
                    // emptySpace is the whitespace besides slots
                    // that need to be insert between words
                    emptySpace = leng - total - i + track + 2;
                    // addSpace is the normal whitespace that 
                    // need to be insert between words
                    addSpace = emptySpace/(i - 2 - track);
                    // extraSpace is the extra whitespace that 
                    // need to be insert between words in the begining part
                    extraSpace = emptySpace%(i - 2 - track);
                    total = 0;
                    // append addSpace and extraSpace between words
                    for(int j = track; j < i - 2; ++ j){
                        line.append(words[j]);
                        line.append(" ");
                        line.append(addSpace, ' ');
                        if(extraSpace > 0){
                            line.append(" ");
                            extraSpace --;
                        }
                    }
                    // append the last word
                    line.append(words[i - 2]);
                }
                // if there is only one word in this line
                else{
                    line.append(words[i - 2]);
                }
            }
            // if the size of last word is as long as the limitation
            else if(words[i - 2].size() == leng){
                line.append(words[i - 2]);
            }
            lines.push_back(line);
            line.clear();
            i --;
            // set track to be the begining of next line
            track = i;
            sum = 0;
        }
    }
    std::string last;
    // dealing with the last line, if there are 
    if(track < words.size() - 1){
        for(int j = track; j < words.size() - 1; ++ j){
            last.append(words[j]);
            last.append(" ");
        }
        last.append(words[words.size() - 1]);
        lines.push_back(last);
    }
    else if (track == words.size() - 1){
        last.append(words[words.size() - 1]);
        lines.push_back(last);
    }

    for (unsigned int m = 0; m < lines.size(); ++ m){
        std::string empty( leng - lines[m].size(), ' ');
        // std::cout << "| " << lines[m] << empty << " |" << std::endl;
        out_str << "| " << lines[m] << empty << " |" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // input should be 5 strings
    if(argc != 5){
        std::cerr << "Usage: " << argv[0] << " words-file\n.";
        return 1;
    }

    std::ifstream words_str(argv[1]);
    if(!words_str) {
        std::cerr << "Cannot open grade file " << argv[1] << "\n";
        return 1;
    }
    // read the length of the line
    int leng = atoi(argv[3]);    

    std::vector<std::string> words;
    // read the words from the txt document and store in the words vector
    read_words(words, words_str, leng);

    if(words.size() == 0){
        std::cerr << "No words enterd, Please try again!" << std::endl;
        return 1;
    }

    std::ofstream out_str(argv[2]);
    if(!out_str){
        std::cerr << "Can not open " << argv[2] << " to write.\n";
        return 1;
    }
    // read the type
    std::string type = argv[4];

    // Head and final line
    std::string bounder (leng + 4, '-');

    // output the first line
    // std::cout << bounder << std::endl;
    out_str << bounder << std::endl;

    if(type == std::string("flush_left")){
        flush_left(words, leng, out_str);
    }
    else if(type == std::string("flush_right")){
        flush_right(words, leng, out_str);
    }
    else if(type == std::string("full_justify")){
        full_justify(words, leng, out_str);
    }
    else{
        std::cerr << "Please type in the correct type of pack";
    }

    // output the final line
    // std::cout << bounder << std::endl;
    out_str << bounder << std::endl;
    return 0;
}
