/*main.cpp*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <functional>

#include "student.h"

using namespace std;


//
// input(filename):
// 
// Inputs student data from the file and returns a map of Student objects.
// 
map<string,Student> input(string filename)
{
  ifstream  file(filename);
  string    line, name, mid, fnl;
  
  map<string,Student> students;

  if (!file.good())
  {
    cout << "**Error: cannot open input file!" << endl;
    return students;
  }

  getline(file, line);  // skip header row:

  //
  // for each line of data, create a student and push into the vector:
  // 
  while (getline(file, line))
  {
    stringstream  ss(line);

    // format: name,midterm,final
    getline(ss, name, ',');
    getline(ss, mid, ',');
    getline(ss, fnl);

    Student  S(name, stoi(mid), stoi(fnl));
    
    //
    // insert student into map, using name as the key.
    // Insert using map's overloaded [ ] operator:
    // 
    students[name] = S;
  }
  
  return students;
}

//
// main:
// 
int main()
{  
  cout << std::fixed;
  cout << std::setprecision(2); 
  
  // 1. Input student data:
  auto students = input("exams.csv");
  
  // 2. Output:
  cout << "** students **" << endl;
  
  for(const auto& keyvaluepair : students)
  {
    cout << keyvaluepair.first << ":" << keyvaluepair.second.ExamAvg() << endl;
  }
  
  string name;
  
  cout << "** lookup **" << endl;
  
  cout << "Please enter a name (or #)> ";
  cin >> name;
  
  while (name != "#")
  {

    auto iter = std::find_if(students.begin(), students.end(),
                             [=](const pair<string, Student> thing) {
                                 if(thing.first == name) {
                                     return true;
                                 }
                                 else {
                                     return false;
                                 }
                             });
    if(iter == students.end()) {
        cout << "not found" << endl;
    }
    else {
        cout << iter->first << ":" << students[iter->first].ExamAvg() << endl;
    }
	
    cout << students[name].Name << ":" <<students[name].ExamAvg() << endl;
    //
    // prompt for next name and repeat:
    //
    cout << "Please enter a name (or #)> ";
    cin >> name;
  }
  return 0;
}
