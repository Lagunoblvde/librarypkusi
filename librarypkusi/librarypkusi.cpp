#include <iostream>
#include <windows.h>
#include <string>


using namespace std;

typedef bool (*ContainsAllCharsFunc)(const char*, const char*);

int main() {
    setlocale(0, "");
    string inputStr;
    string inputChars;

    cout << "Напишите че нить: ";
    getline(cin, inputStr);

    cout << "Введите символы для поиска: ";
    getline(cin, inputChars);

    HINSTANCE hLib = LoadLibrary(L"notlibraryplusio.dll");
    if (hLib == NULL) {
        cerr << "Не пошло, библиотеки нема!" << endl;
        return 1;
    }

    ContainsAllCharsFunc contains_all_chars = (ContainsAllCharsFunc)GetProcAddress(hLib, "contains_all_chars");
    if (contains_all_chars == NULL) {
        cerr << "А вот функция работать не хочет!" << endl;
        FreeLibrary(hLib);
        return 1;
    }

    bool result = contains_all_chars(inputStr.c_str(), inputChars.c_str());

    if (result) {
        cout << "Работает!" << endl;
    }
    else {
        cout << "Работет, но не до конца." << endl;
    }

    FreeLibrary(hLib);

    return 0;
}