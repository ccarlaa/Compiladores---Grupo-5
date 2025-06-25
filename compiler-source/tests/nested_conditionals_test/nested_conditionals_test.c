int main() {
    int a = 10;
    int b = 5;

    if (a > b) {
        printf("a is greater than b");
        if (a > 15) {
            printf(" and a is greater than 15");
        } else {
            printf(" and a is not greater than 15");
        }
    } else if (b > a) {
        printf("b is greater than a");
    } else {
        printf("a and b are equal");
    }
    return 0;
}