#include <iostream>
using namespace std;

int minval(int arr[], int n)
{
	int m =  arr[0];
	
	#pragma omp parallel for reduction(min : m)
	for(int i=0; i<n; i++)
	{
		if(arr[i]<m)
		{
			m = arr[i];
		}
	}
	
	return m;
}

int maxval(int arr[], int n)
{
	int m =  arr[0];
	
	#pragma omp parallel for reduction(max : m)
	for(int i=0; i<n; i++)
	{
		if(arr[i]>m)
		{
			m = arr[i];
		}
	}
	
	return m;
}

int sum(int arr[], int n)
{
	int s = 0;
	
	#pragma omp parallel for reduction(+ : sum)
	for(int i=0; i<n; i++)
	{
		s = s+arr[i];
	}
	
	return s;
}

int avg(int arr[], int n)
{
	int s = 0;
	
	#pragma omp parallel
	{
//		int id = omp_get_thread_num();
		#pragma omp for
		for(int i=0; i<n; i++)
		{
			s = s+arr[i];
		}	
	}
	
	
	int a = s/n;
}

int main()
{
	cout<<"Enter number of elements: ";
	int n;
	cin>>n;
	int *arr = new int[n];
	cout<<"Enter elements: ";
	for(int i=0; i<n; i++)
	{
		cin>>arr[i];
	}
	
	cout<<"Minimum value of all is: "<<minval(arr,n)<<endl;
	cout<<"Maximum value of all is: "<<maxval(arr,n)<<endl;
	cout<<"Sum of all is: "<<sum(arr,n)<<endl;
	cout<<"Average of all is: "<<avg(arr,n)<<endl;
}

