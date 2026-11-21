#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name, phone;
    int id;
public:
    Person(string n, int i, string p) : name(n), phone(p), id(i) {}
    void showPerson() const {
        cout << "Name: " << name << '\n' << "ID: " << id << '\n'
             << "Phone: " << phone << '\n';
    }
};

class Student : virtual public Person {
protected:
    string programme;
    double cgpa;
public:
    Student(string n, int i, string p, string prog, double g)
        : Person(n, i, p), programme(prog), cgpa(g) {}
};

class Staff : virtual public Person {
protected:
    string department;
    double salary;
public:
    Staff(string n, int i, string p, string dept, double s)
        : Person(n, i, p), department(dept), salary(s) {}
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int i, string p, string prog, double g,
                      string dept, double s)
        : Person(n, i, p), Student(n, i, p, prog, g), Staff(n, i, p, dept, s) {}
    void display() const {
        showPerson();
        cout << "Programme: " << programme << '\n' << "CGPA: " << cgpa << '\n'
             << "Department: " << department << '\n' << "Salary: " << salary << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(string n, int i, string p, string prog, double g, double f)
        : Person(n, i, p), Student(n, i, p, prog, g), fellowship(f) {}
    void display() const {
        showPerson();
        cout << "Programme: " << programme << '\n' << "CGPA: " << cgpa << '\n'
             << "Fellowship: " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant ta("Raju", 101, "9876543210", "CSE", 8.5, "Computer Science", 25000);
    cout << "Teaching Assistant Details\n";
    ta.display();
    cout << "\nResearch Scholar Details\n";
    ResearchScholar rs("Kavya", 102, "9876501234", "PhD CSE", 9.1, 15000);
    rs.display();
}
