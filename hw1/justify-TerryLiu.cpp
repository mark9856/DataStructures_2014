#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

std::string start_line;
std::string blanks;
std::string empty_line;

//read from file and put each word in a vector. If a word is longer than the width of the wrapper,
//break it into several pieces of words with the length that is equal to or less than the wrapper's
//width.
std::vector<std::string> longwordjustify(std::ifstream & input, unsigned int width) {
    std::string word;
    unsigned int line = 0;
    unsigned int remainingchar = 0;
    std::string tmpstring(15,' ');
    std::vector<std::string> content_tmp;
     while (input >> word) {
         if (word.size() <= width) {
             content_tmp.push_back (word);
         }
         else {
             line = word.size()/width + 1;
             remainingchar = word.size() % width;
             tmpstring.resize(width);
             for (unsigned int i = 0; i < line - 1; i++) {
                 for (unsigned int j = 0; j < width - 1; j++) {
                    tmpstring[j] = word[j+i*(width-1)];
                 }
                 tmpstring[width-1] = '-';
                 content_tmp.push_back(tmpstring);
                 remainingchar++;
             }
             tmpstring.clear();
             tmpstring.resize(remainingchar);
             for (unsigned int i = 0; i < remainingchar; i++) {
                 tmpstring[i] = word[i+(line-1)*(width-1)];
             }
             content_tmp.push_back(tmpstring);
         }
     }
    return content_tmp;
}

//Returns the number of whitespaces after a string of words that are seperated by one whitespace.
std::vector<unsigned int> getwhitespace(const std::vector<std::string> & content, unsigned int width) {
    unsigned int nextplace = 0;
    std::vector<unsigned int> whitespace;
    for (unsigned int i = 0; i < content.size(); i++) {
        if (content[i].size() < width - nextplace - 1) {
                nextplace = nextplace + content[i].size();
        }
        else if (content[i].size() == width - nextplace - 1) {
            whitespace.push_back (1);
            nextplace = 0;
            continue;
        }
        else if (content[i].size() == width - nextplace) {
            whitespace.push_back (0);
            nextplace = 0;
            continue;
        }
        
        else {
            whitespace.push_back (width - nextplace + 1);
            nextplace = 0;
            i--;
            continue;
        }
    nextplace++;
    }
    nextplace--;
    whitespace.push_back(width - nextplace );
    return whitespace;
}

//Returns the number of words in a line
std::vector<unsigned int> getword (const std::vector<std::string> & content, unsigned int width) {
    unsigned int nextplace = 0;
    unsigned int word = 0;
    std::vector<unsigned int> wordnumber;
    for (unsigned int i = 0; i < content.size(); i++) {
        if (content[i].size() < width - nextplace) {
            word++;
            nextplace = nextplace + content[i].size();
        }
        else if (content[i].size() == width - nextplace) {
            nextplace = 0;
            word++;
            wordnumber.push_back(word);
            word = 0;
            continue;
        }
        else {
            wordnumber.push_back(word);
            nextplace = 0;
            word = 0;
            i--;
            continue;
        }
        nextplace++;
    }
    wordnumber.push_back (word);
    return wordnumber;
}

//Returns the total number of whitespaces in a line, that is the number of whitespaces between each
//word plus the number of whitespaces after these words.
std::vector<unsigned int> getextraspace (const std::vector<unsigned int> & whitespace, const std::vector<unsigned int> & wordnumber) {
    std::vector<unsigned int> extraspace;
    for (unsigned int i = 0; i < whitespace.size(); i++) {
        extraspace.push_back(whitespace[i] + wordnumber[i] - 1);
    }
    return extraspace;
}

//If fully justified, returns the the least number of whitespaces after a word
std::vector<unsigned int> getspaceafteraword (const std::vector<unsigned int> & whitespace, const std::vector<unsigned int> & wordnumber) {
    std::vector<unsigned int> spaceafteraword;
    std::vector<unsigned int> totalwhitespace = getextraspace (whitespace, wordnumber);
    for (unsigned int i = 0; i < totalwhitespace.size(); i++) {
        if (wordnumber[i] != 1) {
            spaceafteraword.push_back(totalwhitespace[i]/(wordnumber[i]-1));
        }
        else {
            spaceafteraword.push_back(0);
        }
    }
    return spaceafteraword;
}

//If fully justified, returns the number of remaining whitespaces
std::vector<unsigned int> getremains (const std::vector<unsigned int> & whitespace, const std::vector<unsigned int> & wordnumber) {
    std::vector<unsigned int> remains;
    std::vector<unsigned int> totalwhitespace = getextraspace (whitespace, wordnumber);
    for (unsigned int i = 0; i < totalwhitespace.size(); i++) {
        if (wordnumber[i] != 1) {
            remains.push_back(totalwhitespace[i]%(wordnumber[i]-1));
        }
        else {
            remains.push_back(0);
        }
    }
    return remains;
}

//To flush left
std::vector<std::string> flush_left (const std::vector<std::string> & content, unsigned int width) {
    unsigned int nextplace = 0;
    std::string one_line = empty_line;
    std::vector<std::string> formatted;
    formatted.push_back (start_line);
    for (unsigned int i = 0; i < content.size(); i++) {
        if (content[i].size() < width - nextplace +1) {
            for (unsigned int j = 0; j < content[i].size(); j++) {
                one_line[2+nextplace+j] = content[i][j];
            }
            nextplace = nextplace + content[i].size();
            one_line[2+nextplace] = ' ';
            nextplace++;
        }
        else {
            for (unsigned int m = nextplace; m < width; m++ ) {
                one_line[2+m] = ' ';
            }
            formatted.push_back (one_line);
            nextplace = 0;
            i--;
            continue;
        }
    }
    for (unsigned int m = nextplace; m < width; m++ ) {
        one_line[2+m] = ' ';
    }
    formatted.push_back (one_line);
    formatted.push_back (start_line);
    return formatted;
}

//To flush right
std::vector<std::string> flush_right (const std::vector<std::string> & content, unsigned int width) {
    unsigned int nextplace = 0;
    unsigned int nextword = 0;
    std::vector<unsigned int> whitespace;
    std::string one_line = empty_line;
    std::vector<std::string> formatted;
    formatted.push_back (start_line);
    whitespace = getwhitespace(content, width);
    for (unsigned int i = 0; i < whitespace.size(); i++) {
        for (unsigned int j = 0; j < whitespace[i]; j++) {
            one_line[2+j] = ' ';
        }
        nextplace = whitespace[i];
        for (unsigned int m = nextword; m < content.size(); m++) {
            for (unsigned int n = 0; n < content[m].size(); n++) {
                one_line[2+nextplace+n] = content[m][n];
            }
            nextplace = nextplace + content[m].size();
            if (nextplace < width) {
                one_line[2+nextplace] = ' ';
                nextplace++;
            }
            else {
                formatted.push_back (one_line);
                nextword = m + 1;
                break;
            }
        }
    }
    formatted.push_back (start_line);
    return formatted;
}

//To fully justify
std::vector<std::string> full_justify (const std::vector<std::string> & content, unsigned int width) {
    unsigned int nextplace = 0;
    std::vector<unsigned int> whitespace;
    std::vector<unsigned int> wordnumber;
    std::string one_line = empty_line;
    std::vector<std::string> formatted;
    formatted.push_back (start_line);
    whitespace = getwhitespace(content, width);
    wordnumber = getword(content, width);
    std::vector<unsigned int> extraspace = getextraspace (whitespace, wordnumber);
    std::vector<unsigned int> remains = getremains (whitespace, wordnumber);
    std::vector<unsigned int> spaceafter = getspaceafteraword (whitespace, wordnumber);
    unsigned int capacity = remains.size();
    unsigned int wordindex = 0;
    for (unsigned int i = 0; i < capacity - 1; i++) {
        for (unsigned int j = 0; j < wordnumber[i]; j++) {
            for (unsigned int m = 0; m < content[wordindex].size(); m++) {
                one_line[2+nextplace+m] = content[wordindex][m];
            }
            nextplace = nextplace + content[wordindex].size();
            wordindex++;
            if (content[wordindex + 1].size() == width) {
                for (unsigned int m = nextplace; m < width; m++ ) {
                    one_line[2+m] = ' ';
                }
            }
            else {
                for (unsigned int n = 0; (n < spaceafter[i])&&(j < wordnumber[i] - 1); n++) {
                    one_line[2+nextplace] = ' ';
                    nextplace++;
                }
            
                if (j < remains[i]) {
                    one_line[2+nextplace] = ' ';
                    nextplace++;
                }
            }
        }
        formatted.push_back (one_line);
        nextplace = 0;
    }
    for (unsigned int i = 0; i < wordnumber[capacity-1]; i++) {
            for (unsigned int j = 0; j < content[wordindex].size(); j++) {
                one_line[2+nextplace+j] = content[wordindex][j];
            }
            nextplace = nextplace + content[wordindex].size();
            one_line[2+nextplace] = ' ';
            nextplace++;
        wordindex++;
    }
    for (unsigned int m = nextplace; m < width; m++ ) {
        one_line[2+m] = ' ';
    }
    formatted.push_back (one_line);
    formatted.push_back (start_line);
    return formatted;
}

//Set the wrapper type
void setwrapper (unsigned int width) {
    const std::string start_line_tmp(width+4, '-');
    const std::string blanks_tmp(width+2, ' ');
    const std::string empty_line_tmp = '|'+blanks_tmp+'|';
    start_line=start_line_tmp;
    blanks=blanks_tmp;
    empty_line=empty_line_tmp;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " lack of arguments.\n";
        return 1;
    }
    
    std::ifstream input_str(argv[1]);
    if (!input_str.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        return 1;
    }
    
    std::ofstream output_str(argv[2]);
    if (!output_str.good()) {
        std::cerr << "Can't open " << argv[2] << " to write.\n";
        return 1;
    }
    
    std::string width_string = std::string(argv[3]);
    unsigned int width = atoi (width_string.c_str());
    std::vector<std::string> content = longwordjustify(input_str,width);
    std::vector<std::string> formatted;
    setwrapper (width);
    if (std::string(argv[4]) == std::string("flush_left")) {
        formatted = flush_left (content, width);
    }
    else if (std::string(argv[4]) == std::string("flush_right")) {
        formatted = flush_right (content, width);
    }
    else if (std::string(argv[4]) == std::string("full_justify")) {
        formatted = full_justify (content, width);
    }
    for (unsigned int i = 0; i < formatted.size(); i++) {
        output_str << formatted[i] << "\n";
    }
    return 0;
}