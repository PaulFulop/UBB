#include <stdio.h>
#include <stdbool.h>

int ZeroDigits();
void Run();
int CountZeros(int n);
bool Prime(int n);
void FindLCS(int seq[], int n);

int main()
{
    Run();
    return 0;
}

/**
 * @brief Provides a menu and runs the application.
 * 
 */
void Run()
{
    printf("0 -> exit\n1 -> solve statement a\n2-> solve statement b\n");
    int choice = 1;
    while (choice)
    {
        printf("> ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int zero_digits = ZeroDigits();
            printf("The number of zeros of the final product is %d.", zero_digits);
            break;
        }
        else if (choice == 2)
        {
            int n = -1, seq[101];
            printf("Read the number of elements of the given sequence: ");
            scanf("%d", &n);

            printf("Read the sequence of numbers: ");
            for (int i = 0; i < n; ++i)
                scanf("%d", &seq[i]);

            FindLCS(seq, n);
            break;
        }
        else if (!choice)
            printf("Exiting...\n");
        else
            printf("Invalid choice.\n");
    }
}

/**
 * @brief Reads numbers until 0 is read, computes the product of all read numbers and returns the numbers of 0's in the final product.
 * 
 * @return int 
 */
int ZeroDigits()
{
	int x, prod = 1;
	printf("Read a number: ");
	scanf("%d", &x);

	if (x == 0)
		return 1;
	
	while (x)
	{
		printf("Read a number: ");
		prod *= x;
		scanf("%d", &x);
	}

	return CountZeros(prod);
}

/**
 * @brief Counts the number of 0's in a integer.
 * 
 * @param n The desired number.
 * @return int 
 */
int CountZeros(int n)
{
	int count = 0;
	while (n)
	{
		count += !(n % 10) ? 1 : 0;
		n /= 10;
	}

	return count;
}

/**
 * @brief Used for verifying whether a number is prime or not. 
 * 
 * @param n The number to verify the said "property".
 * @return true if n is a prime number.
 * @return false if n is not a prime number.
 */
bool Prime(int n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0) return false;
	return true;
}

/**
 * @brief Given a sequence of numbers,
 *  it finds the longest contiguous subsequence such that
 *  the sum of any two consecutive elements is a prime number.
 * 
 * @param seq The given sequence of numbers.
 * @param n The number of elements in that sequence.
 */
void FindLCS(int seq[], int n)
{
	int max_count = -1, max_left, max_right;
	bool found = false;


	for (int i = 1; i < n; ++i)
		if (Prime(seq[i] + seq[i - 1]))
		{
			found = true;
			int j = i;
			while (Prime(seq[j] + seq[j - 1]) && j < n)
				++j;

			if (j == n)
			{
				if (j - i > max_count)
				{
					max_count = j - i;
					max_left = i - 1;
					max_right = j - 1;
				}
				break;
			}
			
			if (j - i > max_count)
			{
				max_count = j - i;
				max_left = i - 1;
				max_right = j - 1;
			}

			i += j - i;
		}

	if (!found)
		printf("No such subsequence was found.");
	else
		for (int i = max_left; i <= max_right; ++i)
			printf("%d ", seq[i]);
}