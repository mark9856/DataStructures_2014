#ifndef Table_h_
#define Table_h_

#include <iostream>
#include <vector>

template <class T> class Table{

    public:
        // TYPEDEFS
        typedef unsigned int size_type;

        // CONSTRUCTORS
        Table() {this->create();}
        Table(size_type r, size_type c, const T & val);
        Table(const Table & t) {copy(t);}
        Table & operator= (const Table & t);
        ~Table();

        // MEMBER FUNCTIONS AND OTHER FUNCTIONS
        T& get(size_type r, size_type c) const;
        void set(size_type r, size_type c, T value);
        const size_type numRows() const{return rows;}
        const size_type numColumns() const{return cols;}
        void push_back_row(std::vector <T> & new_row);
        void pop_back_row();
        void push_back_column(std::vector <T> & new_col);
        void pop_back_column();
        void print() const;
        void push_back_rows(const Table & t);
        void push_back_columns(const Table & t);
        
    private:
        // PRIVATE MEMBER FUNCTIONS
        void create();
        void create(size_type r, size_type c, const T& val);
        void copy(const Table<T> & t);

        // REPRESENTATION
        size_type rows;
        size_type cols;

        T** data;
};

// create an empty table
template <class T> void Table<T>::create(){
    data = NULL;
    rows = 0;
    cols = 0;
}

// create a table with r rows and c columns and make each element has the value of val
template <class T> void Table<T>::create(size_type r, size_type c, const T & val){
    // create a new table and assign space for it
    data = new T*[r];
    for(size_type i = 0; i < r; ++ i){
        data[i] = new T[c];
    }
    this->rows = r;
    this->cols = c;
    // copy the value to each element
    for(size_type i = 0; i < rows; ++ i){
        for (size_type j = 0; j < cols; ++ j){
            data[i][j] = val;
        }
    }
}

// assign one table to a table, and avoid duplicate
template <class T> Table<T>& Table<T>::operator= (const Table & t){
    // if the value of the existing table is not the same with other table
    if (this != &t){
        // delete the space of the existing table
        for(size_type i = 0; i < rows; ++ i){
            delete [] data[i];
        }
        delete [] data;
        // copy the value into the table
        this -> copy(t);
    }
    return *this;
}

// create a table as a copy of the given table
template <class T> void Table<T>::copy(const Table<T> & t){
    this -> rows = t.rows;
    this -> cols = t.cols;
    // create new space for a new table
    this -> data = new T*[this -> rows];
    for (size_type i = 0; i < this -> rows; ++ i){
        data[i] = new T[this -> cols];
    }

    // copy the value of a table into the table 
    for(size_type i = 0; i < this -> rows; ++ i){
        for (size_type j = 0; j < this -> cols; ++ j){
            this -> data[i][j] = t.data[i][j];
        }
    }
}

// Create a table with size n, each location having the given value
template <class T> Table<T>::Table(size_type r, size_type c, const T & val){
    this->create(r, c, val);
}

// Disconstructor function of table 
template <class T> Table<T>::~Table(){
    // delete all the space of the table
    for (size_type i = 0; i < rows; ++ i){
        delete [] data[i]; 
    }
    delete [] data;
}

// get the value of the location in the r row, and c column
template <class T> T& Table<T>::get(size_type r, size_type c) const{
    if(r <= rows && c <= cols){
        return data[r][c];
    }
    // record the error information when the r is bigger than rows 
    else if(r > rows){
        std::cerr << "Wrong row index!";
        exit(1);
    }
    // record the error information when the c is bigger than columns
    else if(c > cols){
        std::cerr << "Please type in correct column";
        exit(1);
    }
    exit(1);
}

// set the the value of the location in the r row and c column to be other value
template <class T> void Table<T>::set(size_type r, size_type c, T value){
    if(r <= rows && c <= cols){
        data[r][c] = value;
    }
    // record the error information when the r is bigger than rows 
    else if(r > rows){
        std::cerr << "Wrong row index!";
        exit(1);
    }
    // record the error information when the c is bigger than columns
    else if(c > cols){
        std::cerr << "Please type in correct column";
        exit(1);
    }
}

// push back a row with the value in a vector into the table 
template <class T> void Table<T>::push_back_row(std::vector <T> & new_row){
    // record the error information when the length of new data 
    // is not the same with the columns of the table
    if(new_row.size() != this -> cols && this -> cols != 0){
        std::cerr << "Please push back a correct length of vector";
        exit(1);
    }
    // create a table with (rows + 1) rows
    // O(n)
    T** new_data = new T*[rows + 1];
    // allocate space for this new table
    // O(n)
    for(size_type i = 0; i < rows + 1; ++ i){
        // O(m)
        new_data[i] = new T[cols];
    }
    // copy the value of the new table into this table
    // O(n)
    for(size_type i = 0; i < rows; ++ i){
        // O(m)
        for(size_type j = 0; j < cols; ++ j){
            new_data[i][j] = data[i][j];
        }
        delete [] data[i];
    }
    delete [] data;
    // assign the new table to the table
    data = new_data;

    // assign the value of the vector to the last row of the table
    for(size_type j = 0; j < cols; ++ j){
        data[rows][j] = new_row[j];
    }
    ++ rows;
}

// pop back the last row of value in the table
template <class T> void Table<T>::pop_back_row(){
    // record the error information when the table has no row
    if(rows == 0){
        std::cerr << "there is no row in this Table";
        exit(1);
    }
    else{
        // delete the last row
        delete [] data[rows - 1];
        // create a table with (rows - 1) rows
        // O(n)
        T** new_data = new T*[rows - 1];
        // O(n)
        for(size_type i = 0; i < rows - 1; ++ i){
            // O(m)
            new_data[i] = new T[cols];
            // assign the value of the original table into the new table
            // O(m)
            for(size_type j = 0; j < cols; ++ j){
                new_data[i][j] = data[i][j];
            }
            // delete the space of the table
            delete [] data[i];
        }
        delete [] data;
        // assign the new table to the existing table
        data = new_data;
        -- rows;
    }
}

// push back a vector of value into the table
template <class T> void Table<T>::push_back_column(std::vector <T> & new_col){
    // record the error information when the length of new data 
    // is not the same with the rows of the table
    if(new_col.size() != this -> rows && this -> rows != 0){
        std::cerr << "Please push back a correct length of vector";
        exit(1);
    }
    // create a new table
    // O(n)
    T** new_data = new T*[rows];
    // O(n)
    for(size_type i = 0; i < rows; ++ i){
        // assign (cols + 1) column to the new table
        // O(m)
        new_data[i] = new T[cols + 1];
        // copy the value of the original data to the new table
        // O(m)
        for(size_type j = 0; j < cols; ++ j){
            new_data[i][j] = data[i][j];
        }
        // copy the value of the vector to the last column of the table
        new_data[i][cols] = new_col[i];
        delete [] data[i];
    }
    delete [] data;
    // assign the value of new table to the table
    data = new_data;
    ++ cols;
}

// pop back the last column of value in the table 
template <class T> void Table<T>::pop_back_column(){
    // assign space to a new table
    // O(n)
    T** new_data = new T*[rows];
    // O(n)
    for(size_type i = 0; i < rows; ++ i){
        // assign only (cols - 1) columns of space to the table
        // O(m)
        new_data[i] = new T[cols - 1];
        // assign the value to the table
        // O(m)
        for(size_type j = 0; j < cols - 1; ++ j){
            new_data[i][j] = data[i][j];
        }
        delete [] data[i];
    }
    delete [] data;
    // assign the value of new table to the table
    data = new_data;
    -- cols;
}

// print out all the values in the table
template <class T> void Table<T>::print() const{
    std::cout << "table: " << this -> rows << " rows, " << this -> cols << " cols" << std::endl;
    // O(n)
    for(size_type i = 0; i < rows; ++ i){
        // O(m)
        for(size_type j = 0; j < cols; ++ j){
            std::cout << this -> data[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// push back a table of values as new rows into the table
template <class T> void Table<T>::push_back_rows(const Table & t){
    if(t.numColumns() != this -> cols && this -> cols != 0){
        std::cerr << "Please push back a correct length of table";
        exit(1);
    }
    size_type new_rows = this -> rows + t.rows;
    // create a new table with the combination of rows of original and new tables
    // O(n1 + n2)
    T** new_data = new T*[new_rows];
    // O(n1 + n2)
    for(size_type i = 0; i < new_rows; ++ i){
        // O(m)
        new_data[i] = new T[this -> cols];
    }
    // assign the original table as the first part of the table
    // O(n1)
    for(size_type i = 0; i < this -> rows; ++ i){
        // O(m)
        for(size_type j = 0; j < this -> cols; ++ j){
             new_data[i][j] = this -> data[i][j];
        }
        delete [] this -> data[i];
    }
    delete [] this -> data;
    // assign the second table as the second part of the table
    // O(n2)
    for(size_type i = this -> rows; i < new_rows; ++ i){
        // O(m)
        for(size_type j = 0; j < this -> cols; ++ j){
            new_data[i][j] = t.data[i - (this -> rows)][j];
        }
        // delete [] t.data[i - (this -> rows)];
    }
    // delete [] t.data;
    data = new_data;
    rows = new_rows;
}

// push back a table of values as new columns into the table
template <class T> void Table<T>::push_back_columns(const Table & t){
    if(t.numRows() != this -> rows && this -> rows != 0){
        std::cerr << "Please push back a correct length of table";
        exit(1);
    }
    size_type new_cols = this -> cols + t.cols;
    // O(n1)
    T** new_data = new T*[this -> rows];
    // O(n1)
    for(size_type i = 0; i < this -> rows; ++ i){
        // O(m1 + m2)
        new_data[i] = new T[new_cols];
    }
    // O(n1)
    for(size_type i = 0; i < this -> rows; ++ i){
        // O(m1)
        for(size_type j = 0; j < this -> cols; ++ j){
            new_data[i][j] = this -> data[i][j];
        }
        // O(m2)
        for(size_type k = 0; k < t.cols; ++ k){
            new_data[i][k + this -> cols] = t.data[i][k];
        }
        delete [] this -> data[i];
        // delete [] t.data[i];
    }
    delete [] this -> data;
    // delete [] t.data;
    data = new_data;
    cols = new_cols;
}
#endif
