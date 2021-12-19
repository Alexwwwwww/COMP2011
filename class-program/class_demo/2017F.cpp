#include <iostream>
using namespace std;

void mysterious(int a[], int& n)
{
    int k = 0;
    for (int i = 1; i < n; i++)
    {
        int j = 0;
        while (j <= k && a[i] != a[j])
        j++;
        if (j > k)
        {
            k++;
            a[k] = a[i];
        }
    }
    n = k + 1;
}
int main()
{
    int arr[] = {58, 26, 91, 26, 70, 70, 91, 58, 58, 58, 66};
    int size = sizeof(arr)/sizeof(int);

    mysterious(arr, size);

    for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
    cout << "size = " << size;
    cout << endl;
    return 0;
}