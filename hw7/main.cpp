// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <assert.h>
#include <cstdlib>
#include <stdlib.h>


#include "MersenneTwister.h"

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
//typedef  /*** YOUR TYPE ***/  MY_MAP;
typedef  std::map<std::string, std::map<std::string, int> > MY_MAP;



// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
    char c;
    word.clear();
    while (istr) {
        // just "peek" at the next character in the stream
        c = istr.peek();
        if (isspace(c)) {
            // skip whitespace before a word starts
            istr.get(c);
            if (word != "") {
                // break words at whitespace
                return true;
            }
        } else if (c == '"') {
            // double quotes are a delimiter and a special "word"
            if (word == "") {
                istr.get(c);
                word.push_back(c);
            }
            return true;
        } else if (isalpha(c)) {
            // this a an alphabetic word character
            istr.get(c);
            word.push_back(tolower(c));
        } else {
            // ignore this character (probably punctuation)
            istr.get(c);
        }
    }
    return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
    // returns a vector of strings of the different words
    std::vector<std::string> answer;
    std::string word;
    bool open_quote = false;
    while (ReadNextWord(istr,word)) {
        if (word == "\"") {
            if (open_quote == false) { open_quote=true; }
            else { break; }
        } else {
            // add each word to the vector
            answer.push_back(word);
        }
    }
    return answer;
}


// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method, std::string &last) {
    // open the file stream
    std::ifstream istr(filename.c_str());
    if (!istr) { 
        std::cerr << "ERROR cannot open file: " << filename << std::endl; 
        exit(1);
    } 
    // verify the window parameter is appropriate
    if (window < 2) {
        std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
    }
    // verify that the parse method is appropriate
    bool ignore_punctuation = false;
    if (parse_method == "ignore_punctuation") {
        ignore_punctuation = true;
    } else {
        std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
        exit(1);
    }



    //
    // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
    //

    std::string word;
    std::list<std::string> lst;

    // O(n)
    while (ReadNextWord(istr, word)) {
        // skip the quotation marks (not used for this part)
        if (word == "\"") continue;

        if(window == 2){
            // if it's the first word just push_back value into list
            if(lst.size() < 1){
                lst.push_back(word);
            }
            // if it's not the first word, push_back into data
            else{
                // push_back last word and the word before it
                // O(log m * (log p)^(w - 1))
                ++((data[lst.front()])[word]);
                // clean the list
                lst.pop_front();
                // add last word into the list
                lst.push_back(word);
            }
        }
        //
        // ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
        // INSERTING THESE WORDS INTO THE DATA STRUCTURE
        //
    }
    // set the last word 
    last = lst.back();
}
void LoadSampleText(std::map<std::string, MY_MAP> &data, const std::string &filename, 
        int window, const std::string &parse_method, std::string &last, std::string &last2) {
    // open the file stream
    std::ifstream istr(filename.c_str());
    if (!istr) { 
        std::cerr << "ERROR cannot open file: " << filename << std::endl; 
        exit(1);
    } 
    // verify the window parameter is appropriate
    if (window < 2) {
        std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
    }
    // verify that the parse method is appropriate
    bool ignore_punctuation = false;
    if (parse_method == "ignore_punctuation") {
        ignore_punctuation = true;
    } else {
        std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
        exit(1);
    }
    //
    // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
    //

    std::string word;
    std::list<std::string> lst;

    while (ReadNextWord(istr, word)) {
        // skip the quotation marks (not used for this part)
        if (word == "\"") continue;

        if(window == 3){
            // if it's the first two words just push_back value into list
            if(lst.size() < 2){
                lst.push_back(word);
            }
            else{
                // push_back last word and the two words before it
                ++(((data[lst.front()])[lst.back()])[word]);
                // delete the front element of list
                lst.pop_front();
                // push_back the last word into the list
                lst.push_back(word);
            }
        }
        //
        // ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
        // INSERTING THESE WORDS INTO THE DATA STRUCTURE
        //
    }
    // set the last two words
    last = lst.back();
    last2 = lst.front();
}

// print out the words in most_common 
void generateNext(MY_MAP &data, std::string word, int times){
    // O(log m)
    std::map<std::string, int>::const_iterator m_itr = (data.find(word) -> second).begin();
    std::string selected = m_itr -> first;
    // find out the word with largest happen times
    int bigNo = m_itr -> second;
    // O(log m * p)
    for(; m_itr != (data.find(word) -> second).end(); ++ m_itr){
        if(bigNo < m_itr -> second){
            selected = m_itr -> first;
            bigNo = m_itr -> second;
        }
    }
    // print out 
    std::cout << selected << " ";
    // recusion
    times --;
    if(times > 0){
        // print out the words in most_common 
        generateNext(data, selected, times);
    }
}

// print out the words when window is 3 
void generateNextWord(std::map<std::string, MY_MAP> &data, std::list<std::string> &lst, int times, bool random_flag){
    // It's in most_common
    if(!random_flag){
        // there is only one word in the this sentence
        if(lst.size() == 1){
            // O(log m)
            std::map<std::string, std::map<std::string, int> >::const_iterator m_itr = (data[lst.front()]).begin();
            std::string selected = m_itr -> first;
            // find out the word with largest happen times
            int bigNo = 0;

            // O(log m *  p)
            for(; m_itr != (data[lst.front()]).end(); ++ m_itr){
                int count = 0;
                std::map<std::string, int>::const_iterator n_itr = (m_itr -> second).begin();
                // O( p)
                for(; n_itr != (m_itr -> second).end(); ++ n_itr){
                    count += n_itr -> second;
                }
                if(bigNo < count ){
                    selected = m_itr -> first;
                    bigNo = count;
                }
            }
            // print out 
            std::cout << selected << " ";
            // push_back selected word into list
            lst.push_back(selected);
        }
        // if there are two words in the list use different way
        else if(lst.size() == 2){
            // if can find the two words together
            if((data[lst.front()]).find(lst.back()) != data[lst.front()].end()){
                // O(log m * log p)
                std::map<std::string, int>::const_iterator m_itr = ((data[lst.front()])[lst.back()]).begin();
                std::string selected = m_itr -> first;
                // find out the word with largest happen times
                int bigNo = 0;
                // O(log m * (log p)^(w - 1))
                for(; m_itr != ((data[lst.front()])[lst.back()]).end(); ++ m_itr){
                    if(bigNo < m_itr -> second){
                        selected = m_itr -> first;
                        bigNo = m_itr -> second;
                    }
                }
                // print out 
                std::cout << selected << " ";
                // pop_front the list
                lst.pop_front();
                // push_back selected word to make sure there are two elements in this list
                lst.push_back(selected);
            }
        }
        // recusion
        times --;
        if(times > 0){
            // print out the words when window is 3 
            generateNextWord(data, lst, times, random_flag);
        }
    }
    // if it's in random
    else if(random_flag){
        // random number creator
        MTRand mtrand;
        // create random possibility
        double possibility = mtrand.randExc();
        // if there is only one word in the sentence
        if(lst.size() == 1){
            // calculate the total amount in order to calculate the happen possibility
            int total = 0;
            // O(log m)
            std::map<std::string, std::map<std::string, int> >::const_iterator m_itr = (data[lst.front()]).begin();
            // O(log m * p)
            for(; m_itr != (data[lst.front()]).end(); ++ m_itr){
                int count = 0;
                std::map<std::string, int>::const_iterator n_itr = (m_itr -> second).begin();
                // O(log m * p * p)
                for(; n_itr != (m_itr -> second).end(); ++ n_itr){
                    count += n_itr -> second;
                }
                total += count;
            }
            // reset back to beginning
            m_itr = (data[lst.front()]).begin();
            // found out the selected word
            std::string selected = m_itr -> first;
            // found out the words happen rate
            int totalCount = 0;
            // O(log m * p)
            for(; m_itr != (data[lst.front()]).end(); ++ m_itr){
                // total rate of happen for each word
                int count = 0;
                std::map<std::string, int>::const_iterator n_itr = (m_itr -> second).begin();
                // O(log m * p * p)
                for(; n_itr != (m_itr -> second).end(); ++ n_itr){
                    count += n_itr -> second;
                }
                // if the words is in this possibility print out 
                if(possibility > double(totalCount)/total 
                        && possibility <= double(totalCount + count)/total){
                    selected = m_itr -> first;
                }
                totalCount += count;
            }
            std::cout << selected << " ";
            // push_back selected word into list
            lst.push_back(selected);
        }
        // if there are two words in the list
        else if(lst.size() == 2){
            // if can find this two words together
            if((data[lst.front()]).find(lst.back()) != data[lst.front()].end()){
                // calculate the total amount in order to calculate the happen possibility
                int total = 0;
                std::map<std::string, int>::const_iterator m_itr = ((data[lst.front()])[lst.back()]).begin();
                // O(log m * log p * p)
                for(; m_itr != ((data[lst.front()])[lst.back()]).end(); ++ m_itr){
                    total += m_itr -> second;
                }
                // reset back to the begining
                m_itr = ((data[lst.front()])[lst.back()]).begin();
                // found the selected word
                std::string selected = m_itr -> first;
                // found out the words happen rate
                int totalCount = 0;
                // O(log m * log p * log p * p)
                for(; m_itr != ((data[lst.front()])[lst.back()]).end(); ++ m_itr){
                    // if the words is in this possibility print out 
                    if(possibility > double(totalCount)/total 
                            && possibility <= double((totalCount + (m_itr -> second)))/total){
                        selected = m_itr -> first;
                    }
                    totalCount += m_itr -> second;
                }
                std::cout << selected << " ";
                // pop_front of the list and push_back the last word to make sure there are two elements in the list
                lst.pop_front();
                lst.push_back(selected);
            }
        }
        // recusion
        times --;
        if(times > 0){
            generateNextWord(data, lst, times, random_flag);
        }
    }
}

// print out the words in random
void generateNext(MY_MAP &data, std::string word, int times, int total){
    // random number creator
    MTRand mtrand;
    // create random possibility
    double possibility = mtrand.randExc();
    // if can find the word
    if(data.find(word) != data.end()){
        // O(log m)
        std::map<std::string, int>::const_iterator m_itr = (data.find(word) -> second).begin();
        std::string selected = m_itr -> first;
        int count = 0;
        // O(log m * p)
        for(; m_itr != (data.find(word) -> second).end(); ++ m_itr){
            // if the words is in this possibility print out 
            if(possibility > double(count)/total 
                    && possibility <= double((count + (m_itr -> second)))/total){
                selected = m_itr -> first;
            }
            count += m_itr -> second;
        }

        std::cout << selected << " ";

        // recusion "times" times
        times --;
        if(times > 0){
            // print out next words in random
            generateNext(data, selected, times, total);
        }
    }
}

int main () {

    // ASSIGNMENT: THE MAIN DATA STRUCTURE
    MY_MAP data;

    std::map<std::string, MY_MAP> data3;
    // Parse each command
    std::string command;    
    int window;
    std::string last;
    std::string last2;
    while (std::cin >> command) {

        // load the sample text file
        if (command == "load") {
            std::string filename;
            std::string parse_method;
            std::cin >> filename >> window >> parse_method;      

            //
            // ASSIGNMENT: ADD YOUR COMMANDS HERE
            //

            if(window == 2){
                // load the text information into the data
                LoadSampleText(data, filename, window, parse_method, last);
            }
            if(window == 3){
                // load the text information into the data
                LoadSampleText(data3, filename, window, parse_method, last, last2);
            }
            //std::cout << data.size() << std::endl;
            std::cout << "Loaded " << filename << " with window = " << window 
                << " and parse method = " << parse_method << std::endl << std::endl;
        } 

        // print the portion of the map structure with the choices for the
        // next word given a particular sequence.
        else if (command == "print") {
            std::vector<std::string> sentence = ReadQuotedWords(std::cin);

            //
            // ASSIGNMENT: ADD YOUR COMMANDS HERE
            //
            if(window == 2){
                // Noticify if can't find the word
                // O(log m)
                if(data.find(sentence[0]) == data.end()){
                    std::cout << "Can't find " << sentence[0] << std::endl;
                }
                else{
                    // calculate the total amount in order to calculate the happen possibility
                    int total = 0;
                    std::map<std::string, int>::const_iterator m_itr = (data.find(sentence[0]) -> second).begin();
                    // O(log m * p)
                    for(; m_itr != (data.find(sentence[0]) -> second).end(); ++ m_itr){
                        total += m_itr -> second;
                    }
                    // when this word is the last word in the passage, the number will increase one 
                    if(sentence[0] == last){
                        std::cout << sentence[0] << " (" << total + 1 << ")" << std::endl;
                    }
                    else{
                        std::cout << sentence[0] << " (" << total << ")" << std::endl;
                    }
                    // reset back to the begin
                    m_itr = (data.find(sentence[0]) -> second).begin();
                    // print the words
                    for(; m_itr != (data.find(sentence[0]) -> second).end(); ++ m_itr){
                        std::cout << sentence[0] << " " << m_itr -> first << " (" 
                            << m_itr -> second << ")" << std::endl;
                    }
                }
            }

            if(window == 3){
                // Noticify if can't find the word
                if(data3.find(sentence[0]) == data3.end()){
                    std::cout << "Can't find " << sentence[0] <<  std::endl;
                }
                else{
                    // calculate the total amount in order to calculate the happen possibility
                    int total = 0;
                    // if there are two word in this sentence
                    if(sentence.size() == 2){
                        // Noticify if can't find the word
                        // O(log m * log p)
                        if(((data3.find(sentence[0])) -> second).find(sentence[1]) ==  
                                ((data3.find(sentence[0])) -> second).end()){
                            std::cout << "Can't find " << sentence[0] << " " << sentence[1] << std::endl;
                        }
                        else{
                            std::map<std::string, int>::const_iterator m_itr = 
                                ((data3[sentence[0]])[sentence[1]]).begin();
                            // O(log m * (log p)^(w - 2) * p)
                            for(; m_itr != ((data3[sentence[0]])[sentence[1]]).end(); ++ m_itr){
                                total += m_itr -> second;
                            }
                            // when this word is the last word in the passage, the number will increase one 
                            if(sentence[0] == last2 && sentence[1] == last){
                                std::cout << sentence[0] << " " << sentence[1] 
                                    << " (" << total + 1 << ")" << std::endl;
                            }
                            else{
                                std::cout << sentence[0] << " " << sentence[1] << " (" << total << ")" << std::endl;
                            }
                            // reset back to begining
                            m_itr = ((data3[sentence[0]])[sentence[1]]).begin();
                            // O(log m * (log p)^(w - 2) * p)
                            for(; m_itr != ((data3[sentence[0]])[sentence[1]]).end(); ++ m_itr){
                                std::cout << sentence[0] << " " << sentence[1] << " " << m_itr -> first << " (" 
                                    << m_itr -> second << ")" << std::endl;
                            }
                        }
                    }
                    // if there is only one word
                    else if(sentence.size() == 1){
                        // set to the beginning
                        std::map<std::string, std::map<std::string, int> >::const_iterator m_itr = 
                            (data3[sentence[0]]).begin();
                        // calculate the total amount in order to calculate the happen possibility
                        for(; m_itr != (data3[sentence[0]]).end(); ++ m_itr){
                            std::map<std::string, int>::const_iterator n_itr = (m_itr -> second).begin();
                            for(; n_itr != (m_itr -> second).end(); ++ n_itr){
                                total += n_itr -> second;
                            }
                        }
                        // when this word is the last word in the passage, the number will increase one 
                        if(sentence[0] == last || sentence[0] == last2){
                            std::cout << sentence[0] << " (" << total + 1 << ")" << std::endl;
                        }
                        else{
                            std::cout << sentence[0] << " (" << total << ")" << std::endl;
                        }
                        // reset back to begining
                        m_itr = (data3[sentence[0]]).begin();
                        // print the words
                        for(; m_itr != (data3[sentence[0]]).end(); ++ m_itr){
                            int count = 0;
                            std::map<std::string, int>::const_iterator n_itr = (m_itr -> second).begin();
                            for(; n_itr != (m_itr -> second).end(); ++ n_itr){
                                count += n_itr -> second;
                            }
                            std::cout << sentence[0] << " " << m_itr -> first << " (" 
                                << count << ")" << std::endl;
                        }
                    }
                }
            }
            std::cout << std::endl;
        }

        // generate the specified number of words 
        else if (command == "generate") {
            std::vector<std::string> sentence = ReadQuotedWords(std::cin);
            // how many additional words to generate
            int length;
            std::cin >> length;
            std::string selection_method;
            std::cin >> selection_method;
            bool random_flag;
            if (selection_method == "random") {
                random_flag = true;
            } else {
                assert (selection_method == "most_common");
                random_flag = false;
            }

            if(window == 2){
                // when it's not random
                if(!random_flag){
                    std::cout << sentence[0] << " ";
                    // print out the words
                    generateNext(data, sentence[0], length);
                    std::cout << std::endl;
                    std::cout << std::endl;
                }
                // when it's random
                else{
                    // calculate the total amount in order to calculate the happen possibility
                    int total = 0;
                    std::map<std::string, int>::const_iterator m_itr = (data.find(sentence[0]) -> second).begin();
                    for(; m_itr != (data.find(sentence[0]) -> second).end(); ++ m_itr){
                        total += m_itr -> second;
                    }
                    std::cout << sentence[0] << " ";
                    // print out the words
                    generateNext(data, sentence[0], length, total);
                    std::cout << std::endl;
                    std::cout << std::endl;
                }
            }
            else if(window == 3){
                std::list<std::string> lst;
                // if there is only one word in this sentence
                if(sentence.size() == 1){
                    lst.push_back(sentence[0]);
                    std::cout << sentence[0] << " ";
                }
                // if there are two words in this sentence
                else{
                    lst.push_back(sentence[0]);
                    lst.push_back(sentence[1]);
                    std::cout << sentence[0] << " ";
                    std::cout << sentence[1] << " ";
                }
                // print out the words
                generateNextWord(data3, lst, length, random_flag);
                std::cout << std::endl;
                std::cout << std::endl;

            }

            //
            // ASSIGNMENT: ADD YOUR COMMANDS HERE
            //


        } else if (command == "quit") {
            break;
        } else {
            std::cout << "WARNING: Unknown command: " << command << std::endl;
        }
    }
}
