#include <iostream>
using namespace std;

int main() {
    string sentence, result = "";
    cout << "Enter your sentence: ";
    getline(cin, sentence);
    result += toupper(sentence[0]);
    for (int i = 1; i < sentence.length(); i++) {
        if (sentence[i] == ' ' && result[result.length() - 1] == ' ') {
            continue;
        }
        result += tolower(sentence[i]);
    }
    cout << result;
    return 0;
}