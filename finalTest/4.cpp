void insert_in_order(double x, queue<double>& q){
    queue<double> p;
    for(int i = 0; i < q.size(); ++ i){
        if(q.front == x){
            p.push(x);
        }
        p.push(q.front);
        q.pop();
    }
    q = p;
}

void insert_in_order(double x, queue<double>& q){
    int i = 0;
    for(; i < q.size(); ++ i){
        if(q.front() > x){
            break;
        }
        else{
            q.push(q.front());
            q.pop();
        }
    }
    q.push(x);
    for(; i < q.size(); ++ i){
        q.push(q.front());
        q.pop();
    }
}
