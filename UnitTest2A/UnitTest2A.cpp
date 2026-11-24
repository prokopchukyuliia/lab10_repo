#include "pch.h"
#include "CppUnitTest.h"
#include "../LR10.2A/Students.h" 
#include "../LR10.2A/Students.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2A
{
    TEST_CLASS(UnitTest2A)
    {
    public:

        // заповнює масив із 6 студентів (середні бали: 5, 4, 4, 4.67, 5, 4)
        static void Fill(Student* s)
        {
            s[0] = { "Ivanenko", 2, COMPUTER_SCIENCE, 5, 5, 5 };
            s[1] = { "Petrenko", 1, MATH_ECONOMICS, 4, 4, 4 };
            s[2] = { "Kovalenko", 2, PHYSICS_INFORMATICS, 3, 4, 5 };
            s[3] = { "Shevchenko", 1, INFORMATICS, 5, 5, 4 };
            s[4] = { "Bondarenko", 2, LABOR_TRAINING, 5, 5, 5 };
            s[5] = { "Melnyk", 1, COMPUTER_SCIENCE, 4, 4, 4 };
        }

        // ---------- Average ----------

        TEST_METHOD(Average_Value) // (5 + 5 + 4) / 3
        {
            Student s = { "A", 1, COMPUTER_SCIENCE, 5, 5, 4 };
            Assert::AreEqual(4.6667, Average(s), 0.001); // допустима похибка 0.001
        }

        // ---------- Sort (фізичне впорядкування) ----------

        TEST_METHOD(Sort_Order) // курс і середній бал - за зростанням, прізвище - за спаданням
        {
            Student s[6];
            Fill(s);
            Sort(s, 6);
            const char* expected[] = { "Petrenko", "Melnyk", "Shevchenko", "Kovalenko", "Ivanenko", "Bondarenko" };
            for (int i = 0; i < 6; i++)
                Assert::IsTrue(s[i].surname == expected[i]);
        }

        // ---------- IndexSort (індексне впорядкування) ----------

        TEST_METHOD(IndexSort_Order) // курс, середній бал, прізвище - за зростанням
        {
            Student s[6];
            Fill(s);
            int* I = IndexSort(s, 6);
            const char* expected[] = { "Melnyk", "Petrenko", "Shevchenko", "Kovalenko", "Bondarenko", "Ivanenko" };
            for (int i = 0; i < 6; i++)
                Assert::IsTrue(s[I[i]].surname == expected[i]);
            delete[] I;
        }

        TEST_METHOD(IndexSort_DoesNotChangeData) // основний масив лишається без змін
        {
            Student s[6];
            Fill(s);
            int* I = IndexSort(s, 6);
            Assert::IsTrue(s[0].surname == "Ivanenko");
            Assert::IsTrue(s[5].surname == "Melnyk");
            delete[] I;
        }

        // ---------- BinSearch (фізично впорядкований масив) ----------

        TEST_METHOD(BinSearch_Found) // шукаємо кожного студента
        {
            Student s[6];
            Fill(s);
            Sort(s, 6);
            Assert::AreEqual(0, BinSearch(s, 6, "Petrenko", 1, 4.00));
            Assert::AreEqual(1, BinSearch(s, 6, "Melnyk", 1, 4.00));
            Assert::AreEqual(2, BinSearch(s, 6, "Shevchenko", 1, 4.67));
            Assert::AreEqual(3, BinSearch(s, 6, "Kovalenko", 2, 4.00));
            Assert::AreEqual(4, BinSearch(s, 6, "Ivanenko", 2, 5.00));
            Assert::AreEqual(5, BinSearch(s, 6, "Bondarenko", 2, 5.00));
        }

        TEST_METHOD(BinSearch_NotFound) // невірне прізвище, курс або середній бал
        {
            Student s[6];
            Fill(s);
            Sort(s, 6);
            Assert::AreEqual(-1, BinSearch(s, 6, "Hrytsenko", 1, 4.00)); // немає такого прізвища
            Assert::AreEqual(-1, BinSearch(s, 6, "Petrenko", 2, 4.00)); // інший курс
            Assert::AreEqual(-1, BinSearch(s, 6, "Petrenko", 1, 5.00)); // інший середній бал
        }

        TEST_METHOD(BinSearch_EmptyArray) // порожній масив
        {
            Student s[1];
            Assert::AreEqual(-1, BinSearch(s, 0, "Petrenko", 1, 4.00));
        }

        // ---------- IndexBinSearch (індексно впорядкований масив) ----------

        TEST_METHOD(IndexBinSearch_Found) // повертається позиція в індексному масиві
        {
            Student s[6];
            Fill(s);
            int* I = IndexSort(s, 6);
            Assert::AreEqual(0, IndexBinSearch(s, I, 6, "Melnyk", 1, 4.00));
            Assert::AreEqual(1, IndexBinSearch(s, I, 6, "Petrenko", 1, 4.00));
            Assert::AreEqual(2, IndexBinSearch(s, I, 6, "Shevchenko", 1, 4.67));
            Assert::AreEqual(3, IndexBinSearch(s, I, 6, "Kovalenko", 2, 4.00));
            Assert::AreEqual(4, IndexBinSearch(s, I, 6, "Bondarenko", 2, 5.00));
            Assert::AreEqual(5, IndexBinSearch(s, I, 6, "Ivanenko", 2, 5.00));
            delete[] I;
        }

        TEST_METHOD(IndexBinSearch_NotFound) // невірне прізвище, курс або середній бал
        {
            Student s[6];
            Fill(s);
            int* I = IndexSort(s, 6);
            Assert::AreEqual(-1, IndexBinSearch(s, I, 6, "Hrytsenko", 1, 4.00));
            Assert::AreEqual(-1, IndexBinSearch(s, I, 6, "Melnyk", 3, 4.00));
            Assert::AreEqual(-1, IndexBinSearch(s, I, 6, "Ivanenko", 2, 4.50));
            delete[] I;
        }
    };
}
