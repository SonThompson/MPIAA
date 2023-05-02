#include "lcs.h"
#include <vector>

using namespace std;

string lcs(const string& first,const string& second) {

    vector<vector<int> > max_len;
    max_len.resize(first.size() + 1);
    for (int i = 0; i <= static_cast<int>(first.size()); i++)
        max_len[i].resize(second.size() + 1);
    for (int i = static_cast<int>(first.size()) - 1; i >= 0; i--) {
        for (int j = static_cast<int>(second.size()) - 1; j >= 0; j--) {
            if (first[i] == second[j]) {
                max_len[i][j] = 1 + max_len[i + 1][j + 1];
            }
            else {
                max_len[i][j] = max(max_len[i + 1][j], max_len[i][j + 1]);
            }
        }
    }
    string res;
    for (int i = 0, j = 0; max_len[i][j] != 0 && i < static_cast<int>(first.size()) && j < static_cast<int>(second.size()); ) {
        if (first[i] == second[j]) {
            res.push_back(first[i]);
            i++;
            j++;
        }
        else {
            if (max_len[i][j] == max_len[i + 1][j])
                i++;
            else
                j++;
        }
    }
    return res;
}

string lcs_naiv(const string& first, const string& second) {

    string result = "", str;
    int last_position = -1;
    for (int i = 0; i < first.length(); i++) {
        for (int j = i; j < first.length(); j++) {
            for (int k = 0; k < second.length(); k++) {
                if (first[j] == second[k] && k > last_position) {
                    str += first[j];
                    last_position = k;
                    break;
                }
            }
        }
        if (str.length() > result.length())
            result = str;
        str = "";
        last_position = -1;
    }
    return result;
}


   //{
   //    
   //    vector <string> L;
   //    int i, j;
   //    string C;

   //    /* Following steps build L[m+1][n+1] in bottom up fashion. Note
   //      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   //    for (i = 0; i <= first.length(); i++) {
   //        for (j = 0; j <= second.length(); j++) {
   //            if (i == 0 || j == 0)
   //                L[i][j] = 0;

   //            else if (first[i - 1] == second[j - 1])
   //                L[i][j] = L[i - 1][j - 1] + 1;

   //            else
   //                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
   //        }
   //    }
   //    return L;