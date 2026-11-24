#pragma once 
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
    union // третя оцінка залежить від спеціальності (всі поля в одній пам'яті)
    {
        int programming = 0; // програмування - для "Комп'ютерні науки"
        int numerical;       // чисельні методи - для "Інформатика"
        int pedagogy;        // педагогіка - для всіх інших спеціальностей
    };
};

// заповнює масив студентів даними з клавіатури
void Create(Student* students, const int N);

// виводить масив студентів на екран у вигляді таблиці
void Print(const Student* students, const int N);

// повертає кількість студентів, які вчаться на "відмінно" (всі три оцінки 5)
int CountExcellent(const Student* students, const int N);

// повертає процент студентів, які отримали з фізики оцінку 5
double PercentPhysics5(const Student* students, const int N);