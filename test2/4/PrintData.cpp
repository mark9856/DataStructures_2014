void PrintData(Node * head){
    if(head -> next != NULL){
        PrintData(head -> next);
        std::cout << head -> value << std::endl;
    }
    return;
}
