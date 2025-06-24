int main() {
    int x = 10;
    int y = 5;
    int z = 15;

    if (x > y && z > x) {
        printf("Both conditions are true");
    }

    if (x < y || z > y) {
        printf("At least one condition is true");
    }

    if (!(x == y)) {
        printf("x is not equal to y");
    }
    return 0;
}