/*main.cpp*/

//
// <<YOUR NAME HERE>>
// U. of Illinois, Chicago
// CS 341, Spring 2019
// HW #05: std::map
//

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
    // TODO #1: insert student into map, using name as the key.
    // Insert using map's insert() method, which requires the
    // insert of a (key, value) pair.
    // 
     auto keyvaluepair = std::pair<string, Student>(name, S);
     students.insert(keyvaluepair);
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
  
  // 3. Interact with user and lookup students:
  string name;
  
  cout << "** lookup **" << endl;
  
  cout << "Please enter a name (or #)> ";
  cin >> name;
  
  while (name != "#")
  {
    auto g = find_if(students.begin(), students.end(), 
                      [&](pair<string, Student> y)
                       {
                          if(y.first.compare(name) == 0){
                              return true;
                          }else{
                              return false;
                          } 
                       });
      if(g == students.end()){
          cout << "not found" << endl;
      }
      else{
          cout << name << ":" << g->second.ExamAvg() << endl;
      }

    
    //
    // TODO #4: now lookup using map's find() method. Much like
    // std::find_if, find() returns an iterator to a (key, value)
    // pair.  
    //
     auto iter2 = students.find(name);
    // 
     if (iter2 == students.end())
       cout << "not found" << endl;
     else
       cout << name << ":" << iter2->second.ExamAvg() << endl;

    
    //
    // prompt for next name and repeat:
    //
    cout << "Please enter a name (or #)> ";
    cin >> name;
  }

  //
  // done:
  //
  return 0;
}
