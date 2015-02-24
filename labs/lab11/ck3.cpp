#include <iostream>
#include <cassert>


// the data structure
class Node {
    public:
        int value;
        Node *a;
        Node *b;
        Node *c;
        Node *parent;
};


// a very simple sideways tree visualization
void print(Node *n, const std::string &prefix) {
    if (n == NULL) return;
    if (n->a != NULL) assert (n->a->parent == n);
    if (n->b != NULL) assert (n->b->parent == n);
    if (n->c != NULL) assert (n->c->parent == n);
    print(n->c,prefix+" c ");
    print(n->b,prefix+" b ");
    std::cout << prefix << n->value << std::endl;
    print(n->a,prefix+" a ");
}


// cleanup the whole tree
void destroy(Node *n) {
    if (n == NULL) return;
    destroy (n->a);
    destroy (n->b);
    destroy (n->c);
    delete n;
}


// problem 2.1
bool insert(Node* &n, int value, Node* parent = NULL) {
    if(n == NULL){
        n = new Node;
        n -> value = value;
        return true;
    }
    else if(value < n -> value){
        if(n -> a == NULL){
            Node * newA = new Node;
            newA -> value = value;
            n -> a = newA;
            newA -> parent = n;
            return true;
        }
        else{
            insert(n -> a, value, n);
        }
    }
    else if(value > n -> value && value <= 2 * (n -> value)){
        if(n -> b == NULL){
            Node * newB = new Node;
            newB -> value = value;
            n -> b = newB;
            newB -> parent = n;
            return true;
        }
        else{
            insert(n -> b, value, n);
        }
    }
    else if(value > 2 * (n -> value)){
        if(n -> c == NULL){
            Node * newC = new Node;
            newC -> value = value;
            n -> c = newC;
            newC -> parent = n;
            return true;
        }
        else{
            insert(n -> c, value, n);
        }
    }
    return false;



}


// problem 2.2
Node* find_largest(Node *n) {
    if(n -> c != NULL){
        return find_largest(n -> c);
    }
    else if(n -> c == NULL && n -> b != NULL){
        return find_largest(n -> b);
    }
    else {
        return n;
    }
}


// problem 2.3
Node* find_previous(Node *n) {
    if(n -> parent == NULL){
        if(n -> a != NULL){
            return find_largest(n -> a);
        }
        else{
            return NULL;
        }
    }
    else{
        if(n -> parent -> c == n){
            if(n -> a != NULL){
                return find_largest(n -> a);
            }
            else{
                if(n -> parent -> b != NULL){
                    return find_largest(n -> parent -> b);
                }
                else{
                    return n -> parent;
                }
            }
        }
        else if(n -> parent -> b == n){
            if(n -> a != NULL){
                return find_largest(n -> a);
            }
            else{
                return n -> parent;
            }
        }
        else if(n -> parent -> a == n){
            if(n -> a != NULL){
                return find_largest(n -> a);
            }
            else{
                if(n -> parent -> parent != NULL){
                    if(n -> parent -> parent -> b != NULL && n -> parent -> parent -> b != n -> parent){
                        return find_largest(n -> parent -> parent -> b);
                    }
                    else if(n -> parent -> parent -> b == n -> parent){
                        return n -> parent -> parent;
                    }
                }
            }
        }
    }
    return NULL;



}



int main() {

    Node* root = NULL;

    // create the diagram on the test handout
    insert(root,30);
    insert(root,10);
    insert(root,32);
    insert(root,70);
    insert(root,5);
    insert(root,16);
    insert(root,24);
    insert(root,31);
    insert(root,52);
    insert(root,64);
    insert(root,92);
    insert(root,200);
    insert(root,12);
    insert(root,19);
    insert(root,45);
    insert(root,59);
    insert(root,150);
    insert(root,210);
    insert(root,450);
    insert(root,13);
    insert(root,4);
    insert(root,1);

    // print the tree before iteration
    print(root,"");
    std::cout << std::endl;
    std::cout << std::endl;

    // loop over the structure
    int count = 0;
    Node *tmp = find_largest(root);
    int prev = tmp->value;
    while (tmp != NULL) {
        std::cout << tmp->value << " ";
        tmp = find_previous(tmp);
        if (tmp != NULL) { 
            assert (prev > tmp->value);
            prev = tmp->value;
        }
        count++;
    }
    std::cout << std::endl;
    assert (count == 22);

    // cleanup so we have no memory leaks
    destroy (root);
}
