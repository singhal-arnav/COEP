#include <stdio.h>
#include <string.h>

int findLongestSubsequence(const char* str1, const char* str2, const char** subsequence) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int start = 0;
    int maxLength = 0;

    for (int i = 0; i < len1; i++) {
        int currentLength = 0;
        int index1 = i;
        int index2 = 0;

        while (index1 < len1 && index2 < len2) {
            if (str1[index1] == str2[index2]) {
                currentLength++;
                index2++;
            }
            index1++;
        }

        if (currentLength > maxLength) {
            start = index2 + currentLength - 1;
            maxLength = currentLength;
        }
    }

    *subsequence = str1 + start;
    return maxLength;
}

int main() {
    const char* str1 = "abcdemnopxyz";
    const char* str2 = "mnotq";

    const char* subsequence;
    int length = findLongestSubsequence(str1, str2, &subsequence);

    printf("Longest subsequence: %.*s\n", length, subsequence);
    printf("Length of longest subsequence: %d\n", length);

    return 0;
}