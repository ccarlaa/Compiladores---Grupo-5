// Test 5: Complex expressions and operators
int main() {
    int a = 10;
    int b = 20;
    int c = 30;
    
    int result = (a + b) * c - (a / 2);
    
    if (result > 100 && a < b) {
        result = result % 50;
    }
    
    if (!(a == b) || c >= 30) {
        result = result + 1;
    }
    
    return result;
}
