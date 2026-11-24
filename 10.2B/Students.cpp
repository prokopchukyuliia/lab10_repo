#include "Students.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// ---------- допоміжні функції (видимі лише в цьому файлі) ----------

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

// порівнює два середні бали: -1 (x < y), 0 (рівні), 1 (x > y)
static int CompareAverage(const double x, const double y)
{
    if (fabs(x - y) < 0.005) // рівними вважаємо числа, що відрізняються менше ніж на 0.005
        return 0;
    return x < y ? -1 : 1;
}

// порівнює двох студентів за курсом, а потім за середнім балом
static int CompareCourseAverage(const Student& a, const Student& b)
{
    if (a.course != b.course)
        return a.course < b.course ? -1 : 1;
    return CompareAverage(Average(a), Average(b));
}

// порівнює студента із шуканими курсом та середнім балом
static int CompareWithKey(const Student& s, const int course, const double average)
{
    if (s.course != course)
        return s.course < course ? -1 : 1;
    return CompareAverage(Average(s), average);
}

// виводить заголовок та шапку таблиці
static void PrintTableHeader()
{
    cout << "                                         STUDENTS TABLE" << endl; // заголовок таблиці
    cout << "=====================================================================================================================" << endl;
    cout << "| No | Surname         | Course | Specialty               | Physics | Math | Programming | Num. methods | Pedagogy |" << endl; // шапка
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
}

// виводить один рядок таблиці (number - порядковий номер у таблиці)
static void PrintTableRow(const int number, const Student& s)
{
    cout << "| " << setw(2) << right << number << " " // порядковий номер
        << "| " << setw(15) << left << s.surname << " " // прізвище
        << "| " << setw(6) << right << s.course << " " // курс
        << "| " << setw(23) << left << SpecialtyToString(s.specialty) << " " // спеціальність
        << "| " << setw(7) << right << s.physics << " " // фізика
        << "| " << setw(4) << right << s.math << " "; // математика

    // у рядку заповнена лише одна з трьох останніх клітинок - залежно від спеціальності
    cout << "| " << setw(11) << right;
    if (s.specialty == COMPUTER_SCIENCE)
        cout << s.programming;
    else
        cout << "";
    cout << " | " << setw(12) << right;
    if (s.specialty == INFORMATICS)
        cout << s.numerical;
    else
        cout << "";
    cout << " | " << setw(8) << right;
    if (s.specialty != COMPUTER_SCIENCE && s.specialty != INFORMATICS)
        cout << s.pedagogy;
    else
        cout << "";
    cout << " |" << endl;
}

// виводить нижню лінію таблиці
static void PrintTableFooter()
{
    cout << "=====================================================================================================================" << endl;
    cout << endl;
}

// ---------- введення з контролем помилок ----------

int ReadInt(const string& prompt, const int min, const int max)
{
    int value; // число, яке вводить користувач
    bool ok; // чи коректне введення
    do
    {
        cout << prompt;
        cin >> value;
        ok = !cin.fail() && value >= min && value <= max; // число введено і воно в межах
        if (cin.fail()) // введено не число
            cin.clear(); // скидаємо стан помилки потоку
        cin.ignore(10000, '\n'); // видаляємо з буфера решту рядка
        if (!ok)
            cout << "Error: enter an integer from " << min << " to " << max << "!" << endl;
    } while (!ok);
    return value;
}

double ReadDouble(const string& prompt, const double min, const double max)
{
    double value; // число, яке вводить користувач
    bool ok; // чи коректне введення
    do
    {
        cout << prompt;
        cin >> value;
        ok = !cin.fail() && value >= min && value <= max; // число введено і воно в межах
        if (cin.fail()) // введено не число
            cin.clear(); // скидаємо стан помилки потоку
        cin.ignore(10000, '\n'); // видаляємо з буфера решту рядка
        if (!ok)
            cout << "Error: enter a number from " << min << " to " << max << "!" << endl;
    } while (!ok);
    return value;
}

string ReadSurname(const string& prompt)
{
    string surname; // прізвище, яке вводить користувач
    cout << prompt;
    cin >> surname;
    cin.ignore(10000, '\n'); // видаляємо з буфера решту рядка
    return surname;
}

// ---------- робота з масивом ----------

void Create(Student* students, const int N)
{
    for (int i = 0; i < N; i++) // проходимо по всіх студентах
    {
        cout << "Student #" << i + 1 << ":" << endl;
        students[i].surname = ReadSurname("  surname: ");
        students[i].course = ReadInt("  course (1-6): ", 1, 6);
        students[i].specialty = (Specialty)ReadInt(
            "  specialty (0 - Computer Science, 1 - Math and Economics, "
            "2 - Physics and Informatics, 3 - Informatics, 4 - Labor Training): ", 0, 4); // число -> елемент переліку
        students[i].physics = ReadInt("  physics grade (1-5): ", 1, 5); // максимальна оцінка - 5
        students[i].math = ReadInt("  math grade (1-5): ", 1, 5);

        // третю оцінку записуємо в те поле об'єднання, яке відповідає спеціальності
        switch (students[i].specialty)
        {
        case COMPUTER_SCIENCE:
            students[i].programming = ReadInt("  programming grade (1-5): ", 1, 5);
            break;
        case INFORMATICS:
            students[i].numerical = ReadInt("  numerical methods grade (1-5): ", 1, 5);
            break;
        default:
            students[i].pedagogy = ReadInt("  pedagogy grade (1-5): ", 1, 5);
        }
        cout << endl;
    }
}

void Print(const Student* students, const int N)
{
    PrintTableHeader();
    for (int i = 0; i < N; i++) // один рядок таблиці - один студент
        PrintTableRow(i + 1, students[i]);
    PrintTableFooter();
}

double Average(const Student& student)
{
    return (student.physics + student.math + ThirdGrade(student)) / 3.0; // 3.0, щоб ділення було дійсним
}

void Sort(Student* students, const int N)
{
    Student tmp; // для обміну елементів
    for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            int c = CompareCourseAverage(students[i1], students[i1 + 1]); // порівнюємо курс і середній бал
            // міняємо місцями, якщо перший елемент має стояти після другого:
            // більший курс, або більший середній бал, або (рівні) - менше прізвище (спадання)
            if (c > 0 || (c == 0 && students[i1].surname < students[i1 + 1].surname))
            {
                tmp = students[i1];
                students[i1] = students[i1 + 1];
                students[i1 + 1] = tmp;
            }
        }
}

int* IndexSort(const Student* students, const int N)
{
    int* I = new int[N]; // створили індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i; // заповнили його початковими даними

    for (int i = 1; i < N; i++) // сортуємо масив індексів методом вставки
    {
        int value = I[i]; // індекс, який вставляємо
        int j = i - 1;
        // зсуваємо вправо індекси, які мають стояти після value
        while (j >= 0)
        {
            int c = CompareCourseAverage(students[I[j]], students[value]);
            if (c > 0 || (c == 0 && students[I[j]].surname > students[value].surname)) // прізвище - за зростанням
            {
                I[j + 1] = I[j];
                j--;
            }
            else
                break;
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(const Student* students, const int* I, const int N)
{
    PrintTableHeader();
    for (int i = 0; i < N; i++) // замість students[i] беремо students[I[i]]
        PrintTableRow(i + 1, students[I[i]]);
    PrintTableFooter();
}

int BinSearch(const Student* students, const int N,
    const string& surname, const int course, const double average)
{
    int L = 0, R = N - 1; // межі пошуку
    while (L <= R)
    {
        int m = (L + R) / 2; // середній елемент
        int c = CompareWithKey(students[m], course, average); // порівнюємо курс і середній бал
        if (c == 0)
        {
            if (students[m].surname == surname) // знайшли
                return m;
            if (students[m].surname > surname) // прізвища впорядковані за спаданням,
                L = m + 1; // тому більше прізвище стоїть раніше - шукаємо правіше
            else
                R = m - 1;
        }
        else if (c < 0) // елемент "менший" за шуканий - шукаємо правіше
            L = m + 1;
        else
            R = m - 1;
    }
    return -1; // не знайшли
}

int IndexBinSearch(const Student* students, const int* I, const int N,
    const string& surname, const int course, const double average)
{
    int L = 0, R = N - 1; // межі пошуку
    while (L <= R)
    {
        int m = (L + R) / 2; // середній елемент
        const Student& s = students[I[m]]; // доступ до елемента через індексний масив
        int c = CompareWithKey(s, course, average); // порівнюємо курс і середній бал
        if (c == 0)
        {
            if (s.surname == surname) // знайшли
                return m;
            if (s.surname < surname) // прізвища впорядковані за зростанням -
                L = m + 1; // менше прізвище стоїть раніше - шукаємо правіше
            else
                R = m - 1;
        }
        else if (c < 0) // елемент "менший" за шуканий - шукаємо правіше
            L = m + 1;
        else
            R = m - 1;
    }
    return -1; // не знайшли
}
