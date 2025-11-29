void main() {
    String a = IO.readln();
    int n = Integer.parseInt(a);
    int sum = 0;

    for (int i = 1; i <= n; i++) {
        String strNum = IO.readln();
        int num = Integer.parseInt(strNum);

        sum += num;
    }

    double avg = (double) sum / n;
    IO.println(avg);
}