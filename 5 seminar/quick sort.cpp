#include <iostream>

void printArray(int *a, int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << a[i] << std::endl;
}

void quickSort(int *a, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = a[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = a[i];
            a[i] = array[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(a, low, j);
    if (i < high)
        quickSort(a, i, high);
}

int main()
{
    int a[] = {4, 7, 1, 10, 9};
    int n = sizeof(array)/sizeof(array[0]);

    std::cout << "исходный набор :" << std::endl;
    printArray(a, n);

    quickSort(a, 0, n);

    std::cout << "упорядоченный набор :" << std::endl;
    printArray(a, n);
    return (0);
}
