#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

using namespace std;

double f(double x)
{
    return (4 / (1 + x * x));
}

double simpsons()
{
    double a = 0;
    double b = 1;
    double eps = 0.0001;
    double I = eps + 1, I1 = 0;
#pragma loop(hint_parallel(2))
    for (int N = 2; (N <= 4) || (fabs(I1 - I) > eps); N *= 2)
    {
        double h, sum2 = 0, sum4 = 0, sum = 0;
        h = (b - a) / (2 * N);
        for (int i = 1; i <= 2 * N - 1; i += 2)
        {
            sum4 += f(a + h * i);
            sum2 += f(a + h * (i + 1));
        }
        sum = f(a) + 4 * sum4 + 2 * sum2 - f(b);
        I = I1;
        I1 = (h / 3) * sum;
    }
    cout << I1 << endl;
    return 0;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    // Границы интегрирования.
    double a = 0;
    double b = 1;

    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

    double n = 100;
    double h = (b - a) / n;

    cout << "Метод Симпсона:" << endl;
    cout << simpsons() << endl;
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration <double> durationTrapezia = (t2 - t1);
    cout << "Время подсчёта методом Симпсона с шагом " << n << ": " << durationTrapezia.count() << " секунд." << endl << endl;

    n = 1000;
    h = (b - a) / n;
    cout << simpsons() << endl;
    t2 = chrono::high_resolution_clock::now();
    durationTrapezia = (t2 - t1);
    cout << "Время подсчёта : " << durationTrapezia.count() << " секунд." << " " << "Число интервалов:" << n << endl << endl;

    n = 10000;
    h = (b - a) / n;
    cout << simpsons() << endl;
    t2 = chrono::high_resolution_clock::now();
    durationTrapezia = (t2 - t1);
    cout << "Время подсчёта : " << durationTrapezia.count() << " секунд." << " " << "Число интервалов:" << n << endl << endl;

    n = 100000;
    h = (b - a) / n;
    cout << simpsons() << endl;
    t2 = chrono::high_resolution_clock::now();
    durationTrapezia = (t2 - t1);
    cout << "Время подсчёта : " << durationTrapezia.count() << " секунд." << " " << "Число интервалов:" << n << endl << endl;

    n = 1000000;
    h = (b - a) / n;
    cout << simpsons() << endl;
    t2 = chrono::high_resolution_clock::now();
    durationTrapezia = (t2 - t1);
    cout << "Время подсчёта : " << durationTrapezia.count() << " секунд." << " " << "Число интервалов:" << n << endl << endl;

    return 0;
}