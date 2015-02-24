void even_array(const list<int> & b, int* & a, int & n){
    int size = 0;
    for(const list<int>::iterator itr = b.begin(); itr != b.end(); ++ itr){
        if(*itr > 0 && *itr % 2 == 0){
            size++;
        }
    }
    int* t = new int[size];
    for(const list<int>::iterator itr = b.begin(); itr != b.end(); ++ itr){
        if(*itr > 0 && *itr % 2 == 0){  
            *t = *itr;
            ++ t;
        }
    }
}
