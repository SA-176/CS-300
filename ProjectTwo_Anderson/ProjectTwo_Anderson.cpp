//========================================================================
//  ProjectTwo.cpp : This file contains the 'main' function. 
// CS-300
// Steven Anderson
// Feb 2023
//=========================================================================

//CSVparser.cpp and CSVparser.hpp are included from when I was trying to make them work
//same with info.csv

#include <iostream>
#include <fstream>
#include <sstream> // getline wouldn't work without
#include <vector>
#include <cstring>

using namespace std;

// define Course
struct Course {
    string courseNumber;
    string courseName;
    // use a string vector to store prerequisites
    vector<string> preReq;
};

// token used to split the string into multiple strings when it comes accross a comma
vector<string> token(string tokenString, string del = " ") {
    //create vector to send back
    vector<string> tokenArray;

    //variables to control start and ending of while loop through the line
    int start = 0;
    int end = tokenString.find(del);

    while (end != -1) {
        tokenArray.push_back(tokenString.substr(start, end - start));
        start = end + del.size();
        end = tokenString.find(del, start);
    }

    tokenArray.push_back(tokenString.substr(start, end - start));

    return tokenArray;
}

// loadFile used to load data from file to vector
vector<Course> loadFile() {

    // make file as ifstream while opening info.txt assigned to it
    ifstream file("info.txt", ios::in);

    //variables for vector and line
    vector<Course> courses;
    string line;

    //variable to keep count of how many courses have been read
    int count = 0;

    //test line 
    // cout << "test 1" << endl;

    // uses getline to run until the end of the file
    while (getline(file, line)) {
        // course object variable
        Course course;

        // assign vector tokenInfo with results from token to break the string vector appart
        vector<string> tokenInfo = token(line, ",");

        //test line 
        // cout << "test 2" << endl;

        //if tokenInfo is more than 1
        if (tokenInfo.size() > 1) {
            // assigning number and name of course
            course.courseNumber = tokenInfo[0];
            course.courseName = tokenInfo[1];

            // for loop to find preReqs
            for (int i = 2; i < tokenInfo.size(); i++) {
                //test line 
                // cout << "test 3" << endl;

                //use push back to add preReq
                course.preReq.push_back(tokenInfo[i]);
            }

            // using push back to add information to courses
            courses.push_back(course);

            count += 1;
        }
    }

    //closes file to avoid any memory leak
    file.close();

    //prints how many courses were loaded
    cout << "Loaded " << count << " Courses" << endl << endl;

    // returning courses
    return courses;
}

// function to print a course
void printCourse(Course course) {

    //variables for number, name and prerequisites
    string courseNumber = course.courseNumber;
    string courseName = course.courseName;
    vector<string> prerequisites = course.preReq;

    // print statement for course information
    cout << courseNumber << ", " << courseName << endl << "Prerequisites: ";

    //for loop til all prerequisites are printed
    for (int i = 0; i < prerequisites.size(); i++) {
        cout << prerequisites[i] << " ";
    }

    cout << endl << endl;
}

// function to print the list of all courses
void printCourseList(vector<Course> courses) {
    int n = courses.size();

    // sorting the courses according the course number
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                swap(courses[j + 1], courses[j]);
            }
        }
    }

    // printing the list of all courses
    for (int i = 0; i < n; i++) {
        //prints the course number and name
        cout << courses[i].courseNumber << ", " << courses[i].courseName << endl;
    }
}

// function to find a course with a course number
void searchCourse(vector<Course> courses, string courseNumber) {
    int n = courses.size();

    // variable used for if program doesn't find course
    int f = 0;

    // searching and showing details of the course if found
    cout << "\nCourse Details: \n";
    for (int i = 0; i < n; i++) {

        if (_stricmp(courses[i].courseNumber.c_str(), courseNumber.c_str()) == 0) {
            // then printing its details
            f = 1;
            printCourse(courses[i]);
            break;
        }
    }

    // message printed if course isnt found in vector
    if (f == 0) {
        cout << "Sorry, course with number: " << courseNumber << " was not found" << endl << endl;
    }
}

int main(int argc, char** argv) {
    // vector array to store all the courses
    vector<Course> courses;

    // variable to store user's choice and string for course choice
    int choice = 0;
    string courseNumber;

    //opening message
    cout << "*Course Planner*" << endl;
    cout << "===============================================================" << endl;

    while (choice != 9) {

        // showing menu to the users each loop of while
        cout << endl << "1.Load From File" << endl;
        cout << "2.Print Course List" << endl;
        cout << "3.Print Course Information" << endl;
        cout << "9.Exit" << endl << endl;

        cout << "Enter Choice: " << endl;
        cin >> choice;
        cout << endl;

        //switch used to interpret user choice
        switch (choice)
        {
        case 1:
            //assigns courses with the results of file loaded
            courses = loadFile();
            break;
        case 2:
            // call to print all the lists
            printCourseList(courses);
            break;
        case 3:
            // message and input for user search
            cout << "Enter Course Number: " << endl;
            cin >> courseNumber;

            //call search course to find user inputed course number
            searchCourse(courses, courseNumber);
            break;
        case 9:
            // exit message
            cout << "Goodbye!" << endl;
            cout << "===============================================================" << endl;
            break;
        default:
            // cout << "Invalid Choice\n";
            cout << choice << " is not a valid choice" << endl << endl;
        }
    }

    return 0;
}