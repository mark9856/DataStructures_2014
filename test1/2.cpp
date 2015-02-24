#include <iostream>
#include <vector>

int replace_in_matrix(std::vector <std::vector <int> > & matrix, int old_value, int new_value){
    int total = 0;
    for(int i = 0; i < matrix.size(); ++ i){
        for(int j = 0; j < matrix[i].size(); ++ j){
            if(matrix[i][j] == 3){
                matrix[i][j] = 9;
                total ++;
            }
        }
    }
    return total;

}

void output(std::vector <std::vector <int> > & matrix){
    for (int i = 0; i < matrix.size(); ++ i){
        for (int j = 0; j < matrix[i].size(); ++ j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(){
    std::vector <std::vector <int> > matrix;
    int old_value = 3;
    int new_value = 9;
    std::vector <int> line1;
    line1.push_back(3);
    line1.push_back(4);
    line1.push_back(5);
    line1.push_back(9);
    line1.push_back(7);
    matrix.push_back(line1);
    std::vector <int> line2;
    line2.push_back(2);
    line2.push_back(6);
    line2.push_back(3);
    line2.push_back(3);
    line2.push_back(1);
    matrix.push_back(line2);
    /*
    matrix.push_back({3,4,5,9,7});
    matrix.push_back({2,6,3,3,1});
    matrix.push_back({4,7,3,8,3});

    */
    int total = replace_in_matrix(matrix, old_value, new_value);
    std::cout << total << std::endl;
    output(matrix);
    return 0;
}
