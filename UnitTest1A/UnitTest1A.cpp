#include "pch.h"
#include "CppUnitTest.h"
#include "../LR10.1A/Students.h"
#include "../LR10.1A/Students.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        // ---------- CountExcellent ----------

        TEST_METHOD(CountExcellent_Some) // є відмінники і не відмінники
        {
            Student s[] = {
                { "Ivanenko", 1, COMPUTER_SCIENCE, 5, 5, 5 }, // відмінник
                { "Petrenko", 2, MATH_ECONOMICS, 5, 4, 5 },   // не відмінник
                { "Kovalenko", 1, LABOR_TRAINING, 3, 5, 5 }   // не відмінник
            };
            Assert::AreEqual(1, CountExcellent(s, 3));
        }

        TEST_METHOD(CountExcellent_None) // немає відмінників
        {
            Student s[] = {
                { "Hrytsenko", 1, COMPUTER_SCIENCE, 4, 4, 4 },
                { "Savchuk", 2, PHYSICS_INFORMATICS, 3, 5, 5 },
                { "Melnyk", 3, INFORMATICS, 4, 5, 4 }
            };
            Assert::AreEqual(0, CountExcellent(s, 3));
        }

        TEST_METHOD(CountExcellent_All) // всі відмінники
        {
            Student s[] = {
                { "Boyko", 1, INFORMATICS, 5, 5, 5 },
                { "Tkachenko", 2, LABOR_TRAINING, 5, 5, 5 },
                { "Shevchenko", 3, MATH_ECONOMICS, 5, 5, 5 }
            };
            Assert::AreEqual(3, CountExcellent(s, 3));
        }

        TEST_METHOD(CountExcellent_OnlyPhysics5) // п'ятірка лише з фізики - не відмінник
        {
            Student s[] = { { "Lysenko", 3, PHYSICS_INFORMATICS, 5, 4, 4 } };
            Assert::AreEqual(0, CountExcellent(s, 1));
        }

        TEST_METHOD(CountExcellent_EmptyArray) // порожній масив
        {
            Student s[1]; // N = 0, тому елементи не опрацьовуються
            Assert::AreEqual(0, CountExcellent(s, 0));
        }

        // ---------- PercentPhysics5 ----------

        TEST_METHOD(PercentPhysics5_Some) // 2 з 3 мають 5 з фізики
        {
            Student s[] = {
                { "Ivanenko", 1, COMPUTER_SCIENCE, 5, 5, 5 },
                { "Petrenko", 2, MATH_ECONOMICS, 5, 4, 5 },
                { "Kovalenko", 1, LABOR_TRAINING, 3, 5, 5 }
            };
            Assert::AreEqual(66.6667, PercentPhysics5(s, 3), 0.001); // допустима похибка 0.001
        }

        TEST_METHOD(PercentPhysics5_None) // ніхто не має 5 з фізики
        {
            Student s[] = {
                { "Hrytsenko", 1, COMPUTER_SCIENCE, 4, 4, 4 },
                { "Savchuk", 2, PHYSICS_INFORMATICS, 3, 5, 5 },
                { "Melnyk", 3, INFORMATICS, 4, 5, 4 }
            };
            Assert::AreEqual(0.0, PercentPhysics5(s, 3), 0.001);
        }

        TEST_METHOD(PercentPhysics5_All) // всі мають 5 з фізики
        {
            Student s[] = {
                { "Boyko", 1, INFORMATICS, 5, 5, 5 },
                { "Tkachenko", 2, LABOR_TRAINING, 5, 4, 3 },
                { "Shevchenko", 3, MATH_ECONOMICS, 5, 3, 3 }
            };
            Assert::AreEqual(100.0, PercentPhysics5(s, 3), 0.001);
        }

        TEST_METHOD(PercentPhysics5_EmptyArray) // порожній масив - захист від ділення на нуль
        {
            Student s[1];
            Assert::AreEqual(0.0, PercentPhysics5(s, 0), 0.001);
        }
    };
}
