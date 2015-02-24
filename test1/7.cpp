#include <iostream>
#include <vector>

bool square_matrix_all_numbers(std::vector <std::vector <int> > & matrix){
    for(int i = 0; i < matrix.size(); ++ i){
        if(matrix[i].size() != matrix.size()){
            return false;
        }
    }
    int n = matrix.size() * matrix.size();
    for(int k = 1; k < n + 1; ++ k){
        bool found = false;
        for(int i = 0; i < matrix.size(); ++ i){
            for(int j = 0; j < matrix[i].size(); ++ j){
                if(matrix[i][j] == k){
                    found = true;
                }
            }
        }
        if(found == false){
            return false;
        }
        std::cout << "found = " << found << std::endl;
    }
    return true;
}

int main(){
    std::vector <std::vector <int> > matrix;
    int a[] = {1,4,5};
    int b[] = {6,2,9};
    int c[] = {7,8,3};
    std::vector <int> line1(a, a + 3);
    std::vector <int> line2(b, b + 3);
    std::vector <int> line3(c, c + 3);
    matrix.push_back(line1);
    matrix.push_back(line2);
    matrix.push_back(line3);
    //bool try1 = true;
    //std::cout << "try = " << try1 << std::endl;
    std::cout << square_matrix_all_numbers(matrix) << std::endl;

    return 0;
}
