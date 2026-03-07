// 4n^2 - 6n + 6
int calculate_diagomal_sum(int n)
{
    int S = 0;
    for (int i = 3; i <= n; i += 2)
    {
        S += calculate_sum_corners(i);
    }
    return S + 1;
}

int calculate_sum_corners(int n)
{
    return 4 * n * n - 6 * n + 6;
}

int main()
{
    Console.WriteLine(calculate_diagomal_sum(1001));
    return 0;
}

main();