std::string majority(std::vector<std::map<std::string, std::string> > & voters, const std::string & category){
    std::map<std::string, int> collection;
    for(int i = 0; i < voters.size(); ++ i){
        ++ collection[voters[i][category]];
    }
    std::map<std::string, int>::const_iterator itr = collection.begin();
    for(; itr != collection.end(); ++ itr){
        if(itr -> second > voters.size()/2){
            return itr -> first;
        }
    }
    return "(no consensus)";
}

O(vlogk + k);


std::string majority(const std::vector<std::map<std::string,std::string> > &voters,
        const std::string &category) {
    // determine how many votes are necessary to 'win'
    int num_voters = voters.size();
    assert (num_voters > 0);
    int majority = (int)ceil((num_voters+1)/2.0);
    // a structure to store the total count for each vote
    std::map<std::string,int> votes;
    for (int i = 0; i < num_voters; i++) {
        std::map<std::string,std::string>::const_iterator itr = voters[i].find(category);
        if (itr != voters[i].end()) {
            votes[itr->second]++;
        }
    }
    // go through the votes and find the max/majority
    for (std::map<std::string,int>::const_iterator itr2 = votes.begin(); itr2 != votes.end(); itr2++) {
        if (itr2->second >= majority)
            return itr2->first;
    }
    // if insufficient votes for the majority
    return "(no consensus)";
}
