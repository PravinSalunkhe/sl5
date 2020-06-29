// TSP using Branch And Bound - 33255

#include <iostream>
#include <queue>

using namespace std;


struct term
{
	int cost;
	int path[20];
	int *matrix;
	term(int cost)
        : cost(cost)
	{
	}
};
struct op {
    bool operator()(term const& p1, term const& p2)
    {
        return p1.cost > p2.cost;
    }
};

priority_queue <term, vector<term>, op> g;


void ch_infinity(int *temp,int r,int c,int n);
struct term* expand(term * node,int n);
void display(int *mat,int row,int column);
int reduce_mat(int *mat, int n);
void mat_copy(int *a ,int *b,int n);
void tsp_bb(int *mat,int n)
{

	int cost=reduce_mat(mat,n);
	//display(mat,n,n);
	//cout<<cost;
	term *node = (struct term *)malloc(n*n*sizeof(struct term));
	node->cost=cost;
	node->path[0]=1;
	node->path[1]=1;
	node->matrix = (int *)malloc(n*n*sizeof(int));
	mat_copy(mat,node->matrix,n);
	//display(node->matrix,n,n);

	node = expand(node,n);
	
	if(node->cost <= g.top().cost)
	{
		cout<<"\nPath of Salesman :- ";
		for(int i=1;i<=n;i++)
		{
			cout<<node->path[i]<<" ";
		}
		cout<<node->path[1];
		cout<<"\ncost of travelling :- " <<node->cost<<"\n";
	}
	else
	{
		while(1)
		{

			struct term p = g.top();
			node = &p;
			g.pop();
			node = expand(node,n);
			if(node->cost <= 	g.top().cost)
			{
				cout<<"\nPath of Salesman :- ";
				for(int i=1;i<=n;i++)
				{
					cout<<node->path[i]<<" ";
				}
				cout<<node->path[1];
				cout<<"\ncost of travelling:- " <<node->cost<<"\n";
			}
		}
	}
}
struct term* expand(term *node,int n)
{
		int k,count,r;
		term node1(0);
		while(1)
		{
			count = node->path[0];
			k=count+1;
			int cost = node->cost;
			int visited[n+1];
			r=node->path[count];
			for(int i=0;i<=n;i++)
				visited[i]=0;
			for(int i=1;i<=count;i++)
				visited[node->path[i]]=1;
			for(int j=1;j<=n;j++)
			{
				if(!visited[j])
				{
					int *temp = (int *)malloc(n*n*sizeof(int));
					mat_copy(node->matrix,temp,n);
					ch_infinity(temp,r-1,j-1,n);
					int red_cost = reduce_mat(temp,n);
					node1.cost = cost + *(node->matrix+(r-1)*n+(j-1)) + red_cost;
					//cout<<"\n"<<node1.cost;
					for(int i=0;i<=count;i++)
						node1.path[i]=node->path[i];
					node1.path[0]=k;
					node1.path[k]=j;
					node1.matrix = (int *)malloc(n*n*sizeof(int));
					mat_copy(temp,node1.matrix,n);

					g.push(node1);
				}
			}
			if(k==n+1)
				break;
			term p = g.top();
			node = &p;
			g.pop();
		}
		term *node2 = (struct term *)malloc(sizeof(struct term));
		node2->cost=node->cost;
		for(int i=0;i<=n;i++)
			node2->path[i] = node->path[i];
		mat_copy(node->matrix,node2->matrix,n);
		return node2;
}
void ch_infinity(int *temp,int r,int c,int n)
{
	for(int i=0;i<n;i++)
		*(temp+r*n+i)=99999;
	for(int i=0;i<n;i++)
		*(temp+i*n+c)=99999;

	*(temp+c*n+0)=99999;
}
int reduce_mat(int *mat, int n)
{
	int min[n],r=0;
	for(int i=0;i<n;i++)
	{
		min[i]=99999;
		for(int j=0;j<n;j++)
		{
			if(*(mat+i*n+j) < min[i])
				min[i]=*(mat+i*n+j);
		}
		if(min[i]!=0 && min[i]!=99999)
		{
			for(int j=0;j<n;j++)
			{
				if(*(mat+i*n+j)!=99999)
				*(mat+i*n+j)=*(mat+i*n+j)- min[i];
			}
			r=r+min[i];
		}
	}
	for(int i=0;i<n;i++)
	{
		min[i]=99999;
		for(int j=0;j<n;j++)
		{
			if(*(mat+j*n+i) < min[i])
				min[i]=*(mat+j*n+i);
		}
		if(min[i]!=0 && min[i]!=99999)
		{
			for(int j=0;j<n;j++)
			{
				if(*(mat+i*n+j)!=99999)
				*(mat+j*n+i)=*(mat+j*n+i)- min[i];
			}
			r=r+min[i];
		}
	}
	return r;
}
void input(int *mat,int row,int col)
{
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			cout<<"\nENTER THE WEIGHT BETWEEN VERTEX "<<i<<" AND "<<j<<" :-";
			cin>>*(mat+i*col+j);
		}
	}
}
void display(int *mat,int row,int column)//display matrix
{
	int i,j;
	printf("\n[");
	for(i=0;i<row;i++)
	{
	for(j=0;j<column;j++)
	{
	printf("%d\t",*(mat+i*column+j));
	}
	printf("\n");
	}
	printf("]\n");
}
void mat_copy(int *a,int *b,int n)//display matrix
{
	int i,j;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			*(b+i*n+j)=*(a+i*n+j);
		}
	}
}
int  main()
{
	int n;
	cout<<"Enter the no of nodes in the graph:- ";
	cin>>n;
	int *mat;
	mat = (int *)malloc(n*n*sizeof(int));
	input(mat,n,n);
	tsp_bb(mat,n);
}
/*
Output:- 
admin1@pravin-27:~/te10/sl5$ ./a.out
Enter the no of nodes in the graph:- 4

ENTER THE WEIGHT BETWEEN VERTEX 0 AND 0 :-99999

ENTER THE WEIGHT BETWEEN VERTEX 0 AND 1 :-15

ENTER THE WEIGHT BETWEEN VERTEX 0 AND 2 :-6

ENTER THE WEIGHT BETWEEN VERTEX 0 AND 3 :-20

ENTER THE WEIGHT BETWEEN VERTEX 1 AND 0 :-5

ENTER THE WEIGHT BETWEEN VERTEX 1 AND 1 :-99999

ENTER THE WEIGHT BETWEEN VERTEX 1 AND 2 :-9

ENTER THE WEIGHT BETWEEN VERTEX 1 AND 3 :-15

ENTER THE WEIGHT BETWEEN VERTEX 2 AND 0 :-6

ENTER THE WEIGHT BETWEEN VERTEX 2 AND 1 :-13

ENTER THE WEIGHT BETWEEN VERTEX 2 AND 2 :-99999

ENTER THE WEIGHT BETWEEN VERTEX 2 AND 3 :-12

ENTER THE WEIGHT BETWEEN VERTEX 3 AND 0 :-8

ENTER THE WEIGHT BETWEEN VERTEX 3 AND 1 :-8

ENTER THE WEIGHT BETWEEN VERTEX 3 AND 2 :-19

ENTER THE WEIGHT BETWEEN VERTEX 3 AND 3 :-99999

Path of Salesman :- 1 3 4 2 1
cost of travelling :- 31
admin1@pravin-27:~/te10/sl5$ 


*/

