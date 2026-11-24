#pragma once
#include <string>

// перелік спеціальностей
enum Specialty
{
    COMPUTER_SCIENCE, // Комп'ютерні науки
    MATH_ECONOMICS, // Математика та економіка
    PHYSICS_INFORMATICS, // Фізика та інформатика
    INFORMATICS, // Інформатика
    LABOR_TRAINING // Трудове навчання
};

// структура з даними про одного студента
struct Student
{
    std::string surname; // прізвище
    int course = 0; // курс (ціле число)
    Specialty specialty = COMPUTER_SCIENCE; // спеціальність (перелік)
    int physics = 0; // оцінка з фізики
    int math = 0; // оцінка з математики
    int informatics = 0; // оцінка з інформатики
};

// ---------- введення з контролем помилок ----------

// зчитує ціле число з клавіатури в межах [min; max], поки введення не буде коректним
int ReadInt(const std::string& prompt, const int min, const int max);

// зчитує дійсне число з клавіатури в межах [min; max], поки введення не буде коректним
double ReadDouble(const std::string& prompt, const double min, const double max);

// зчитує прізвище (одне слово) з клавіатури
std::string ReadSurname(const std::string& prompt);

// ---------- робота з масивом ----------

// заповнює масив студентів даними з клавіатури
void Create(Student* students, const int N);

// виводить масив студентів на екран у вигляді таблиці
void Print(const Student* students, const int N);

// повертає середній бал студента (з фізики, математики та інформатики)
double Average(const Student& student);

// фізично впорядковує масив: курс - за зростанням, середній бал - за зростанням,
// прізвище - за спаданням (у зворотному до алфавітного порядку)
void Sort(Student* students, const int N);

// будує індексний масив (курс, середній бал, прізвище - за зростанням);
// масив створюється динамічно, звільняти його має викликач
int* IndexSort(const Student* students, const int N);

// виводить таблицю студентів у порядку, який задає індексний масив
void PrintIndexSorted(const Student* students, const int* I, const int N);

// бінарний пошук у ФІЗИЧНО впорядкованому масиві (після Sort);
// повертає індекс знайденого студента або -1, якщо такого немає
int BinSearch(const Student* students, const int N,
    const std::string& surname, const int course, const double average);

// бінарний пошук в ІНДЕКСНО впорядкованому масиві (після IndexSort);
// повертає позицію в індексному масиві або -1, якщо такого студента немає
int IndexBinSearch(const Student* students, const int* I, const int N,
    const std::string& surname, const int course, const double average);
