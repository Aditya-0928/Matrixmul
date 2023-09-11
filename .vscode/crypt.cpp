#include <iostream>
#include <cstring>
using namespace std;

const int MAX_N = 10;
int used[MAX_N];
int mapping[MAX_N];

bool check(string s1, string s2, string s3) {
    int carry = 0;
    int len = s1.length();
    for (int i = len - 1; i >= 0; i--) {
        int num1 = mapping[s1[i] - 'A'];
        int num2 = mapping[s2[i] - 'A'];
        int num3 = mapping[s3[i] - 'A'];
        int sum = num1 + num2 + carry;
        if (sum % 10 != num3) return false;
        carry = sum / 10;
    }
    if (carry > 0) return false;
    return true;
}

bool backtrack(int index, string s1, string s2, string s3) {
    if (index == s1.length()) {
        return check(s1, s2, s3);
    }
    char c = s1[index];
    for (int i = 0; i < MAX_N; i++) {
        if (!used[i]) {
            used[i] = 1;
            mapping[c - 'A'] = i;
            if (backtrack(index + 1, s1, s2, s3)) {
                return true;
            }
            used[i] = 0;
        }
    }
    return false;
}

int main() {
    string s1 = "SEND";
    string s2 = "MORE";
    string s3 = "MONEY";
    memset(used, 0, sizeof(used));
    memset(mapping, -1, sizeof(mapping));
    if (backtrack(0, s1, s2, s3)) {
        for (int i = 0; i < MAX_N; i++) {
            if (mapping[i] != -1) {
                cout << (char)('A' + i) << ": " << mapping[i] << endl;
            }
        }
    } else {
        cout << "No solution found." << endl;
    }
    return 0;
} 
