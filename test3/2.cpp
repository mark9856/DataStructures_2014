make_symmetric(TriNode * &head){
    if(n == NULL) return;
    if(head -> right != NULL){
        destroyTree(head -> right);
    }
    if(head -> left != NULL){
        copyTree(head -> left, head -> right);
    }
    if(head -> middle != NULL){
        deleteMiddle(head -> middle);
    }
}

destroyTree(TriNode * &node){
    if(node -> left != NULL){
        destroyTree(node -> left);
    }
    if(node -> right != NULL){
        destroyTree(node -> right);
    }
    if(node -> middle != NULL){
        destroyTree(node -> middle);
    }
    delete node;
}

copyTree(TriNode * & leftNode, TriNode * &rightNode){
    if(leftNode -> left != NULL){
        TriNode * tmp = new TriNode((leftNode -> left).val);
        rightNode -> right = tmp;
        copyTree(leftNode -> left, rightNode -> right);
    }
    if(node -> right != NULL){
        TriNode * tmp = new TriNode((leftNode -> right).val);
        rightNode -> left = tmp;
        copyTree(leftNode -> right, rightNode -> left);
    }
    if(node -> middle != NULL){
        TriNode * tmp = new TriNode((node -> middle).val);
        rightNode -> middle = tmp;
        copyTree(leftNode -> middle, rightNode -> middle);
    }
}

deleteMiddle(TriNode * &middle){
    if(node -> right != NULL){
        destroyTree(node -> right);
    }
    if(node -> middle != NULL){
        deleteMiddle(node -> middle);
    }
}







// helper function to clean up unneccessary structure
void destroy(TriNode *n) {
    // base case
    if (n == NULL) return;
    // recursively delete the children
    destroy (n->left);
    destroy (n->middle);
    destroy (n->right);
    // then delete this node
    delete n;
}
// helper function
TriNode* copy_mirror(TriNode *n) {
    // base case
    if (n == NULL) return NULL;
    // create a new node on the heap
    TriNode *tmp = new TriNode(n->val);
    // copy, swapping left and right
    tmp->left = copy_mirror(n->right);
    tmp->middle = copy_mirror(n->middle);
    tmp->right = copy_mirror(n->left);
    return tmp;
}
// primary function
void make_symmetric(TriNode* n) {
    // base case
    if (n == NULL) return;
    // clobber existing structure on right side of tree
    destroy(n->right);
    // replace it with a mirror image copy
    n->right = copy_mirror(n->left);
    // recurse on the middle branch of the tree
    make_symmetric(n->middle);
}
