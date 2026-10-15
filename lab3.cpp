#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <iomanip>
#include <windows.h>

using namespace std;
using namespace chrono;

// Проверка на простоту

// Перебор от 2 до N-1
bool isPrimeBasic(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i < n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Перебор от 2 до N-1 (только нечетные, кроме 2)
bool isPrimeOdd(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i < n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Перебор от 2 до N^2
bool isPrimeSqrt(long long n) {
    if (n < 2) return false;
    long long limit = sqrt(n);
    for (long long i = 2; i <= limit; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Перебор от 2 до N^2
bool isPrimeSqrtOdd(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    long long limit = sqrt(n);
    for (long long i = 3; i <= limit; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Вычисление НОД

// Массива общих делителей с поиском максимума
long long gcdArray(long long a, long long b) {
    vector<long long> divisors;
    long long limit = min(a, b);
    for (long long i = 1; i <= limit; ++i) {
        if (a % i == 0 && b % i == 0) {
            divisors.push_back(i);
        }
    }
    if (divisors.empty()) return 1;
    return *max_element(divisors.begin(), divisors.end());
}

// Перебор от 1 до min(M, N) (возр)
long long gcdAscending(long long a, long long b) {
    long long nod = 1;
    long long limit = min(a, b);
    for (long long i = 1; i <= limit; ++i) {
        if (a % i == 0 && b % i == 0) {
            nod = i;
        }
    }
    return nod;
}

// Перебор от min(M, N) до 1 (убыв)
long long gcdDescending(long long a, long long b) {
    long long limit = min(a, b);
    for (long long i = limit; i >= 1; --i) {
        if (a % i == 0 && b % i == 0) {
            return i;
        }
    }
    return 1;
}

// Алгоритм Евклида
long long gcdEuclid(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Основная программа и таблица

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    const int TRIALS = 500;

    cout << "Проверка на простоту" << endl;
    cout << setw(12) << "Размер (N)" 
         << setw(18) << "Обычный" 
         << setw(18) << "Нечетные" 
         << setw(18) << "N^2" 
         << setw(18) << "N^2, нечетные" << endl;

    vector<long long> primeSizes = {1000, 5000, 10000, 20000, 50000};

    random_device rd;
    mt19937 gen(rd());

    for (long long n : primeSizes) {
        uniform_int_distribution<long long> dist(n / 2, n);

        auto start = high_resolution_clock::now();
        for (int t = 0; t < TRIALS; ++t) {
            isPrimeBasic(dist(gen));
        }
        auto end = high_resolution_clock::now();
        double timeA = duration_cast<microseconds>(end - start).count() / 1000.0;

        start = high_resolution_clock::now();
        for (int t = 0; t < TRIALS; ++t) {
            isPrimeOdd(dist(gen));
        }
        end = high_resolution_clock::now();
        double timeB = duration_cast<microseconds>(end - start).count() / 1000.0;

        start = high_resolution_clock::now();
        for (int t = 0; t < TRIALS; ++t) {
            isPrimeSqrt(dist(gen));
        }
        end = high_resolution_clock::now();
        double timeC = duration_cast<microseconds>(end - start).count() / 1000.0;

        start = high_resolution_clock::now();
        for (int t = 0; t < TRIALS; ++t) {
            isPrimeSqrtOdd(dist(gen));
        }
        end = high_resolution_clock::now();
        double timeD = duration_cast<microseconds>(end - start).count() / 1000.0;

        cout << setw(12) << n 
             << setw(15) << timeA << " ms" 
             << setw(15) << timeB << " ms" 
             << setw(15) << timeC << " ms" 
             << setw(15) << timeD << " ms" << endl;
    }

    cout << "\nВычисление НОД" << endl;
    cout << setw(12) << "Размер (N)" 
         << setw(18) << "Массив" 
         << setw(18) << "От 1 до мин" 
         << setw(18) << "От мин до 1" 
         << setw(18) << "Евклид" << endl;

    vector<long long> gcdSizes = {10000, 50000, 100000, 500000, 1000000};

    for (long long n : gcdSizes) {
        uniform_int_distribution<long long> dist(1, n);

        auto start = high_resolution_clock::now();
        auto end = high_resolution_clock::now();

        double timeA = 0;
        if (n <= 100000) {
            start = high_resolution_clock::now();
            for (int t = 0; t < TRIALS; ++t) {
                gcdArray(dist(gen), dist(gen));
            }
            end = high_resolution_clock::now();
            timeA = duration_cast<microseconds>(end - start).count() / 1000.0;
        }

        start = high_resolution_clock::now();
        for (int t = 0; t < TRIALS; ++t) {
            gcdAscending(dist(gen), dist(gen));
        }
        end = high_resolution_clock::now();
        double timeB = duration_cast<microseconds>(end - start).count() / 1000.0;

        start = high_resolution_clock::now();
        for (int t = 0; t < TRIALS; ++t) {
            gcdDescending(dist(gen), dist(gen));
        }
        end = high_resolution_clock::now();
        double timeC = duration_cast<microseconds>(end - start).count() / 1000.0;

        start = high_resolution_clock::now();
        for (int t = 0; t < TRIALS; ++t) {
            gcdEuclid(dist(gen), dist(gen));
        }
        end = high_resolution_clock::now();
        double timeD = duration_cast<microseconds>(end - start).count() / 1000.0;

        cout << setw(12) << n 
             << setw(15) << (n <= 100000 ? to_string(timeA) + " ms" : "N/A") 
             << setw(15) << timeB << " ms" 
             << setw(15) << timeC << " ms" 
             << setw(15) << timeD << " ms" << endl;
    }

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.clear();
    std::cin.sync();
    std::cin.get();

    return 0;
}