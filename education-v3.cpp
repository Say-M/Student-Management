#include <bits/stdc++.h>
using namespace std;

// ! student class
class Student
{
    string name, id, department, section;
    float cgpa = -1.0;

public:
    // ! make course class & teacher class as a friend of student class
    friend class Course;
    friend class Teacher;

    // ! add student
    void addStudent(string name, string id, string department, string section)
    {
        this->name = name;
        this->id = id;
        this->department = department;
        this->section = section;

        fstream file("students.txt", ios::app);
        file << id << endl
             << name << endl
             << section << endl
             << department << endl
             << cgpa << endl;
        cout << "Student added successfully\n\n";
        file.close();
    }

    // ! show students
    void showStudents()
    {
        int total = 0;
        fstream file("students.txt", ios::in);
        file >> id >> name >> section >> department >> cgpa;
        while (!file.eof())
        {
            if (total == 0)
                cout << "ID"
                     << "\t\tName"
                     << "\t\t\tSection"
                     << "\t\tDepartment"
                     << "\t\tCGPA\n";
            cout << id << "\t\t" << name << "\t\t\t" << section << "\t\t" << department << "\t\t\t";
            if (cgpa < 0)
                cout << "Not Published" << endl;
            else
                cout << cgpa << endl;
            total++;
            file >> id >> name >> section >> department >> cgpa;
        }
        if (total == 0)
            cout << "No students found";
        cout << "\n\n";
        file.close();
    }

    // ! search student
    void searchStudent()
    {
        int total = 0;
        string _id;
        cout << "Search by Student ID - ";
        cin >> _id;
        fstream file("students.txt", ios::in);
        file >> id >> name >> section >> department >> cgpa;
        while (!file.eof())
        {
            if (_id == id)
            {
                if (total == 0)
                    cout << "ID"
                         << "\t\tName"
                         << "\t\t\tSection"
                         << "\t\tDepartment"
                         << "\t\tCGPA\n";
                cout << id << "\t\t" << name << "\t\t\t" << section << "\t\t" << department << "\t\t\t";
                if (cgpa < 0)
                    cout << "Not Published" << endl;
                else
                    cout << cgpa << endl;
                total++;
            }
            file >> id >> name >> section >> department >> cgpa;
        }
        if (total == 0)
            cout << "No students found";
        cout << "\n\n";
        file.close();
    }

    // ! update student
    void updateStudent()
    {
        int total = 0;
        string _id;
        cout << "Enter Student ID which you wanna update - ";
        cin >> _id;
        fstream file("students.txt", ios::in);
        fstream u_file("u_students.txt", ios::out);
        file >> id >> name >> section >> department >> cgpa;
        while (!file.eof())
        {
            if (_id == id)
            {
                string _name, _id, _department, _section;
                cout << "Update student name - ";
                cin >> _name;
                cout << "Update student ID - ";
                cin >> _id;
                cout << "Update student department - ";
                cin >> _department;
                cout << "Update student section - ";
                cin >> _section;
                u_file << _id << endl
                       << _name << endl
                       << _section << endl
                       << _department << endl
                       << cgpa << endl;
                total++;
            }
            else
            {
                u_file << id << endl
                       << name << endl
                       << section << endl
                       << department << endl
                       << cgpa << endl;
            }
            file >> id >> name >> section >> department >> cgpa;
        }
        if (total == 0)
            cout << "No students found";
        else
            cout << "Student updated successfully";
        cout << "\n\n";
        u_file.close();
        file.close();
        remove("students.txt");
        rename("u_students.txt", "students.txt");
    }

    // ! delete student
    void deleteStudent()
    {
        int total = 0;
        string _id;
        cout << "Enter Student ID which you wanna delete - ";
        cin >> _id;
        fstream file("students.txt", ios::in);
        fstream d_file("d_students.txt", ios::out);
        file >> id >> name >> section >> department >> cgpa;
        while (!file.eof())
        {
            if (_id != id)
            {
                d_file << id << endl
                       << name << endl
                       << section << endl
                       << department << endl
                       << cgpa << endl;
                total++;
            }
            file >> id >> name >> section >> department >> cgpa;
        }
        if (total == 0)
            cout << "No students found";
        else
            cout << "Student deleted successfully";
        cout << "\n\n";
        d_file.close();
        file.close();
        remove("students.txt");
        rename("d_students.txt", "students.txt");
    }
};

// ! course class
class Course
{
    string c_name, studentId;
    int marks = -1;
    float gpa = -1.0;

public:
    // ! make teacher class as a friend of course class
    friend class Teacher;
    friend class Student;

    // ! add course
    void addCourse(string c_name, string studentId, Student student)
    {
        int total = 0;
        this->c_name = c_name;
        this->studentId = studentId;
        fstream s_file("students.txt", ios::in);
        fstream u_file("u_students.txt", ios::out);
        s_file >> student.id >> student.name >> student.section >> student.department >> student.cgpa;
        while (!s_file.eof())
        {
            if (studentId == student.id)
            {
                u_file << student.id << endl
                       << student.name << endl
                       << student.section << endl
                       << student.department << endl
                       << student.cgpa << endl;
                fstream file("courses.txt", ios::app);
                file << c_name << endl
                     << studentId << endl
                     << marks << endl
                     << gpa << endl;
                file.close();
                cout << "Course added successfully\n\n";
                total++;
            }
            else
            {
                u_file << student.id << endl
                       << student.name << endl
                       << student.section << endl
                       << student.department << endl
                       << student.cgpa << endl;
            }
            s_file >> student.id >> student.name >> student.section >> student.department >> student.cgpa;
        }
        if (total == 0)
            cout << "No student found so you cannot add course\n\n";
        s_file.close();
        u_file.close();
        remove("students.txt");
        rename("u_students.txt", "students.txt");
    }

    // ! show courses taken by a student
    void showCourses(Student student)
    {
        system("cls");
        int s_total = 0, c_total = 0;
        string _id, s_name;
        cout << "Enter Student ID - ";
        cin >> _id;
        fstream s_file("students.txt", ios::in);
        s_file >> student.id >> student.name >> student.section >> student.department >> student.cgpa;
        while (!s_file.eof())
        {
            if (_id == student.id)
            {
                s_name = student.name;
                cout << "\n\n----Student Information----\n";
                cout << "Name - " << student.name << endl;
                cout << "Section - " << student.section << endl;
                cout << "Department - " << student.department << endl
                     << endl;
                s_total++;
            }
            s_file >> student.id >> student.name >> student.section >> student.department >> student.cgpa;
        }
        fstream c_file("courses.txt", ios::in);
        c_file >> c_name >> studentId >> marks >> gpa;
        while (!c_file.eof())
        {
            if (_id == studentId)
            {
                if (c_total == 0)
                    cout << "Course Name"
                         << "\t\tMarks"
                         << "\t\t\t\tGPA" << endl;
                cout << c_name << "\t\t\t";
                if (marks < 0)
                    cout << "Not yet graded"
                         << "\t\t\t";
                else
                    cout << marks << "\t\t\t";
                if (gpa < 0)
                    cout << "Not yet graded" << endl;
                else
                    cout << gpa << endl;
                c_total++;
            }
            c_file >> c_name >> studentId >> marks >> gpa;
        }
        if (s_total == 0)
            cout << "No student found";
        if (c_total == 0 && s_total != 0)
            cout << s_name << " not registered for any course yet";
        cout << "\n\n";
        c_file.close();
    }

    // ! update course
    void updateCourse()
    {
        int total = 0;
        string _id;
        cout << "Enter Student ID which course you wanna update - ";
        cin >> _id;
        fstream file("courses.txt", ios::in);
        fstream u_file("u_courses.txt", ios::out);
        file >> c_name >> studentId >> marks >> gpa;
        while (!file.eof())
        {
            if (_id == studentId)
            {
                cout << "Update course name - ";
                cin >> c_name;
                u_file << c_name << endl
                       << studentId << endl
                       << marks << endl
                       << gpa << endl;
                total++;
            }
            else
            {
                u_file << c_name << endl
                       << studentId << endl
                       << marks << endl
                       << gpa << endl;
            }
            file >> c_name >> studentId >> marks >> gpa;
        }
        if (total == 0)
            cout << "No course found";
        else
            cout << "Course updated successfully";
        cout << "\n\n";
        u_file.close();
        file.close();
        remove("courses.txt");
        rename("u_courses.txt", "courses.txt");
    }

    // ! delete course
    void deleteCourse()
    {
        int total = 0;
        string _id, _c_name;
        cout << "Enter course information which you wanna delete - \n";
        cout << "Student ID - ";
        cin >> _id;
        cout << "Course Name - ";
        cin >> _c_name;
        fstream file("courses.txt", ios::in);
        fstream d_file("d_courses.txt", ios::out);
        file >> c_name >> studentId >> marks >> gpa;
        while (!file.eof())
        {
            if (_id != studentId || _c_name != c_name)
            {
                d_file << c_name << endl
                       << studentId << endl
                       << marks << endl
                       << gpa << endl;
            }
            else
                total++;
            file >> c_name >> studentId >> marks >> gpa;
        }
        if (total == 0)
            cout << "No course found";
        else
            cout << "Course deleted successfully";
        cout << "\n\n";
        d_file.close();
        file.close();
        remove("courses.txt");
        rename("d_courses.txt", "courses.txt");
    }

    // ! show student's result
    void showResult(Student student)
    {
        int s_total = 0, c_total = 0;
        float total_cpga = 0;
        string _id, s_name;
        cout << "Enter Student ID which result you wanna see - ";
        cin >> _id;
        fstream s_file("students.txt", ios::in);
        s_file >> student.id >> student.name >> student.section >> student.department >> student.cgpa;
        while (!s_file.eof())
        {
            if (_id == student.id)
            {
                s_name = student.name;
                cout << "\n\n----Student Information----\n";
                cout << "Name - " << student.name << endl;
                cout << "Section - " << student.section << endl;
                cout << "Department - " << student.department << endl
                     << endl;
                s_total++;
            }
            s_file >> student.id >> student.name >> student.section >> student.department >> student.cgpa;
        }
        fstream c_file("courses.txt", ios::in);
        c_file >> c_name >> studentId >> marks >> gpa;
        while (!c_file.eof())
        {
            if (_id == studentId)
            {
                if (c_total == 0)
                    cout << "Course Name"
                         << "\t\tMarks"
                         << "\t\t\tGPA\n";
                cout << c_name << "\t\t\t";
                if (marks < 0)
                    cout << "Not yet graded"
                         << "\t\t";
                else
                    cout << marks << "\t\t\t";
                if (gpa < 0)
                    cout << "Not yet graded" << endl;
                else
                {
                    cout << gpa << endl;
                    total_cpga += gpa;
                    c_total++;
                }
            }
            c_file >> c_name >> studentId >> marks >> gpa;
        }
        if (c_total)
        {
            cout << "\nTotal CGPA - " << total_cpga / c_total << endl;
        }
        else
            cout << endl
                 << s_name << " result isn't published yet" << endl;
        cout << "\n\n";
    }
};

// ! teacher class
class Teacher
{
    string name, id, department;

public:
    // ! add teacher
    void addTeacher(string name, string id, string department)
    {
        this->name = name;
        this->id = id;
        this->department = department;

        fstream file("teachers.txt", ios::app);
        file << id << endl
             << name << endl
             << department << endl;
        file.close();
    }

    // ! show teachers
    void showTeachers()
    {
        int total = 0;
        fstream file("teachers.txt", ios::in);
        file >> id >> name >> department;
        while (!file.eof())
        {
            if (total == 0)
                cout << "ID"
                     << "\t\tName"
                     << "\t\tDepartment" << endl;
            cout << id << "\t\t" << name << "\t\t" << department << endl;
            total++;
            file >> id >> name >> department;
        }
        if (total == 0)
            cout << "No teacher found";
        cout << "\n\n";
        file.close();
    }

    // ! search teacher
    void searchTeacher()
    {
        int total = 0;
        string _id;
        cout << "Search by Teacher ID - ";
        cin >> _id;
        fstream file("teacher.txt", ios::in);
        file >> id >> name >> department;
        while (!file.eof())
        {
            if (_id == id)
            {
                if (total == 0)
                    cout << "ID"
                         << "\t\tName"
                         << "\t\t\tDepartment" << endl;
                cout << id << "\t\t" << name << "\t\t\t" << department << endl;
                total++;
            }
            file >> id >> name >> department;
        }
        if (total == 0)
            cout << "No teacher found";
        cout << "\n\n";
        file.close();
    }

    // ! update teacher
    void updateTeacher()
    {
        int total = 0;
        string _id;
        cout << "Enter Teacher ID which you wanna update - ";
        cin >> _id;
        fstream file("teachers.txt", ios::in);
        fstream u_file("u_teachers.txt", ios::out);
        file >> id >> name >> department;
        while (!file.eof())
        {
            if (_id == id)
            {
                string _name, _id, _department;
                cout << "Update teacher name - ";
                cin >> _name;
                cout << "Update teacher ID - ";
                cin >> _id;
                cout << "Update teacher department - ";
                u_file << _id << endl
                       << _name << endl
                       << _department << endl;
                total++;
            }
            else
            {
                u_file << id << endl
                       << name << endl
                       << department << endl;
            }
            file >> id >> name >> department;
        }
        if (total == 0)
            cout << "No teacher found";
        else
            cout << "Teacher updated successfully";
        cout << "\n\n";
        u_file.close();
        file.close();
        remove("teachers.txt");
        rename("u_teachers.txt", "teachers.txt");
    }

    // ! delete Teacher
    void deleteTeacher()
    {
        int total = 0;
        string _id;
        cout << "Enter Teacher ID which you wanna delete - ";
        cin >> _id;
        fstream file("teachers.txt", ios::in);
        fstream d_file("d_teachers.txt", ios::out);
        file >> id >> name >> department;
        while (!file.eof())
        {
            if (_id != id)
            {
                d_file << id << endl
                       << name << endl
                       << department << endl;
                total++;
            }
            file >> id >> name >> department;
        }
        if (total == 0)
            cout << "No teachers found";
        else
            cout << "Teacher deleted successfully";
        cout << "\n\n";
        d_file.close();
        file.close();
        remove("teachers.txt");
        rename("d_teachers.txt", "teachers.txt");
    }

    // ! result processing
    void resultProcessing(Course course, Student student)
    {
        int s_total = 0, c_total = 0;
        string _id, s_name;
        cout << "Enter Student ID which result you wanna publish - ";
        cin >> _id;
        fstream s_file("students.txt", ios::in);
        s_file >> student.id >> student.name >> student.section >> student.department >> student.cgpa;
        while (!s_file.eof())
        {
            if (_id == student.id)
            {
                cout << "----Student Information----\n";
                s_name = student.name;
                cout << "Name - " << student.name << endl;
                cout << "Section - " << student.section << endl;
                cout << "Department - " << student.department << endl
                     << endl;
                s_total++;
            }
            s_file >> id >> name >> department;
        }
        if (s_total == 0)
            cout << "No student found";
        fstream c_file("courses.txt", ios::in);
        fstream u_c_file("u_courses.txt", ios::out);
        // fstream u_s_file("u_students.txt", ios::out);
        c_file >> course.c_name >> course.studentId >> course.marks >> course.gpa;
        while (!c_file.eof())
        {
            if (_id == course.studentId)
            {
                int marks;
                float gpa;
                cout << "----Course Information----\n";
                cout << "Course Name - " << course.c_name << endl;
                cout << "Update obtain marks - ";
                cin >> marks;
                if (marks >= 80)
                    gpa = 4.00;
                else if (marks >= 75 && marks < 80)
                    gpa = 3.75;
                else if (marks >= 70 && marks < 75)
                    gpa = 3.50;
                else if (marks >= 65 && marks < 70)
                    gpa = 3.25;
                else if (marks >= 60 && marks < 65)
                    gpa = 3.00;
                else if (marks >= 55 && marks < 60)
                    gpa = 2.75;
                else if (marks >= 50 && marks < 55)
                    gpa = 2.50;
                else if (marks >= 45 && marks < 50)
                    gpa = 2.25;
                else if (marks >= 40 && marks < 45)
                    gpa = 2.00;
                else
                    gpa = 0.00;
                u_c_file << course.c_name << endl
                         << course.studentId << endl
                         << marks << endl
                         << gpa << endl;
                c_total++;
            }
            c_file >> course.c_name >> course.studentId >> course.marks >> course.gpa;
        }
        if (c_total == 0 && s_total != 0)
            cout << s_name << " not registered for any course yet";
        cout << "\n\n";
        c_file.close();
        u_c_file.close();
        remove("courses.txt");
        rename("u_courses.txt", "courses.txt");
    }
};

// ! starting menu options
void showInitialMenu()
{
    cout << "1. Enter student panel\n";
    cout << "2. Enter teacher panel\n";
    cout << "0. Exit programme\n";
}

// ! student menu options
void showStudentMenu()
{
    cout << "1. Add a student\n";
    cout << "2. Show students information\n";
    cout << "3. Search student information\n";
    cout << "4. Update a student information\n";
    cout << "5. Delete a student information\n";
    cout << "6. Course registration\n";
    cout << "7. See results\n";
    cout << "0. Back\n";
}

// ! course menu options
void showCourseMenu()
{
    cout << "1. Add a course to a student\n";
    cout << "2. Show courses taken by a student\n";
    cout << "3. Update a course taken by a student\n";
    cout << "4. Delete a course taken by a student\n";
    cout << "0. Back\n";
}

// ! teacher menu options
void showTeacherMenu()
{
    cout << "1. Add a teacher\n";
    cout << "2. Show teachers information\n";
    cout << "3. Search teacher information\n";
    cout << "4. Update a teacher information\n";
    cout << "5. Delete a teacher information\n";
    cout << "6. Result processing\n";
    cout << "0. Back\n";
}

// ! result processing menu options
void resultProcessingMenu()
{
    cout << "1. Process student result\n";
    cout << "2. See student result\n";
    cout << "3. Update a student result\n";
    cout << "0. Back\n";
}

int main()
{
    Student student;
    Teacher teacher;
    Course course;
    int panel = 1;
    while (panel)
    {
        showInitialMenu();
        cin >> panel;

        int choice = 1;
        while (choice)
        {
            if (panel == 1)
            {
                showStudentMenu();
                cin >> choice;
                if (choice == 1)
                {
                    system("cls");
                    string name, id, department, section;
                    cout << "Enter student name - ";
                    cin >> name;
                    cout << "Enter student ID - ";
                    cin >> id;
                    cout << "Enter student department - ";
                    cin >> department;
                    cout << "Enter student section - ";
                    cin >> section;
                    student.addStudent(name, id, department, section);
                }
                else if (choice == 2)
                {
                    system("cls");
                    student.showStudents();
                }
                else if (choice == 3)
                {
                    system("cls");
                    student.searchStudent();
                }
                else if (choice == 4)
                {
                    system("cls");
                    student.updateStudent();
                }
                else if (choice == 5)
                {
                    system("cls");
                    student.deleteStudent();
                }
                else if (choice == 6)
                {
                    system("cls");
                    int courseChoice = 1;
                    while (courseChoice)
                    {
                        showCourseMenu();
                        cin >> courseChoice;
                        if (courseChoice == 1)
                        {
                            system("cls");
                            string name, studentId;
                            cout << "Enter course name - ";
                            cin >> name;
                            cout << "Enter student ID - ";
                            cin >> studentId;
                            course.addCourse(name, studentId, student);
                        }
                        else if (courseChoice == 2)
                        {
                            system("cls");
                            course.showCourses(student);
                        }
                        else if (courseChoice == 3)
                        {
                            system("cls");
                            course.updateCourse();
                        }
                        else if (courseChoice == 4)
                        {
                            system("cls");
                            course.deleteCourse();
                        }
                        else if (courseChoice == 0)
                        {
                            system("cls");
                            break;
                        }
                    }
                }
                else if (choice == 7)
                {
                    system("cls");
                    course.showResult(student);
                }
            }
            else if (panel == 2)
            {
                showTeacherMenu();
                cin >> choice;
                if (choice == 1)
                {
                    system("cls");
                    string name, id, department;
                    cout << "Enter teacher name - ";
                    cin >> name;
                    cout << "Enter teacher ID - ";
                    cin >> id;
                    cout << "Enter teacher department - ";
                    cin >> department;
                    teacher.addTeacher(name, id, department);
                }
                else if (choice == 2)
                {
                    system("cls");
                    teacher.showTeachers();
                }
                else if (choice == 3)
                {
                    system("cls");
                    teacher.searchTeacher();
                }
                else if (choice == 4)
                {
                    system("cls");
                    teacher.updateTeacher();
                }
                else if (choice == 5)
                {
                    system("cls");
                    teacher.deleteTeacher();
                }
                else if (choice == 6)
                {
                    system("cls");
                    teacher.resultProcessing(course, student);
                }
            }
        }
    }
}