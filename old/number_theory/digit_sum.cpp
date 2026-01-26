int digit_sum(int n) {
    while(n>=10) {
            int temp = 0;
            while (n > 0) {
                temp += n % 10;
                n /= 10;
            }
            n = temp;
        }
    return n;
}