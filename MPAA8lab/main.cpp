#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <ctime>
#include "lcs.h"
using namespace std;

string Naiv(string One, string Two) {
    if ((One.length() == 0) || (Two.length() == 0)) return "";
    if (One[0] == Two[0]) {
        char c = One[0];
        One.erase(0, 1);
        Two.erase(0, 1);
        return c + Naiv(One, Two);
    }
    else {
        string S1 = One;
        string S2 = Two;
        One.erase(0, 1);
        Two.erase(0, 1);
        S1 = Naiv(Two, S1);
        S2 = Naiv(S2, One);
        if (S1 > S2) return S1;
        else return S2;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int N, M, i;
    string Alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", S1 = "", S2 = "";
    cout << "Введите размеры строк: ";
    cin >> N >> M;
    for (i = 0; i < N; i++)
        S1 += Alphabet[rand() % 52];
    for (i = 0; i < M; i++)
        S2 += Alphabet[rand() % 52];

    auto t1 = chrono::high_resolution_clock::now();
    cout << lcs(S1, S2);
    auto t2 = chrono::high_resolution_clock::now();
    auto seconds = chrono::duration<double>(t2 - t1).count();
    cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

    t1 = chrono::high_resolution_clock::now();
    cout << Naiv(S1, S2);
    t2 = chrono::high_resolution_clock::now();
    seconds = chrono::duration<double>(t2 - t1).count();
    cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

    S2 = S1;

    t1 = chrono::high_resolution_clock::now();
    cout << lcs(S1, S2);
    t2 = chrono::high_resolution_clock::now();
    seconds = chrono::duration<double>(t2 - t1).count();
    cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

    t1 = chrono::high_resolution_clock::now();
    cout << Naiv(S1, S2);
    t2 = chrono::high_resolution_clock::now();
    seconds = chrono::duration<double>(t2 - t1).count();
    cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

    int result = Catch::Session().run(argc, argv);
    return result;
}