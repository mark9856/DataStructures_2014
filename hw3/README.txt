HOMEWORK 3: RESIZABLE TABLE


NAME:  < insert name >
Huiyu Ma


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
Geoffrey and Terry Liu

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >
20 hours



ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get
O(1)

set
O(1)

numRows
O(1)

numColumns
O(1)

push_back_row
O(mn)

push_back_column
O(mn)

pop_back_row
O(mn)

pop_back_column
O(mn)

print
O(mn)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?
I used the Valgrind for memory debugging. 


EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

I add the push_back_rows and push_back_columns to my codes

if the rows of table are n1 and n2, columns are m1 and m2

push_back_rows
O((n1 + n2) * m1)

push_back_columns
O((m1 + m2) * n1)




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

