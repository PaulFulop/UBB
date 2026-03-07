void ithPermutation(int n, int i)
{
    var digits = new List<int> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int[] fact = new int[10];
    fact[0] = 1;
    for (int j = 1; j < 10; j++)
        fact[j] = fact[j - 1] * j;

    for (int k = 0; k < n; k++)
    {
        int idx = i / fact[n - 1 - k];
        Console.Write(digits[idx]);
        digits.RemoveAt(idx);
        i %= fact[n - 1 - k];
    }
}
ithPermutation(10, 999999); // 2783915460 ✓