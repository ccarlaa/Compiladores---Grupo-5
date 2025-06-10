// Test 3: Loops (while and for)
int main() {
    int i = 0;
    int sum = 0;
    
    while (i < 10) {
        sum = sum + i;
        i = i + 1;
    }
    
    for (int j = 0; j < 5; j++) {
        sum = sum + j;
        if (j == 3) {
            break;
        }
    }
    
    return sum;
}
