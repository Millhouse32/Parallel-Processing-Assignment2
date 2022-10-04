#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Create_Array(int* m, int* n, int array[], int size);

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

    int arraySizes[] = { 1000, 2000, 4000, 8000, 16000 };

    int size = 10;
    int array[10];

    Create_Array(&m, &n, array, size);
}

void Create_Array(int* m, int* n, int array[], int size) {
    // seed random generator
    srand ( time(NULL) );

    for (int i = 0; i < size; i++) {
        int num = (rand() % 
        (*n-*m + 1)) + *m;
        array[i] = num;
    }

    // print array
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}
