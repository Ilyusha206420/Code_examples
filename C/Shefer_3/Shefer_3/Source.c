#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define N 10

int find_max(int* array, int len)
{
    int i = 0;
    int max = 0;
    int max_is_negative = 0;
    for (i = 0; i < len; i++)
    {
        if (array[i] < 0) {
            if ((-1 * array[i]) > max) {
                max = -1 * array[i];
                max_is_negative = 1;
            }
        }
        else {
            if (array[i] > max) {
                max = array[i];
                max_is_negative = 0;
            }
        }
    }
    if (max_is_negative == 1) {
        return -1 * max;
    }
    return max;
}

int main()
{
    int array[N];
    int i = 0;
    int s = 0;
    for (i = 0; i < N; i++) {
        scanf(" %d", &array[i]);
    }
    s = find_max(array, N);
    printf("max = %d \n", s);
    return 0;
}
