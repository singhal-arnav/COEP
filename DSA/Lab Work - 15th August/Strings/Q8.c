#include <stdio.h>
#include <wchar.h>

int wcscmp(const wchar_t* s1, const wchar_t* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (int)(*s1 - *s2);
}

int main() {
    wchar_t str1[100], str2[100];

    wprintf(L"Enter first wide character string: ");
    fgetws(str1, 100, stdin);

    wprintf(L"Enter second wide character string: ");
    fgetws(str2, 100, stdin);

    str1[wcslen(str1) - 1] = L'\0';
    str2[wcslen(str2) - 1] = L'\0';

    int result = wcscmp(str1, str2);

    if (result == 0) {
        wprintf(L"The strings are equal.\n");
    } else if (result < 0) {
        wprintf(L"First string is less than second string.\n");
    } else {
        wprintf(L"First string is greater than second string.\n");
    }

    return 0;
}
