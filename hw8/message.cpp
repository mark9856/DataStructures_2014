#include <string>
#include <vector>
#include "person.h"
#include "message.h"
#include "MersenneTwister.h"

// Constructor
Message::Message(const std::string &msg, Person *person){
    m_owner = person;
    m_message = msg;
    moved = false;
}

// The message is tranferred to the specified new owner.  The
// function returns false if the operation was not successfully
// completed.
bool Message::pass_message(Person *person){
    if(person -> get_name() == m_owner -> get_name()){
        return false;
    }
    else{
        m_owner = person;
        return true;
    }
}

// change the word sequence in the Message
void Message::changeWord(){
    MTRand mtrand1;
    MTRand mtrand2;
    std::vector<std::string> words;
    std::string word;
    // create a vector of string to storage the message
    for(int i = 0; i < m_message.size(); ++ i){
        if(m_message[i] == ' '){
            words.push_back(word);
            word.clear();
            continue;
        }
        if(m_message[i] == '\"'){
            continue;
        }
        word.push_back(m_message[i]);
    }
    words.push_back(word);
    word.clear();
    // randomly swap the place of two words and then place them back
    int randInt1 = mtrand1.randInt(words.size() - 1);
    int randInt2 = mtrand2.randInt(words.size() - 1);
    std::string swap;
    swap = words[randInt2];
    words[randInt2] = words[randInt1];
    words[randInt1] = swap;
    std::string sentence;
    sentence.push_back('\"');
    for(int i = 0; i < words.size() - 1; ++ i){
        for(int j = 0; j < words[i].size(); ++ j){
            sentence.push_back(words[i][j]);
        }
        sentence.push_back(' ');
    }
    for(int j = 0; j< words[words.size() - 1][j]; ++ j){
        sentence.push_back(words[words.size() - 1][j]);
    }
    sentence.push_back('\"');
    m_message.clear();
    m_message = sentence;
}

