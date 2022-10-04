#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;

    printf("Enter a vlaue for M (lower bound)\n");
    scanf("%d", &m);
    printf("Enter value for N (upper bound)\n");
    scanf("%d", &n);

    FILE* file;
    file = fopen("performance.txt", "a");
    fprintf(file, "Value for M (lower bound): %d\n", m);
    fprintf(file, "Value for N (upper bound): %d\n", n);

    fclose(file);
}
