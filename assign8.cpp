#include <iostream>

using namespace std;

typedef struct sparse
{
	int src;
	int dest;
	float value;
}sp;

void bellman(sp *s,int n,int m,int source)
{
	float dist[n],pred[n];
	int flag,k;
	for(int i=0;i<n;i++)
	{
		if(i==source)
		{	
			dist[i]=0;
			pred[i]=source;
		}	
		else
		{	
			dist[i]=32767;
			pred[i]=-1;
		}
	}
	for(int j=0;j<n-1;j++)
	{
		flag=0;
		for(int i=0;i<m;i++)
		{	
			if(dist[(s+i)->src] + (s+i)->value < dist[(s+i)->dest])
			{
				dist[(s+i)->dest]=dist[(s+i)->src] + (s+i)->value;
				pred[(s+i)->dest]=(s+i)->src;
				if(flag==0)
					flag=1;
				cout<<"\n"<<dist[(s+i)->dest];
				cout<<"\n"<<pred[(s+i)->dest]<<"\n";
			}
		}
		if(flag==0)
			break;	
	}
	for(int i=0;i<m;i++)
	{	
		if(dist[(s+i)->src] + (s+i)->value < dist[(s+i)->dest])
		{
			cout<<"\nA negative cycle is present in the graph.Hence bellman ford cannot give the solution.";
			return;
		}
	}
	for(int i=0;i<n;i++)
	{
		int arr[n];
		k=0;
		if(i!=source)
		{
			cout<<"\nPath to vertex " << i <<" is ";
			int j=i;
			arr[k++]=i;
			while(j!=source)
			{
				j=pred[j];
				arr[k++]=j;
			}
			k--;
			while(k>=0)
			{
				cout<<arr[k];
				if(k>0)
					cout<<" -> ";
				k--;
			}
			cout<<"\nDistance of shortest path is :- "<<dist[i];
		}
	}
}

int main()
{
	int m,n,source;
	cout<<"\nEnter the no of vertices in the graph :-";
	cin>>n;
	cout<<"\nEnter the no of edges in the graph :-";
	cin>>m;
	sp s[m];
	for(int i=0;i<m;i++)
	{	
		cout<<"\nEnter the details of edge " << i+1 ;
		cout<<"Enter the source :-";
		cin>>s[i].src;
		cout<<"Enter the destination :-";
		cin>>s[i].dest;
		cout<<"Enter the weight :- ";
		cin>>s[i].value;
	}
	cout<<"Enter the source vertex :- ";
	cin>>source;
	bellman(s,n,m,source);
	return 0;

}