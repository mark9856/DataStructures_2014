delete 3 -> 6
delete 6 -> 7
new 2 -> 6
new 5 -> 7


binarytree_to_linkedlist(DualNode<T> * &root, DualNode<T> * & head, DualNode<T> * & tail){
    head = root;
    transfer(root);

}

void transfer(DualNode<T> * & root){
    if(root -> leftprev != NULL){
        root -> rightnext = root -> leftprev;
        root -> leftprev = root;
        transfer(root -> leftprev);
    }
    else{
        root -> rightnext -> leftprev = root;
        transfer(root -> rightnext);
    }

    if(){
    }

}

template <class T>
void binarytree_to_linkedlist(DualNode<T> *root, DualNode<T>* &head, DualNode<T>* &tail) {
    // base case
    if (root == NULL) {
        head = tail = NULL;
        return; }
    // temporary variables
    DualNode<T>  *l_head, *l_tail, *r_head, *r_tail;
    // recursive calls
    binarytree_to_linkedlist(root->leftprev,l_head,l_tail);
    binarytree_to_linkedlist(root->rightnext,r_head,r_tail);
    // the root comes first in prefix traversal
    head = root;
    head->leftprev = NULL;
    // after that comes the left tree (if it exists)
    if (l_head == NULL) {
        l_tail = head;
    } else {
        head->rightnext = l_head;
        l_head->leftprev = head;
    }
    // then the right tree
    // make sure the tail is set appropriately!
    if (r_head == NULL) {
        tail = l_tail;
    } else {
        l_tail->rightnext = r_head;
        r_head->leftprev = l_tail;
        tail = r_tail;
    } 
}
