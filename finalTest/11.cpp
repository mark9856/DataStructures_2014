default constructor destructor
copy constructor assignment operator


Office();
~Office();
Office(const Office &office);
Office& operator=(const Office &office);



~Office(){
    for(int i = 0; i < _num_desks; ++ i){
        if(_desks[i] != ""){
            _unassigned.push(_desks);
        }
    }
    delete _desks;
}


friend function

for non_member, couldn't get access to the private function and member variables
for member function, we need to create a object to use this function;

