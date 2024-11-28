#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;
    int age;
    string address;

public:
    Person(string n, int a, string addr) : name(n), age(a), address(addr) {}

    virtual void displayDetails()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Address: " << address << endl;
    }
};

class Student : public Person
{
private:
    string studentID;
    int grades[5];
    int numGrades;

public:
    Student(string n, int a, string addr, string id) : Person(n, a, addr), studentID(id), numGrades(0) {}

    void addGrade(int grade)
    {
        if (numGrades < 5)
        {
            grades[numGrades] = grade;
            numGrades++;
        }
    }

    void calculateGPA()
    {
        if (numGrades == 0)
        {
            cout << "GPA: 0.0" << endl;
            return;
        }

        int sum = 0;
        for (int i = 0; i < numGrades; i++)
        {
            sum += grades[i];
        }
        double gpa = static_cast<double>(sum) / numGrades;
        cout << "GPA: " << gpa << endl;
    }

    void displayDetails() override
    {
        Person::displayDetails();
        cout << "Student ID: " << studentID << endl;
        cout << "Grades: ";
        for (int i = 0; i < numGrades; i++)
        {
            cout << grades[i] << " ";
        }
        cout << endl;
        calculateGPA();
    }
};

class Payable
{
public:
    virtual double calculateSalary() = 0;
};

class Teacher : public Person, public Payable
{
private:
    string teacherID;
    string subject;
    int classesTaught;
    double ratePerClass;

public:
    Teacher(string n, int a, string addr, string id, string sub, int classes, double rate)
        : Person(n, a, addr), teacherID(id), subject(sub), classesTaught(classes), ratePerClass(rate) {}

    void assignGrade(Student &student, int grade)
    {
        student.addGrade(grade);
    }

    double calculateSalary() override
    {
        return classesTaught * ratePerClass;
    }

    void displayDetails() override
    {
        Person::displayDetails();
        cout << "Teacher ID: " << teacherID << endl;
        cout << "Subject: " << subject << endl;
        cout << "Classes Taught: " << classesTaught << endl;
        cout << "Rate per Class: " << ratePerClass << endl;
        cout << "Total Salary: " << calculateSalary() << endl;
    }
};

int main()
{
    string teacherName, teacherAddress, teacherID, subject;
    int teacherAge, teacherClassesTaught;
    double teacherRatePerClass;

    cout << "Enter Teacher Name: ";
    getline(cin, teacherName);
    cout << "Enter Teacher Age: ";
    cin >> teacherAge;
    cin.ignore();
    cout << "Enter Teacher Address: ";
    getline(cin, teacherAddress);
    cout << "Enter Teacher ID: ";
    getline(cin, teacherID);
    cout << "Enter Teacher Subject: ";
    getline(cin, subject);
    cout << "Enter Number of Classes Taught: ";
    cin >> teacherClassesTaught;
    cout << "Enter Rate per Class: ";
    cin >> teacherRatePerClass;

    Teacher teacher(teacherName, teacherAge, teacherAddress, teacherID, subject, teacherClassesTaught, teacherRatePerClass);

    string studentName, studentAddress, studentID;
    int studentAge, grade;

    cout << "\nEnter Student 1 Name: ";
    cin.ignore();
    getline(cin, studentName);
    cout << "Enter Student 1 Age: ";
    cin >> studentAge;
    cin.ignore();
    cout << "Enter Student 1 Address: ";
    getline(cin, studentAddress);
    cout << "Enter Student 1 ID: ";
    getline(cin, studentID);
    Student student1(studentName, studentAge, studentAddress, studentID);

    cout << "Enter grades for Student 1 (up to 5 grades):" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter grade " << i + 1 << ": ";
        cin >> grade;
        student1.addGrade(grade);
    }

    cout << "\nEnter Student 2 Name: ";
    cin.ignore();
    getline(cin, studentName);
    cout << "Enter Student 2 Age: ";
    cin >> studentAge;
    cin.ignore();
    cout << "Enter Student 2 Address: ";
    getline(cin, studentAddress);
    cout << "Enter Student 2 ID: ";
    getline(cin, studentID);
    Student student2(studentName, studentAge, studentAddress, studentID);

    cout << "Enter grades for Student 2 (up to 5 grades):" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter grade " << i + 1 << ": ";
        cin >> grade;
        student2.addGrade(grade);
    }

    teacher.assignGrade(student1, 95);
    teacher.assignGrade(student2, 85);

    cout << "\nTeacher Details:" << endl;
    teacher.displayDetails();
    cout << endl;

    cout << "Student 1 Details:" << endl;
    student1.displayDetails();
    cout << endl;

    cout << "Student 2 Details:" << endl;
    student2.displayDetails();

    return 0;
}
