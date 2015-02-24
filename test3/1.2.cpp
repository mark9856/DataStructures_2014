typedef std::map<std::string, std::map<std::string, int> > history

while{
    ++history[name][costume];
    int total = 0;
    for(std::map<std::string, int>::const_iterator itr = history[name].begin(); itr != history[name].end(); ++ itr){
        total += itr -> second;
    }
    for(std::map<std::string, int>::const_iterator itr = history[name].begin(); itr != history[name].end(); ++ itr){
        std::cout << name << " has been to the shop " << total << " time(s) and rented a " 
            << itr -> first << itr -> second << "time(s)" << std::endl;
    }
}

O(npck)

O(n(logp + logv))



typedef std::map<std::string, std::pair<int std::map<std::string, int> > > history;

history::iterator itr = data.find(name);
if(itr == data.end()){
    std::map<std::string, int> tmp;
    tmp[costume] = 1;
    data.insert(std::make_pair(name, std::make_pair(1, tmp)));
}
else{
    (itr -> second).first ++;
    (itr -> second).second[costume] ++;
}
std::cout << name << " has been to the shop " << data[name].first << " time(s) and rented a " 
<< costume << " costume " << data[name].second[costume] << " time(s)." << std::endl;

