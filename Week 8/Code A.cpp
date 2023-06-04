// Mohammad Jaafar
#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r)
{
    int leftArray[m - l + 1], rightArray[r - m];
    for (int i = 0; i < m - l + 1; i++)
    {
        leftArray[i] = arr[l + i];
    }
    for (int j = 0; j < r - m; j++)
    {
        rightArray[j] = arr[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < m - l + 1 && j < r - m)
    {
        if (leftArray[i] <= rightArray[j])
        {
            arr[k] = leftArray[i];
            i++;
        }
        else
        {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < m - l + 1)
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < r - m)
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

struct Node
{
    int d;
    int l;
    int r;
};

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    mergeSort(a, 0, n - 1);

    Node N[n];
    cout << n << endl;
    for (int i = 0; i < n - 1; i++)
    {
        N[i].d = a[i];
        N[i].r = a[i + 1];
        N[i].l = -1;
    }
    N[n - 1].d = a[n - 1];
    N[n - 1].r = -1;
    N[n - 1].l = -1;

    for (int i = 0; i < n - 1; i++)
    {
        cout << N[i].d << " " << N[i].l << " " << N[i].r << endl;
    }
    cout << N[n - 1].d << " " << N[n - 1].l << " " << N[n - 1].r << endl;
    cout << a[0];
    return 0;
}
