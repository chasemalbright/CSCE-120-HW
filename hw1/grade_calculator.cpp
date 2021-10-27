// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double examGrade = 0;
    double examCount = 0;


    double finalExamGrade = 0;
    double finalExamCount = 0;

    // double examTotalAverage = 0;
    

    double hwGrade = 0;
    double hwCount = 0;
    double hwAverage = 0;

    double lwGrade = 0;
    double lwCount = 0;
    double lwAverage = 0;

    double engageCount = 0;
    double engageGrades = 0;

    

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            examCount += 1;
            examGrade = examGrade + score;
            // examTotalAverage = examGrade / examCount;
        } else if (category == "final-exam") {
            finalExamCount += 1;
            finalExamGrade = finalExamGrade + score;
            // examGrade = examGrade + score;
            // finalExamGrade = score;
            // if ((examGrade / examCount) > finalExamGrade ) {
            //     examTotalAverage = examGrade / examCount;
            // } else if (finalExamGrade >= (examGrade / examCount)) {
            //     examTotalAverage = finalExamGrade;
            // }

        } else if (category == "hw") {
            hwCount += 1;
            hwGrade = hwGrade + score;
            hwAverage = hwGrade / hwCount;
        } else if (category == "lw") {
            if (score > 1) {
                score = 1;
            }
            lwCount += 1;
            lwGrade = lwGrade + score;
            lwAverage = (lwGrade / lwCount) * 100;
        } else if (category == "engagement") {
            engageCount += 1;

            engageGrades = engageGrades + score;
            //engageAverage = engageGrades / engageCount;
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double examTotalAvg = 0;

    if (examCount < 2 && finalExamCount == 0) {
        examTotalAvg = examGrade / (examCount+2);
    } else if (examCount == 1 && finalExamCount == 1) {
        examTotalAvg = (examGrade + finalExamGrade) / (examCount +1+ finalExamCount);
        if (finalExamGrade >= examTotalAvg) {
            examTotalAvg = finalExamGrade;
        }
    } else if (finalExamCount == 0) {
        examTotalAvg = examGrade / (examCount+1);
    } else if (finalExamCount > 0) {
        examTotalAvg = (examGrade + finalExamGrade) / (examCount + finalExamCount);
        if (finalExamGrade >= examTotalAvg) {
            examTotalAvg = finalExamGrade;
        }
    }

    if (engageGrades >= 100) {
        engageGrades = 100;
    } 



    double exam_average = examTotalAvg;
    double hw_average = hwAverage;
    double lw_average = lwAverage;
    double engagement = engageGrades;

    // TODO(student): compute weighted total of components
    
    double weighted_total = ((exam_average / 100) * 40) + ((hw_average / 100) * 40) + ((lw_average / 100) * 10) + ((engagement / 100) * 10);

    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';

    if (weighted_total < 60) {
        final_letter_grade = 'F';
    } else if (weighted_total >= 60 && weighted_total < 70) {
        final_letter_grade = 'D';
    } else if (weighted_total >= 70 && weighted_total < 80) {
        final_letter_grade = 'C';
    } else if (weighted_total >= 80 && weighted_total < 90) {
        final_letter_grade = 'B';
    } else {
        final_letter_grade = 'A';
    }
    

    print_results(
        exam_average, hw_average, lw_average, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
