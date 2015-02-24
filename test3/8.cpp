Node * construct_balanced(std::vector<T> &v){
    Node * head = new Node(v[v.size/2]);
    constructTree(head, v);
    return head;
}

constructTree(Node * & head, std::vector<T> & v){
    if(v.size()/4 > 1){
        Node * tmp1 = new Node(v[v.size()/4]);
        head -> left = tmp1;
        head -> left -> parent = head;
        std::vector<T> v1;
        for(int i = 0; i < v.size()/2 - 1; ++ i){
            v1.push_back(v[i]);
        }
        constructTree(head -> left, v1);
        Node * tmp2 = new Node(v[3 * v.size()/4]);
        head -> right = tmp2;
        head -> right -> parent = head;
        std::vector<T> v2;
        for(int i = v.size()/2 + 1; i < v.size(); ++ i){
            v2.push_back(v[i]);
        }
        constructTree(head -> right, v2);
    }
}


template <class T>
Node<T>* construct_balanced(const std::vector<T> &v) {
    return construct_balanced(v,0,v.size());
}
template <class T>
Node<T>* construct_balanced(const std::vector<T> &v, int first, int last) {
    int size = last-first;
    if (size == 0) return NULL;
    // create a node for the middle element
    int middle = first+size/2;
    Node<T> *answer = new Node<T>(v[middle]);
    // recurse to the left and right
    answer->left = construct_balanced(v,first,middle);
    if (answer->left != NULL)
        answer->left->parent = answer;
    answer->right = construct_balanced(v,middle+1,last);
    if (answer->right != NULL)
        answer->right->parent = answer;
    // return the root
    return answer;
}
