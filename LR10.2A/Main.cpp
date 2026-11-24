// main.cpp
// < Прокопчук Юлія >
// Лабораторна робота № 10.2 А
// Впорядкування та бінарний пошук в масиві структур 
// Варіант 24

#include <iostream>
#include "Students.h" // підключаємо інтерфейс модуля
using namespace std;

int main()
{
    int N = ReadInt("Enter number of students N (1-100): ", 1, 100); // кількість студентів
    cout << endl;

    Student* students = new Student[N]; // динамічний масив структур
    int* I = nullptr; // індексний масив (поки не побудований)
    bool sorted = false; // чи масив фізично впорядкований

    int menuItem; // вибраний пункт меню
    do
    {
        cout << endl;
        cout << "Choose an action:" << endl << endl;
        cout << " [1] - enter data from keyboard" << endl;
        cout << " [2] - print data table" << endl;
        cout << " [3] - physical sort (course, average, surname descending)" << endl;
        cout << " [4] - build index array and print index-sorted table" << endl;
        cout << " [5] - binary search in physically sorted array" << endl;
        cout << " [6] - binary search in index-sorted array" << endl << endl;
        cout << " [0] - exit" << endl << endl;
        menuItem = ReadInt("Enter value: ", 0, 6); // контроль помилок меню
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(students, N);
            sorted = false; // дані змінилися - попереднє впорядкування недійсне
            delete[] I;
            I = nullptr;
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            Sort(students, N);
            sorted = true;
            delete[] I; // порядок елементів змінився - старий індексний масив недійсний
            I = nullptr;
            cout << "Array is physically sorted." << endl;
            break;
        case 4:
            delete[] I; // видаляємо старий індексний масив, якщо він був
            I = IndexSort(students, N);
            PrintIndexSorted(students, I, N);
            break;
        case 5:
        case 6:
            if (menuItem == 5 && !sorted) // для пошуку масив має бути впорядкований
                cout << "Array is not sorted. Use item [3] first." << endl;
            else if (menuItem == 6 && I == nullptr)
                cout << "Index array is not built. Use item [4] first." << endl;
            else
            {
                string surname = ReadSurname("Enter surname: ");
                int course = ReadInt("Enter course (1-6): ", 1, 6);
                double average = ReadDouble("Enter average grade (1-5, two decimals, e.g. 4.67): ", 1, 5);
                int pos; // знайдена позиція
                if (menuItem == 5)
                    pos = BinSearch(students, N, surname, course, average);
                else
                    pos = IndexBinSearch(students, I, N, surname, course, average);

                if (pos == -1)
                    cout << "Student NOT found." << endl;
                else
                    cout << "Student found: row #" << pos + 1 << " of the sorted table." << endl;
            }
            break;
        }
    } while (menuItem != 0);

    delete[] I; // звільняємо пам'ять
    delete[] students;
    return 0;
}
