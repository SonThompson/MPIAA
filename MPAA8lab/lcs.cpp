#include "lcs.h"
#include <iostream>

using namespace std;

string Rec(int i, int j, int **A, string x, string y) {
    if ((i == 0) || (j == 0) || (A[i][j] == 0)) return "";
    else if (A[i][j] <= A[i - 1][j]) return Rec(i - 1, j, A, x, y);
    else if ((A[i][j] > A[i - 1][j]) && (A[i][j] > A[i][j - 1])) return Rec(i - 1, j - 1, A, x, y) + x[i - 1];
    else return Rec(i, j - 1, A, x, y);
}

string lcs(const string& first, const string& second) {
    // Return the longest common subsequence (LCS) of the two given strings.

    if ((first.length() == 0) || (second.length() == 0)) return "";
    int i, j;
    int** A = new int* [first.length() + 1];
    for (i = 0; i <= first.length(); i++)
        A[i] = new int[second.length()] + 1;
    for (i = 0; i < first.length() + 1; i++)
        A[i][0] = 0;
    for (i = 0; i < second.length() + 1; i++)
        A[0][i] = 0;

    for (i = 1; i < first.length() + 1; i++)
        for (j = 1; j < second.length() + 1; j++)
            if (first[i - 1] == second[j - 1])
                A[i][j] = A[i - 1][j - 1] + 1;
            else if (A[i - 1][j] > A[i][j - 1]) A[i][j] = A[i - 1][j];
            else A[i][j] = A[i][j - 1];

    return Rec(first.length(), second.length(), A, first, second);
}