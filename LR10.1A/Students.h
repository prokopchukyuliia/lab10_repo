#pragma once // захист від повторного підключення файлу
#include <string>

// перелік спеціальностей
enum Specialty
{
    COMPUTER_SCIENCE,     // Комп'ютерні науки
    MATH_ECONOMICS,       // Математика та економіка
    PHYSICS_INFORMATICS,  // Фізика та інформатика
    INFORMATICS,          // Інформатика
    LABOR_TRAINING        // Трудове навчання
};

// структура з даними про одного студента
struct Student
{
    std::string surname;                    // прізвище
    int course = 0;                         // курс (ціле число)
    Specialty specialty = COMPUTER_SCIENCE; // спеціальність (перелік)
    int physics = 0;                        // оцінка з фізики
    int math = 0;                           // оцінка з математики
    int informatics = 0;                    // оцінка з інформатики
};

// заповнює масив студентів даними з клавіатури
void Create(Student* students, const int N);

// виводить масив студентів на екран у вигляді таблиці
void Print(const Student* students, const int N);

// повертає кількість студентів, які вчаться на "відмінно" (всі оцінки 5)
int CountExcellent(const Student* students, const int N);

// повертає процент студентів, які отримали з фізики оцінку 5
double PercentPhysics5(const Student* students, const int N);
