#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double e;
    cout << "Введите точность: ";
    if (!(cin >> e) || e <=0) {
        cout << "Некорректный ввод точности!" << endl;
        return 1;
    }

    cout << fixed << setprecision(10);

    {
        double p2 = 1.0, q2 = 1.0;
        double p1 = 3.0, q1 = 2.0;

        double x_prev = p2 / q2;
        double x_curr = p1 / q1;
        int steps = 1;

        while (abs(x_curr - x_prev) >= e) {
            double p = 2.0 * p1 + p2;
            double q = 2.0 * q1 + q2;

            x_prev = x_curr;
            x_curr = p / q;

            p2 = p1; p1 = p;
            q2 = q1; q1 = q;
            steps ++;
        }
        cout << "1) while:  Result = " << x_curr << " | Шагов: " << steps << endl;
    }

    {
        double p2 = 1.0, q2 = 1.0;
        double p1 = 3.0, q1 = 2.0;

        double x_prev = p2 / q2;
        double x_curr = p1 / q1;
        int steps =1;

        do {
            if (abs(x_curr - x_prev) < e) break;

            double p = 2.0 * p1 + p2;
            double q = 2.0 * q1 + q2;

            x_prev = x_curr;
            x_curr = p /q;

            p2 = p1; p1 = p;
            q2 = q1; q1 = q;
            steps ++;
        } while (abs(x_curr - x_prev) >= e);

        cout << "2) do while: Result = " << x_curr << "| Шагов: " << steps << endl;
    }

    {
        double p2 = 1.0, q2 = 1.0;
        double p1 = 3.0, q1 = 2.0;

        double x_prev = p2 / q2;
        double x_curr = p1 / q1;
        int steps = 1;

        for ( ; abs(x_curr - x_prev) >= e; steps++) {
            double p = 2.0 * p1 + p2;
            double q = 2.0 * q1 + q2;

            x_prev = x_curr;
            x_curr = p / q;

            p2 = p1; p1 = p;
            q2 = q1; q1 = q;
        }
        cout << "3) for: Result = " << x_curr << "| Шагов: " << steps << endl;
    }

    cout << "Точное значение функции sqrt(2) = " << sqrt(2.0) << endl;

    return 0;
}
