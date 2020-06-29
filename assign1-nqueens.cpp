#include <iostream>

using namespace std;

int count=0;
bool place(int arr[],int k,int i)	//placing queen 
{
	for(int j=0;j<k;j++)	//loop for checking with all previous queens
	{
		if(arr[j]==i || abs(i-arr[j])==abs(k-j))	//checking same column and diagonal condition
			return false;
	}
	return true;		//can be placed at ith position

}
void print(int arr[],int n)		//printing solution
{
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<"	";
	}
}
void nqueens(int arr[],int k,int n)
{
	for(int i=0 ; i<n;i++)	//checking all columns for each queen
	{
		if(place(arr,k,i))	//checking for  ith column
		{
			arr[k]=i;		//place at ith location

			if(k==n-1)		//if last queen 
			{
				print(arr,n);	//print solution
				count++;
				cout<<"\n";
			}
			else
				nqueens(arr,k+1,n);		//placing next queen
		}

	}
}

int main()
{
	int n;
	cout<<"Enter the no of queens to place:-";
	cin>>n;
	int arr[n];
	nqueens(arr,0,n);
	cout<<"\nNo of Solutions are :-";
	cout<<count<<"\n";
	return 0;
}
