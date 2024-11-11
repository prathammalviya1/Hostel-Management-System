#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
struct Student
{
    int registration_number;
    float cgpa;
    vector<int> preferences;
};
unordered_map<int, int> seater_types = {
    {1, 10},
    {2, 20},
    {3, 30},
    {4, 40},
    {5, 50},
    {6, 60} // doormetry
};
bool isValidPreference(int preference)
{
    return seater_types.find(preference) != seater_types.end();
}
bool compareStudents(const Student &a, const Student &b)
{
    if (a.cgpa != b.cgpa)
        return a.cgpa > b.cgpa;
    return a.registration_number < b.registration_number;
}
void perform_hostel_allotment(vector<Student> &students)
{
    sort(students.begin(), students.end(), compareStudents);
    for (const auto &student : students)
    {
        bool roomAllocated = false;
        for (const auto &preference : student.preferences)
        {
            if (isValidPreference(preference) &&
                seater_types[preference] > 0)
            {
                cout << "Registration Number: " << student.registration_number << "\tCGPA: " << student.cgpa << "\t";
                cout << "Allocated Room: " << preference << " seater"
                     << endl;
                seater_types[preference]--;
                roomAllocated = true;

                break;
            }
        }
        if (!roomAllocated)
        {
            cout << "Registration Number: " << student.registration_number << "\tCGPA: " << student.cgpa << "\t";
            cout << "Room Not Allocated" << endl;
        }
    }
}
int main()
{
    int num_students;
    cout << "Enter the number of students: ";
    cin >> num_students;
    vector<Student> students(num_students);
    for (int i = 0; i < num_students; i++)
    {
        cout << "Enter student registration number: ";
        cin >> students[i].registration_number;
        cout << "Enter student CGPA: ";
        cin >> students[i].cgpa;
        cout << "Enter 4 preferences for seater type (1-5 for seater types, 6 for doormetry):" << endl;
        for (int j = 0; j < 4; j++)
        {

            int preference;
            cin >> preference;
            if (!isValidPreference(preference))
            {
                cout << "Invalid preference: " << preference << " is not a seater type" << endl;
                return 1;
            }
            students[i].preferences.push_back(preference);
        }
    }
    perform_hostel_allotment(students);

    return 0;
}