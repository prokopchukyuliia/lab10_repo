#include "Students.h"
#include <iostream>
#include <iomanip>
using namespace std;

// повертає назву спеціальності для виводу в таблицю
static string SpecialtyToString(const Specialty specialty)
{
    switch (specialty)
    {
    case COMPUTER_SCIENCE:
        return "Computer Science";
    case MATH_ECONOMICS:
        return "Math and Economics";
    case PHYSICS_INFORMATICS:
        return "Physics and Informatics";
    case INFORMATICS:
        return "Informatics";
    default:
        return "Labor Training";
    }
}

// зчитує оцінку з клавіатури, поки користувач не введе число від 1 до 5
static int ReadGrade(const string& subject)
{
    int grade; // оцінка, яку вводить користувач
    do
    {
        cout << "  " << subject << " grade (1-5): ";
        cin >> grade;
        if (grade < 1 || grade > 5) // максимальна оцінка - 5
            cout << "  Error: grade must be from 1 to 5!" << endl;
    } while (grade < 1 || grade > 5); // повторюємо, доки оцінка некоректна
    return grade;
}

// повертає третю оцінку студента (поле об'єднання залежить від спеціальності)
static int ThirdGrade(const Student& s)
{
    switch (s.specialty)
    {
    case COMPUTER_SCIENCE:
        return s.programming;
    case INFORMATICS:
        return s.numerical;
    default:
        return s.pedagogy;
    }
}

void Create(Student* students, const int N)
{
    for (int i = 0; i < N; i++) // проходимо по всіх студентах
    {
        int specialty; // тимчасова змінна, бо перелік не можна читати через cin
        cout << "Student #" << i + 1 << ":" << endl;
        cout << "  surname: ";
        cin >> students[i].surname;
        cout << "  course: ";
        cin >> students[i].course;
        cout << "  specialty (0 - Computer Science, 1 - Math and Economics, "
            << "2 - Physics and Informatics, 3 - Informatics, 4 - Labor Training): ";
        cin >> specialty;
        students[i].specialty = (Specialty)specialty; // число -> елемент переліку
        students[i].physics = ReadGrade("physics"); // оцінка з фізики
        students[i].math = ReadGrade("math"); // оцінка з математики

        // третю оцінку записуємо в те поле об'єднання, яке відповідає спеціальності
        switch (students[i].specialty)
        {
        case COMPUTER_SCIENCE:
            students[i].programming = ReadGrade("programming");
            break;
        case INFORMATICS:
            students[i].numerical = ReadGrade("numerical methods");
            break;
        default:
            students[i].pedagogy = ReadGrade("pedagogy");
        }
        cout << endl;
    }
}

void Print(const Student* students, const int N)
{
    cout << "                                         STUDENTS TABLE" << endl; // заголовок таблиці
    cout << "=====================================================================================================================" << endl;
    cout << "| No | Surname         | Course | Specialty               | Physics | Math | Programming | Num. methods | Pedagogy |" << endl; // шапка
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) // один рядок таблиці - один студент
    {
        cout << "| " << setw(2) << right << i + 1 << " " // порядковий номер
            << "| " << setw(15) << left << students[i].surname << " " // прізвище
            << "| " << setw(6) << right << students[i].course << " " // курс
            << "| " << setw(23) << left << SpecialtyToString(students[i].specialty) << " " // спеціальність
            << "| " << setw(7) << right << students[i].physics << " " // фізика
            << "| " << setw(4) << right << students[i].math << " "; // математика

        // у рядку заповнена лише одна з трьох останніх клітинок - залежно від спеціальності
        cout << "| " << setw(11) << right;
        if (students[i].specialty == COMPUTER_SCIENCE)
            cout << students[i].programming;
        else
            cout << "";
        cout << " | " << setw(12) << right;
        if (students[i].specialty == INFORMATICS)
            cout << students[i].numerical;
        else
            cout << "";
        cout << " | " << setw(8) << right;
        if (students[i].specialty != COMPUTER_SCIENCE && students[i].specialty != INFORMATICS)
            cout << students[i].pedagogy;
        else
            cout << "";
        cout << " |" << endl;
    }
    cout << "=====================================================================================================================" << endl;
    cout << endl;
}

int CountExcellent(const Student* students, const int N)
{
    int k = 0; // лічильник відмінників
    for (int i = 0; i < N; i++) // послідовний пошук по масиву
    {
        // студент відмінник, якщо всі три оцінки дорівнюють 5
        if (students[i].physics == 5 && students[i].math == 5 && ThirdGrade(students[i]) == 5)
            k++;
    }
    return k;
}

double PercentPhysics5(const Student* students, const int N)
{
    if (N == 0) // захист від ділення на нуль
        return 0;

    int k = 0; // лічильник студентів з оцінкою 5 з фізики
    for (int i = 0; i < N; i++) // послідовний пошук по масиву
    {
        if (students[i].physics == 5)
            k++;
    }
    return 100.0 * k / N; // частка від загальної кількості у відсотках
}
