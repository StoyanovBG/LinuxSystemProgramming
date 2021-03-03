#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>

using namespace std;

//gcc multiadd.cpp -lstdc++
//compile with ./a.out

int main()
{
	int arr[100];
	int i, n;
	int sum = 0;

	cout<<"\n Enter n nums you want to sum: ";
	cin>>n;
	
	cout<<"\n Enter "<<n<<" int nums: \n";
	for (i = 0; i < n; i++)
	{
		cout<<" Enter num "<<i + 1 <<". :";
		cin>>arr[i];
		sum+=arr[i];
	}
	
	cout<<"\n Sum: "<<sum<<"\n\n";
	return 0;
}
