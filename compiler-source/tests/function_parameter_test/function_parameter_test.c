void calculate(int a, int b)
{
    int sum = a + b;
    printf("The sum of %d and %d is: %d\n", a, b, sum);
}

int main()
{

    printf("Starting the program...");

    calculate(15, 25);
    calculate(7, 3);

    printf("Program finished successfully.");

    return 0;
}