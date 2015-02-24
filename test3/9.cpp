void swivel_left(Node * & root){
    if(root -> left == NULL){
        return 0;
    }
    else {
        if(root -> left -> right != NULL){
            Node * tmp = root -> left;
            root -> left = tmp -> right;
            tmp -> right -> parent = root;
            tmp -> right = root;
            if(root -> parent != NULL){
                tmp -> parent = root -> parent; 
            }
            else{
                head = tmp;
                tmp -> parent = NULL;
            }
            root -> parent = tmp;
        }
        else{
            Node * tmp = root -> left;
            tmp -> right = root;
            root -> left = NULL;
            if(root -> parent != NULL){
                tmp -> parent = root -> parent; 
            }
            else{
                head = tmp;
                tmp -> parent = NULL;
            }
            root -> parent = tmp;
        }
    }
}


void flatten(Node * & root){
    if(root -> left != NULL){
        swivel_left(root);
        flatten(root -> left);
        flatten(root -> right);
    }
}






template <class T>
void left_swivel(Node<T>* &input) {
    assert (input != NULL && input->left != NULL);
    Node<T> *orig = input;
    Node<T> *repl = input->left;
    Node<T> *parent = input->parent;
    Node<T> *mid = input->left->right;
    input = repl;
    repl->parent = parent;
    orig->parent = repl;
    repl->right = orig;
    orig->left = mid;
    if (mid != NULL) mid->parent = orig;
}

template <class T>
void flatten(Node<T>* &n) {
    if (n == NULL) return;
    while (n->left != NULL) { left_swivel(n); }
    flatten(n->right);
}



Solution: The STL map structure stores the data sorted by key. In contrast, data in a hash table appears to be randomly ordered (it is ordered by the hash function evaluated for each element). These orderings are important when we compare iteration over these structures. The map is guaranteed to iterator over the data in sorted order. If having the data sorted is necessary for the application, the map is probably the better data structure choice.
