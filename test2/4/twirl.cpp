void twirl(Node * head, int find){
    Node * tmp = head;
    while(tmp -> next != NULL){
        if(tmp -> value == find){
            tmp -> prev -> prev -> next = tmp -> next;
            tmp -> next -> next = tmp -> prev -> prev;
            tmp -> prev -> next = tmp -> next -> next;
            tmp -> next -> next -> prev = tmp -> prev;
            tmp -> next -> prev = tmp -> prev;
            tmp -> prev -> prev = tmp -> next;
            delete tmp;
        }
        tmp = tmp -> next;
    }
}
