#include <list>
#include <string>
#include "person.h"
#include "message.h"

// whether or not a friend
bool Person::is_friend(Person* person) const{
    for(std::list<Person*>::const_iterator itr = m_friends.begin(); itr != m_friends.end(); ++ itr){
        if((*itr)  -> get_name() == person -> get_name()){
            return true;
        }
    }
    return false;
}

// add friend to the Person
bool Person::add_friend(Person *person){
    for(std::list<Person*>::iterator itr = m_friends.begin(); itr != m_friends.end(); ++ itr){
        if((*itr) -> get_name() == person -> get_name()){
            return false;
        }
    }
    m_friends.push_back(person);
    return true;
}

// remove_friend
bool Person::remove_friend(Person* person){
    for(std::list<Person*>::iterator itr = m_friends.begin(); itr != m_friends.end(); ++ itr){
        if((*itr) -> get_name() == person -> get_name()){
            itr = m_friends.erase(itr);
            return true;
        }
    }
    return false;
}

// add_message to this Person
bool Person::add_message(Message *message){
    for(std::list<Message*>::iterator itr = m_messages.begin(); itr != m_messages.end(); ++ itr){
        if((*itr) -> get_message() == message -> get_message()){
            return false;
        }
    }
    m_messages.push_back(message);
    return true;
}

// remove_message from this Person
bool Person::remove_message(Message *message){
    for(std::list<Message*>::iterator itr = m_messages.begin(); itr != m_messages.end(); ++ itr){
        if((*itr) -> get_message() == message -> get_message()){
            m_messages.erase(itr);
            return true;
        }
    }
    return false;
}
