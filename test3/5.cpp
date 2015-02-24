std::set<int> iSet;
while(std::cin >> n){
    iSet.insert(n);
}
std::set<int>::const_iterator itr = iSet.end();
while(itr != iSet.begin()){
    -- itr;
    std::cout << *itr << std::endl;
}

O(n)
    O(nlogn);



std::set<int> data;
int num;
// read in the data, store in a set
for (int i = 0; i < n; i++) {
    std::cin >> num;
    data.insert(num);
}
// output directly from the set (will be sorted!)
std::set<int>::iterator itr = data.end();
while (itr != data.begin()) {
    itr--;
    std::cout << *itr << " ";
}
std::cout << std::endl;
