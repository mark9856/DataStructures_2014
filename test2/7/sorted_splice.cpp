Node * sorted_splice(Node * & a, Node * & b){
    if(a == NULL) return b;
    if(b == NULL) return a;
    Node * c = new Node;
    if(a -> value < b -> value){
        c = a;
        while(a -> ptr != NULL && b -> ptr != NULL){
            a = a -> ptr;
            if(a -> value < b -> value && a -> ptr -> value > b -> value){
                Node * tmp = a -> ptr;
                a -> ptr = b;
                while(b -> ptr != NULL){
                    b = b -> ptr;
                }
                b -> ptr = tmp;
                break;
            }
        }
        else if(a -> ptr == NULL){
            a -> ptr = b;
        }
    }
    else{ 
        c = b;
        while(b -> ptr != NULL){
            b = b -> ptr;
        }
        b -> ptr = a;
    }
    return c;
}


O(m + n)
