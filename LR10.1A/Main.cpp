// main.cpp
// < Прокопчук Юлія >
// Лабораторна робота № 10.1 А
// Послідовний пошук в масиві структур
// Варіант 24

#include <iostream>
#include "Students.h" // підключаємо інтерфейс модуля
using namespace std;

int main()
{
    int N; // кількість студентів
    cout << "Enter number of students N: ";
    cin >> N;
    cout << endl;

    Student* students = new Student[N]; // динамічний масив структур

    Create(students, N); // введення даних
    Print(students, N);  // вивід таблиці

    int excellent = CountExcellent(students, N);       // кількість відмінників
    double percent = PercentPhysics5(students, N);     // процент з п'ятіркою з фізики

    cout << "Number of excellent students: " << excellent << endl;
    cout << "Percent of students with physics grade 5: " << percent << "%" << endl;

    delete[] students; // звільняємо пам'ять
    return 0;
}
