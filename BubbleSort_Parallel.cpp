#include<iostream>
#include<omp.h>
using namespace std;

void bubble(int *, int);

void swap(int &, int &);

void bubble(int *a, int n)
{
    for( int i = 0; i < n; i++ )
    {
    int first = i % 2;
    #pragma omp parallel for shared(a,first)
    for( int j = first; j < n-1; j += 2 )
    {
    if( a[ j ] > a[ j+1 ] )
    {
    swap( a[ j ], a[ j+1 ] );
    }
    }
    }
}

void swap(int &a, int &b)
{
    int test;
    test=a;
    a=b;
    b=test;
}
int main()
{

    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    bubble(a,n);
    cout<<"\n sorted array is=>";
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<endl;
    }

    return 0;
}
 --------------------------
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int main()
{
	int arr[] = { 5, 1, 4, 2, 8};
	int N = sizeof(arr) / sizeof(arr[0]);
	bubbleSort(arr, N);
	cout << "Sorted array: \n";
	printArray(arr, N);
	return 0;
}

// ## Command to run
// g++ -fopenmp  mergesort.cpp -o mergesort
