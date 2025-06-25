int main() {
    int i = 0;
    while (i < 3) {
        int j = 0;
        while (j < 2) {
            printf(i);
            printf(j);
            j = j + 1;
        }
        i = i + 1;
    }
    return 0;
}