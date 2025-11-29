#include <stdio.h>
#include <string.h>

char* build_str(char* nums, int len, int sign);

int main()
{
    FILE *fptr = fopen("numbers.txt", "r");
    char numbers[100];
    fgets(numbers, 100, fptr);
    int len = strlen(numbers);

    char* P;
    char* N;
    
    P = build_str(numbers, len,  0);
    printf("String of positive numbers: %s", P);

    N = build_str(numbers, len, 1);
    printf("\nString of negative numbers: %s", N);

    return 0;
}