//Optimal Storage On Tapes - 33255 

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int a[100];
int n;
struct tape
{
	int t[100];
	int no_of_elements;
};
void merge(int *arr,int i,int mid,int j)
{
	int k=i,p=i,r= mid + 1;
	
	for(int l=0;l<n;l++)
	{
		a[l]= *(arr+l);
	}	
	while( p <= mid  && r <= j )
	{
		if(*(a+p)  <=  *(a+r) )
		{
			cout<<"1";
			*(arr+k)= *(a+p);
			//cout<<a[k]<<"\n";
			k++;
			p++;
		}
		else
		{
			cout<<"2";
			*(arr+k) = *(a+r);
			//cout<<a[k]<<"cvb\n";
			k++;
			r++;
		}
	}
	while(p <= mid)
	{
		cout<<"3";
		*(arr+k)= *(a+p);
		//cout<<a[k]<<"\n";
		k++;
		p++;
	}
	while(r <= j)
	{
		cout<<"4";
		*(arr+k) = *(a+r);
		//cout<<a[k]<<"\n";
		k++;
		r++;
	}
	
}


void merge_sort(int *arr,int i,int j)
{
	int mid = (i+j)/2;
	//cout<<mid<<"\n";
	if(i < j)
	{ 
		merge_sort(arr,i,mid);
		merge_sort(arr,mid+1,j);
		
		merge(arr,i,mid,j);	
	}
	
}
int fibonacci(int *a,int count)
{
	int s=0;
	for(int i=0;i<=count;i++)
	{
		s=s+*(a+i);
	}
	return s;
}
void cal_mrt(struct tape *z,int m)
{
	int sum;
	for(int i=0;i<m;i++)
	{
		cout<<"\nTape "<<i+1<<":- ";
		sum=0;
		for(int k=0;k<z[i].no_of_elements;k++)
		{
			cout<<z[i].t[k]<<" ";
			sum=sum +fibonacci(z[i].t,k);
			//cout<<" "<<sum;
		}
		cout<<"\nMRT of tape " << i+1 <<" is " << (float)sum/z[i].no_of_elements<<"\n";
	}	
}
void hor_place(int *s,int *arr,int m)
{
	int i = 0,j=0,sum,count;
	int temp[m];
	for(int i=0;i<m;i++)
	{
		temp[i]=*(s+i);
	}
	
	struct tape  z[m];
	for(int i =0 ;i < m;i++)
		z[i].no_of_elements = 0;
		
	while(i < n)
	{
		if(*(temp+j) >= *(arr + i))
		{
			z[j].t[z[j].no_of_elements] = *(arr + i);
			z[j].no_of_elements++;
			*(temp+j) = *(temp+j) - *(arr + i);
			i++;
		}
		else
		{
			j=j+1;
			if(j==m)
				break;
		}
	}
	cout<<"\nPlacement of Tapes :-\n";
	cal_mrt(z,m);	
	
}

void ver_place(int *s,int *arr,int m)
{
	int j=0,i=0,sum,f1=0,b,k=0;
	struct tape z[m];
	int temp[m];
	for(int i=0;i<m;i++)
	{
		temp[i]=*(s+i);
	}	
	for(int i =0 ;i < m;i++)
		z[i].no_of_elements = 0;
	while(i < n)
	{
		if(*(temp+j) >= *(arr + i))
		{
			z[j].t[z[j].no_of_elements] = *(arr+i);
			z[j].no_of_elements++;
			*(temp+j) = *(temp+j) - *(arr + i);
			i++;
			j=(j+1) % m;
			f1=0;
		}
		else
		{
			if(f1==0)
			{
				b=j;
				f1=1;
			}
			j=(j+1) % m;
			if(b==j)
			{
				i++;
				f1=0;
			}
		}
	
	}
	
	cal_mrt(z,m);	

}
int main()
{
	int m,ch;
	cout<<"Enter the no of tapes";
	cin>>m;
	int size[m];
	for(int i=0;i<m;i++)
	{
		cout<<"Enter the length of tape "<< i+1 <<":- ";
		cin>>size[i];
	}
	cout<<"\nEnter the no of programs : -";
	cin>>n;	
	int arr[n];	
	for(int i=0;i<n;i++)
	{
		cout<<"Enter Element " << i+1 << ":-";
		cin>>arr[i];
	}
	merge_sort(arr,0,n-1);
	cout<<"\n";
	for(int i=0;i<n;i++)
	{
		cout<<" "<<arr[i];
	}
	do
	{
		cout<<"\n1.Horizontal placement\n2.Vertical placement\n3.Exit\n Enter ur choice :- ";
		cin>>ch;
		switch(ch)
		{
			case 1 :
					hor_place(size,arr,m);		
					break;
			case 2 : 
					ver_place(size,arr,m);
					break;
		}	
	}while(ch!=3);		
							 
	return 0;	
	
}

