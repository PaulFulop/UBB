#include <stdio.h>

int a[] = {123, 234, 345, 65, 16};
int n = sizeof(a) / sizeof(a[0]);

char* convert_base2(int x);

int main()
{
    // in hexa
    printf("Base2: ");
    for(int i = 0; i < n; ++i)
        printf("%x ", a[i]);
    
    printf("\nBase16: ");

    // in binary
    char* bin_value;
    for(int i = 0; i < n; ++i)
    {
        bin_value = convert_base2(a[i]);
        printf("%s ", bin_value);
    }

    return 0;
}