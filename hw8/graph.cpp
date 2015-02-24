#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <cstdio>
#include "graph.h"
#include "MersenneTwister.h"
#include "person.h"
#include "message.h"
#include <algorithm>



// CONSTRUCTOR 
Graph::Graph(){
}

// DESTRUCTOR
Graph::~Graph(){
    for(std::vector<Message*>::iterator itr = m_messages.begin(); itr != m_messages.end(); ++ itr){
        delete *itr;
    }
    for(std::vector<Person*>::iterator itr = m_people.begin(); itr != m_people.end(); ++ itr){
        delete *itr;
    }
}


// Find the person
Person* Graph::find_person(const std::string &name) const{
    for(std::vector<Person*>::const_iterator p = m_people.begin(); p != m_people.end(); ++ p){
        if((*p) -> get_name() == name){
            return *p;
        }
    }
    return NULL;
}


// Add a new person 
bool Graph::add_person(const std::string& person_name){
    bool found = false;
    // Whether find the person
    for (std::vector<Person*>::iterator p = m_people.begin(); p != m_people.end(); ++p){
        if((*p) -> get_name() == person_name){
            found = true;
        }
    }
    if(found){
        //std::cerr << "There is already existing people with the same name." << std::endl;
        return false;
    }
    else{
        // Create and push_back a new Person
        Person *person = new Person(person_name);
        m_people.push_back(person);
        return true;
    }
}


// Remove person from Graph
bool Graph::remove_person(const std::string& person_name){
    bool found = false;
    // Can found the person
    for(std::vector<Person*>::iterator p = m_people.begin(); p != m_people.end(); ++ p){
        if((*p) -> get_name() == person_name)
            found = true;
    }
    if(!found){
        //std::cerr << "Can't find the person with this name." << std::endl;
        return false;
    }
    else{
        // Remove from all the Persons' name list
        for(std::vector<Person*>::iterator p = m_people.begin(); p != m_people.end(); ++ p){
            (*p) -> remove_friend(find_person(person_name));
        }
        for(int i = 0; i < m_people.size(); ++ i){
            if(m_people[i] -> get_name() == person_name){
                // Delete the Message hold by this person
                std::list<Message*> messagesDeleted = m_people[i] -> get_messages();
                for(std::list<Message*>::iterator l_itr = messagesDeleted.begin(); 
                        l_itr != messagesDeleted.end(); ++ l_itr){
                    delete *l_itr;
                }
                // Delete this person
                delete m_people[i];
                // Reorganize the vector of person
                for(; i < m_people.size() - 1; ++ i){
                    m_people[i] = m_people[i + 1];
                }
                // pop_back the last one people in the end of the vector
                m_people.pop_back();
                return true;
            }
        }
        return false;
    }
}

// add friendship between people 
bool Graph::add_friendship(const std::string& person_name1, const std::string& person_name2){
    // find the person1
    if(find_person(person_name1) != NULL){
        // find the person2
        if(find_person(person_name2) != NULL){
            if(person_name1 != person_name2){
                // return false if there is already a friendship between them
                if(find_person(person_name1) -> is_friend(find_person(person_name2))){
                    //std::cerr << "There is already existing this friendship" << std::endl;
                    return false;
                }
                else{
                    // add friendship between people 
                    (find_person(person_name1)) -> add_friend(find_person(person_name2));
                    return true;
                }
            }
            else{ 
                //std::cerr << "Can't add the friendship with the same person" << std::endl;
                return false;
            }
        }
        else {
            //std::cerr << "There is not existing person named " << person_name2 << std::endl;
            return false;
        }
    }
    else {
        //std::cerr << "There is not existing person named " << person_name1 << std::endl;
        return false;
    }
}

// remove_friendship
bool Graph::remove_friendship(const std::string& person_name1, const std::string& person_name2){
    // make sure exist person_name1
    if(find_person(person_name1) != NULL){
        // make sure exist person_name2
        if(find_person(person_name2) != NULL){
            // make sure is friend
            if(person_name1 != person_name2){
                if(find_person(person_name1) -> is_friend(find_person(person_name2))){
                    find_person(person_name1) -> remove_friend(find_person(person_name2));
                    return true;
                }
                else {
                    //std::cerr << "There is not existing this friendship" << std::endl;
                    return false;
                }
            }
            else{
                //std::cerr << "Can't remove friendship with the same person" << std::endl;
                return false;
            }
        }
        else{
            //std::cerr << "There is not existing person named " << person_name2 << std::endl;
            return false;
        }
    }
    else{
        //std::cerr << "There is not existing person named " << person_name1 << std::endl;
        return false;
    }
}

// add message to the person
bool Graph::add_message(const std::string& person_name, const std::string& message){
    // make sure person exist
    if(find_person(person_name) != NULL){
        Message * newMessage = new Message(message, find_person(person_name));
        // add message to the person
        if(find_person(person_name) -> add_message(newMessage)){
            m_messages.push_back(newMessage);
            return true;
        }
        else return false;
    }
    else return false;
}

// print all the information
void Graph::print(std::ostream &ostr) const{
    std::vector<Person*> sortedPeople = m_people;
    // sort all the person
    std::sort(sortedPeople.begin(), sortedPeople.end(), friend_sorter);
    std::cout << std::endl;

    for(std::vector<Person*>::iterator v_itr = sortedPeople.begin(); v_itr != sortedPeople.end(); ++ v_itr){
        std::cout << (*v_itr) -> get_name() << std::endl;
        std::cout << "  friends: ";

        std::list<Person*> sortedFriends = (*v_itr) -> get_friends();
        // sort all the friend
        sortedFriends.sort(friend_sorter);
        for(std::list<Person*>::iterator l_itr = sortedFriends.begin(); l_itr != sortedFriends.end(); ++ l_itr){
            std::cout << (*l_itr) -> get_name() << " ";
        }
        std::cout << std::endl;
        std::cout << "  messages: ";
        std::list<Message*> sortedMessages = (*v_itr) -> get_messages();
        // sort all the messages
        sortedMessages.sort(message_sorter);
        // print all the Messages
        for(std::list<Message*>::iterator m_itr = sortedMessages.begin(); m_itr != sortedMessages.end(); ++ m_itr){
            std::cout << (*m_itr) -> get_message() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// print invite_list
bool Graph::print_invite_list(std::ostream &ostr, const std::string &name, int n) const{
    std::cout << "Invite list of " << name << n << ": "; 
    std::list<Person*> invite_list;
    // recision function to get invite_list
    add_list(name, n, invite_list);

    // sort all the invite_list
    invite_list.sort(friend_sorter);
    // print all the invite_list
    for(std::list<Person*>::iterator l_itr = invite_list.begin(); l_itr != invite_list.end(); ++ l_itr){
        std::cout << (*l_itr) -> get_name() << " ";
    }
    std::cout << std::endl;
    return true;
}

// help function to add person to invite_list
void Graph::add_list(std::string name, int n, std::list<Person*> &invite_list) const{
    if(n != 0){
        n --;
        std::list<Person*> friend_list = find_person(name) -> get_friends();
        for(std::list<Person*>::iterator itr = friend_list.begin(); itr != friend_list.end(); ++ itr){
            bool found = false;
            // make the friend is not already in the invite_list
            for(std::list<Person*>::iterator i_itr = invite_list.begin(); i_itr != invite_list.end(); ++ i_itr){
                if((*itr) -> get_name() == (*i_itr) -> get_name()){
                    found = true;
                }
            }
            if(!found){
                invite_list.push_back(*itr);
            }
            add_list((*itr) -> get_name(), n, invite_list);
        }
    }
}
// pass_messages to next Person
void Graph::pass_messages(MTRand &mtrand){
    // for all the people
    for(int i = 0; i < m_people.size(); ++ i){
        std::list<Person*> friends = m_people[i] -> get_friends();
        std::list<Message*> messages = m_people[i] -> get_messages();
        // for all the Messages
        for(std::list<Message*>::iterator m_itr = messages.begin(); m_itr != messages.end(); ++ m_itr){
            // get random number
            int randInt = mtrand.randInt(friends.size());
            // if randInt is 0 keep unmoved
            if(randInt > 0){
                // move to Person selected
                for(std::list<Person*>::iterator f_itr = friends.begin(); f_itr != friends.end(); ++ f_itr){
                    randInt --;
                    if(randInt == 0){
                        if(!(*m_itr) -> move()){
                            // if what to achieve the function of whisper, just uncomment it
                            (*m_itr) -> changeWord();
                            (*m_itr) -> setMoved();
                            (*f_itr) -> add_message(*m_itr);
                            m_people[i] -> remove_message(*m_itr);
                            break;
                        }
                    }
                }
                break;
            }
            else break;
        }
    }
    for(std::vector<Message*>::iterator itr = m_messages.begin(); itr != m_messages.end(); ++ itr){
        (*itr) -> setMovedBack();
    }
}
