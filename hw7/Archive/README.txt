HOMEWORK 7: WORD FREQUENCY MAPS


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
15


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?

O(mp^(w - 1))

What is the order notation for performance (running time) of each of
the commands?

load: O(n(log m * (log p)^(w - 1)))

print:  O(log m * (log p)^(w - 2) * p)

generate most_common: O(log m * (log p)^(w - 2) * p)

generate random: O(log m * (log p)^(w - 2) * p)

quit: O(1)

EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


