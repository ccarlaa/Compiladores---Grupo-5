int main() {
    int count = 0;
    while (count < 5) {
        if (count % 2 == 0) {
            printf("Even: ");
            printf(count);
        } else {
            printf("Odd: ");
            printf(count);
        }
        count = count + 1;
    }
    return 0;
}