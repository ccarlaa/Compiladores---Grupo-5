int main()
{
    parameterTest(5, 10);
    return 0;
}

int parameterTest(int a, int b)
{
    int x;
    x = a + b;

    printf("\n--- TESTE DOS PARÂMETROS ---\n");
    printf("Valor de a: %d\n", a);
    printf("Valor de b: %d\n", b);
    printf("Soma (a + b): %d\n", x);
    printf("Os parâmetros estão funcionando corretamente!\n");
}