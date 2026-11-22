#include "pch.h"
#include "CppUnitTest.h"
#include "../LR10.1B/Students.h"
#include "../LR10.1B/Students.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1B
{
    TEST_CLASS(UnitTest1B)
    {
    public:

        // створює студента: третя оцінка потрапляє в поле об'єднання, яке відповідає спеціальності
        static Student Make(const std::string& surname, Specialty specialty,
            int physics, int math, int third)
        {
            Student s; // усі поля мають початкові значення
            s.surname = surname;
            s.specialty = specialty;
            s.physics = physics;
            s.math = math;
            switch (specialty)
            {
            case COMPUTER_SCIENCE:
                s.programming = third;
                break;
            case INFORMATICS:
                s.numerical = third;
                break;
            default:
                s.pedagogy = third;
            }
            return s;
        }

        // ---------- CountExcellent ----------

        TEST_METHOD(CountExcellent_Some) // є відмінники і не відмінники
        {
            Student s[] = {
                Make("Ivanenko", COMPUTER_SCIENCE, 5, 5, 5),  // відмінник (програмування)
                Make("Petrenko", MATH_ECONOMICS, 5, 4, 5),    // не відмінник
                Make("Shevchenko", INFORMATICS, 5, 5, 5),     // відмінник (чисельні методи)
                Make("Melnyk", COMPUTER_SCIENCE, 5, 5, 4)     // не відмінник (програмування 4)
            };
            Assert::AreEqual(2, CountExcellent(s, 4));
        }

        TEST_METHOD(CountExcellent_PedagogyThirdGrade) // для інших спеціальностей третя оцінка - педагогіка
        {
            Student s[] = {
                Make("Boyko", LABOR_TRAINING, 5, 5, 5),       // відмінник
                Make("Tkachenko", PHYSICS_INFORMATICS, 5, 5, 4) // не відмінник
            };
            Assert::AreEqual(1, CountExcellent(s, 2));
        }

        TEST_METHOD(CountExcellent_None) // немає відмінників
        {
            Student s[] = {
                Make("Hrytsenko", COMPUTER_SCIENCE, 4, 4, 4),
                Make("Savchuk", INFORMATICS, 3, 5, 5),
                Make("Lysenko", MATH_ECONOMICS, 5, 5, 3)
            };
            Assert::AreEqual(0, CountExcellent(s, 3));
        }

        TEST_METHOD(CountExcellent_EmptyArray) // порожній масив
        {
            Student s[1];
            Assert::AreEqual(0, CountExcellent(s, 0));
        }

        // ---------- PercentPhysics5 ----------

        TEST_METHOD(PercentPhysics5_Some) // 2 з 3 мають 5 з фізики
        {
            Student s[] = {
                Make("Ivanenko", COMPUTER_SCIENCE, 5, 5, 5),
                Make("Petrenko", MATH_ECONOMICS, 5, 4, 5),
                Make("Kovalenko", INFORMATICS, 3, 5, 5)
            };
            Assert::AreEqual(66.6667, PercentPhysics5(s, 3), 0.001); // допустима похибка 0.001
        }

        TEST_METHOD(PercentPhysics5_None) // ніхто не має 5 з фізики
        {
            Student s[] = {
                Make("Hrytsenko", COMPUTER_SCIENCE, 4, 4, 4),
                Make("Savchuk", LABOR_TRAINING, 3, 5, 5)
            };
            Assert::AreEqual(0.0, PercentPhysics5(s, 2), 0.001);
        }

        TEST_METHOD(PercentPhysics5_All) // всі мають 5 з фізики
        {
            Student s[] = {
                Make("Boyko", INFORMATICS, 5, 5, 5),
                Make("Tkachenko", LABOR_TRAINING, 5, 4, 3)
            };
            Assert::AreEqual(100.0, PercentPhysics5(s, 2), 0.001);
        }

        TEST_METHOD(PercentPhysics5_EmptyArray) // порожній масив - захист від ділення на нуль
        {
            Student s[1];
            Assert::AreEqual(0.0, PercentPhysics5(s, 0), 0.001);
        }
    };
}
