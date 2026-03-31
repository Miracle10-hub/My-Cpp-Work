#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Student {
private:
    string name;
    int id;
    int grades[3][2];
    string subjects[3] = {"Math", "Science", "English"};

public:
    void inputDetails() {
        cout << "Enter name: ";
        getline(cin, name);
        if (name.empty()) throw invalid_argument("Name cannot be empty");

        cout << "Enter ID: ";
        cin >> id;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                cout << subjects[i] << " Exam " << j+1 << ": ";
                cin >> grades[i][j];
                if (grades[i][j] < 0 || grades[i][j] > 100)
                    throw out_of_range("Grade must be between 0 and 100");
            }
        }
        cin.ignore();
    }

    void displayDetails() const {
        cout << "\nName: " << name << " | ID: " << id << endl;
        for (int i = 0; i < 3; i++) {
            cout << subjects[i] << ": ";
            for (int j = 0; j < 2; j++) {
                cout << grades[i][j] << " ";
            }
            cout << endl;
        }
    }

    double calculateAverage() const {
        return totalGrades() / 6.0;
    }

    int totalGrades() const {
        int sum = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++)
                sum += grades[i][j];
        return sum;
    }

    int getId() const { return id; }

    void updateGrades() {
        cout << "Updating grades for " << name << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                cout << "New " << subjects[i] << " Exam " << j+1 << ": ";
                cin >> grades[i][j];
            }
        }
    }

    int getSubjectTotal(int subjectIndex) const {
        return grades[subjectIndex][0] + grades[subjectIndex][1];
    }
};

int main() {
    vector<Student> students;
    int n;

    cout << "Enter number of students: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        Student s;
        try {
            cout << "\nStudent " << i+1 << endl;
            s.inputDetails();
            students.push_back(s);
        } catch (exception &e) {
            cout << "Error: " << e.what() << endl;
            i--;
        }
    }

    int choice;
    do {
        cout << "\nMenu:\n1. Display all\n2. Show averages\n3. Highest total\n4. Update grades\n5. Class subject averages\n6. Exit\nChoice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                sort(students.begin(), students.end(), [](Student &a, Student &b){
                    return a.calculateAverage() > b.calculateAverage();
                });
                for (auto &s : students) s.displayDetails();
                break;

            case 2:
                for (auto &s : students)
                    cout << "Average: " << s.calculateAverage() << endl;
                break;

            case 3: {
                auto maxStudent = max_element(students.begin(), students.end(),
                    [](Student &a, Student &b){
                        return a.totalGrades() < b.totalGrades();
                    });
                if (maxStudent != students.end())
                    maxStudent->displayDetails();
                break;
            }

            case 4: {
                int searchId;
                cout << "Enter ID: ";
                cin >> searchId;
                for (auto &s : students) {
                    if (s.getId() == searchId) {
                        s.updateGrades();
                    }
                }
                break;
            }

            case 5: {
                for (int i = 0; i < 3; i++) {
                    double total = 0;
                    for (auto &s : students)
                        total += s.getSubjectTotal(i);
                    cout << "Subject " << i+1 << " average: " << total / (students.size()*2) << endl;
                }
                break;
            }
        }

    } while(choice != 6);

    return 0;
}
