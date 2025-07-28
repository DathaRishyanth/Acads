#include <bits/stdc++.h>
using namespace std;

void allocateCourses(map<string,vector<int>> &courses, map<string,vector<int>>  &Students){
    queue<string> q;
    map<string, string> studentToCourse; //student to course mapping
    map<string, string> courseToStudent; //course to student mapping
    map<string, int> studentIndex; //index of the course that the student is currently looking at

    for(auto it = Students.begin(); it!=Students.end();it++){
        q.push(it->first);
        studentIndex[it->first] = 0;
    }

    while(!q.empty()){
        string student = q.front();
        q.pop();
        int courseIndex = Students[student][studentIndex[student]];
        string course = "C" + to_string(courseIndex);

        if(courseToStudent.find(course) == courseToStudent.end()){
            courseToStudent[course] = student;
            studentToCourse[student] = course;
        } else {
            string currentStudent = courseToStudent[course];
            vector<int> &preferences = courses[course];
            if(find(preferences.begin(), preferences.end(), stoi(student.substr(1))) < find(preferences.begin(), preferences.end(), stoi(currentStudent.substr(1)))){
                courseToStudent[course] = student;
                studentToCourse[student] = course;
                q.push(currentStudent);
            } else {
                q.push(student);
            }
        }
        studentIndex[student]++;
    }

    for(auto it = studentToCourse.begin(); it != studentToCourse.end(); it++){
        cout << it->first << " is allocated to " << it->second << endl;
    }
}

int main(){
    map<string,vector<int>>  courses;
    map<string,vector<int> > Students;
    courses["C0"] = {2,1,2};
    courses["C1"] = {2,1,0};
    courses["C2"] = {0,1,2};

    Students["S0"] = {0,1,2};
    Students["S1"] = {2,1,0};
    Students["S2"] = {0,1,2};

    allocateCourses(courses,Students);
    return 0;
}