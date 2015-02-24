// Compute the median value of an input set of grades.
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

void read_scores(std::vector<int> & scores, std::ifstream & grade_str) {
    int x;  // input variable
    while (grade_str >> x) {
        scores.push_back(x);
    }
}

void compute_avg_and_std_dev(const std::vector<int>& s, double & avg, double & std_dev) {
    // Compute and output the average value.
    int sum=0;
    for (unsigned int i = 0; i < s.size(); ++ i) {
        sum += s[i]; 
    }
    avg = double(sum) / s.size();
    // Compute the standard deviation
    double sum_sq = 0.0;
    for (unsigned int i=0; i < s.size(); ++i) {
        sum_sq += (s[i]-avg) * (s[i]-avg);
    }
    std_dev = sqrt(sum_sq / (s.size()-1));
}

double compute_median(const std::vector<int> & scores) {
    // Create a copy of the vector
    std::vector<int> scores_to_sort(scores);
    // Sort the values in the vector.  By default this is increasing order.
    std::sort(scores_to_sort.begin(), scores_to_sort.end());
    // Now, compute and output the median.
    unsigned int n = scores_to_sort.size();
    if (n%2 == 0)  // even number of scores
        return double(scores_to_sort[n/2] + scores_to_sort[n/2-1]) / 2.0;
    else
        return double(scores_to_sort[ n/2 ]);  // same as (n-1)/2 because n is odd
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " grades-file\n";
        return 1; }
    std::ifstream grades_str(argv[1]);
    if (!grades_str) {
        std::cerr << "Can not open the grades file " << argv[1] << "\n";
        return 1; }
    std::vector<int> scores;  // Vector to hold the input scores; initially empty.
    read_scores(scores, grades_str);   // Read the scores, as before
    // Quit with an error message if too few scores.
    if (scores.size() == 0) {
        std::cout << "No scores entered.  Please try again!" << std::endl;
        return 1; }
    // Compute the average, standard deviation and median
    double average, std_dev;
    compute_avg_and_std_dev(scores, average, std_dev);
    double median = compute_median(scores);
    // Output
    std::cout << "Among " << scores.size() << " grades: \n"
        << "  average = " << std::setprecision(3) << average << '\n'
        << "  std_dev = " << std_dev << '\n'
        << "   median = " << median << std::endl;
    return 0; 
}

