#include <iostream>

using namespace std;

void bubbleSort(int arr[], int n)
{
    int i, j;
    bool flag;

    for (i = 0; i < n; i++)
    {
        flag = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }

        if (!flag)
        {
            break;
        }
    }
}
int main()
{
    int arr[9] = {};
    srand(time(0));

    for (int i = 0; i < 9; i++)
    {
        int random = (rand() % 9);
        arr[i] = random;
    }

    int n = sizeof(arr) / sizeof(int);

    cout << "Neseřazeno:";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    bubbleSort(arr, n);

    cout << "\nSeřazeno:";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return (0);
}