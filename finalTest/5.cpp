template <class T> void dslist<T>::reverse(){
    T t1 = head;
    T t2 = t1 -> next;
    T t3 = t2 -> next;
    T t2 -> next = t1;
    t1 -> next = NULL;
    tail = t1;
    t1 = t2;
    t2 = t3;
    t3 = t3 -> next;
    while(t3 != NULL){
        t2 -> next = t1;
        t1 = t2;
        t2 = t3;
        t3 = t3 -> next;
    }
    t2 -> next = t1;
    head = t2;
}


//consider more about 
/*
Node<T>* Sublist(Node<T>* head, int low, int high){
    Node<T> * tmp = head;
    for(int i = 0; i < low; ++ i){
        tmp = tmp -> next;
    }
    Node<T> * nhead = new Node<T>;
    Node<T> * nTmp = new Node<T>;
    Node<T> * nTmp2 = new Node<T>;
    for(int i = low; i < high; ++ i){
        if(i = low){
            nhead -> value = tmp -> value;
            nhead -> next = nTmp;
            tmp = tmp -> next;
        }
        else{
            nTmp = tmp -> value;
            nTmp -> next = nTmp2;
            nTmp = new Node<T>;
        }
    }
}
*/

Node<T> * Sublist(Node<T>* head, int low, int high){
    Node<T> * tmp = head;
    int i = 0;
    for(; i < low; ++ i){
        tmp = tmp -> next;
    }
    Node<T> * nhead = new Node<T>;
    nhead -> value = tmp -> value;
    Node<T> * last = nhead;
    tmp = tmp ->next;
    for(; i < high; ++ i, tmp = tmp -> next){
        last -> next = new Node<T>;
        last = last -> next;
        last -> value = tmp -> value;
    }
    last -> next = NULL;
}




template <class T>
void cs2list<T>::splice(iterator itr, cs2list<T>& second) {
    if (second.empty()) return;
    second.head_->prev_ = itr.ptr_;
    second.tail_->next_ = itr.ptr_->next_;
    if (itr.ptr_->next_) {
        itr.ptr_->next_->prev_ = second.tail_;
    } else { // itr.ptr_ is the tail, so it must be reset
        this->tail_ = second.tail_;
    }
    itr.ptr_->next_ = second.head_;
    this->size_ += second.size_;
    second .size_ = 0;
    second.head_ = second.tail_ = 0;
}
