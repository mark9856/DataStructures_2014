HOMEWORK 8: FRIENDLY RECURSION


NAME:  < insert name >
Huiyu Ma


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
Terry Liu

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >
10


NETWORK COMPLEXITY
Analysis of the maximum number of people at a party with chain
length n, if each person has at most k friends.

O(k^n)


YOUR NEW TEST CASES
Submitted as an input file named my_input.txt.  Briefly describe how
this test exercises the corner cases of your implementation.  Why is
this test case interesting and/or challenging?

the corner case included in this test case are:
1. add people with the same name existing in list;
2. remove people with no existing name;
3. add friendship with existing friendship, no existing person and the same person;
4. remove friendship with no existing person and not existing friendship

But in order to pass the test in server, I need to comment all these std::cerr. but it still works.


EXTRA CREDIT
Describe your (optional) implementation of the telephone game.

I have develop this extra credit part, if we don’t need this function, can just comment the changeWord() function in the pass_messages function in the Graph.cpp


MISC. COMMENTS TO GRADER:  
Optional, please be concise!






