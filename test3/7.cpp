int count_at_level(Node<T> head, int level){
    int total = 1;
    if(level == 0){
        return total;
    }
    while(level != 0){
        for(int i = 0; i < (head -> children).size(); ++ i){
            total += count_at_level((head -> children)[i], level - 1);
        }
    }
    return total;
}

5, 10, 6, 21, 2, 8, 3

top down, depth first, in order


template <class T>
int count_at_level(Node<T>* n, int level) {
    if (n == NULL) return 0;
    if (level == 0) return 1;
    int answer = 0;
    for (int i = 0; i < n->children.size(); i++) {
        answer += count_at_level(n->children[i],level-1);
    }
    return answer;
}
