//Lexical Analyzer - 33255

#include <iostream>
#include <string.h>
#include <fstream>
#include <typeinfo>


using namespace std;

typedef struct keyword_tab
{
	char kw[40];
	char token[40];
}keyword_tab;

typedef struct term_tab
{
	char sym[40];
	char token[40];
	
}term_tab;
	
typedef struct ident_tab
{
	char name[40];
	char token[40];
	
}ident_tab;

typedef struct ust
{
	char inp[40];
	char tab[40];
	char token[40];
	int  ind;
}ust;

typedef struct lit_tab
{
	char name[40];
	char type[40];
}lit_tab;

keyword_tab key[32] = 
{
{"auto","K1"},{"break","K2"},{"case","K3"},{"char","K4"},{"const","K5"},{"continue","K6"},{"default","K7"},{"do","K8"},{"double","K9"},{"else","K10"},{"enum","K11"},{"extern","K12"},{"float","K13"},{"for","K14"},{"goto","K15"},{"if","K16"},{"int","K17"},
{"long","K18"},{"register","K19"},{"return","K20"},{"short","K21"},
{"signed","K22"},{"sizeof","K23"},{"static","K24"},{"struct","K25"},{"switch","K26"},{"typedef","K27"},{"union","K28"},{"unsigned","K29"},{"void","K30"},{"volatile","K31"},{"while","K32"}	
};

term_tab t[20] = 
{
	{"(","OB"},{")","CB"},{"{","OP"},{"}","CP"},{"+","PLUS"},{"-","MINUS"},{"*","MU"},{"/","DI"},{"=","EQUAL"}
	,{"&","AND"},{",","C"},{";","SC"},{"<","LT"},{">","GT"},{"++","PP"}
	,{"--","MM"},{"+=","PE"},{"-=","ME"},{"*=","MUE"},{"/=","DIE"}
};

ust u[100];ident_tab id[100];lit_tab l[100];
int res,ust_index=0,id_index=0,lit_index=0;

int convert(char *buffer)
{
	char *bp,*fp;
	int k,f1,f2,f3,f4,f5,prev=0;
	char temp[1000];
	char z[5],x[5];
	bp=&buffer[0];
	fp=&buffer[0];
	bzero(temp,1000);
	for(int i=0;i<strlen(buffer);i++)
	{
		f1=0;f2=0;
		if(buffer[i]=='"')			//HANDLING STRING CONSTANTS
		{

			k=0;
			do
			{
				temp[k]=buffer[i];
				i++;k++;
			}while(buffer[i]!='"');
			temp[k]=buffer[i];
			strcpy(l[lit_index].name,temp);
			strcpy(l[lit_index].type,"String Constant");
			strcpy(u[ust_index].inp,temp);
			strcpy(u[ust_index].tab,"Literal");
			strcpy(u[ust_index].token,l[lit_index].type);
			u[ust_index].ind=lit_index;
			lit_index+=1;
			ust_index+=1;
			fp=&buffer[i+1];
			bp=fp;
			bzero(temp,1000);	
			continue;
		}
		
		
		z[0]=buffer[i];
		z[1]='\0';
		if(prev==1)				//HANDLING ++,--,+=,etc.
		{
			if((buffer[i-1]=='+' && buffer[i]=='+') || (buffer[i-1]=='-' && buffer[i]=='-') || (buffer[i-1]=='+' && buffer[i]=='=') || (buffer[i-1]=='-' && buffer[i]=='=') || ((buffer[i-1]=='*' && buffer[i]=='=')) || ((buffer[i-1]=='/' && buffer[i]=='=')))
			{
			
				z[0]=buffer[i-1];
				z[1]=buffer[i];
				z[2]='\0';
				ust_index-=1;
			}
		}
		
		for(int j=0;j<20;j++)			//CHECKING FOR TERMINAL
		{
				
			if(strcmp(z,t[j].sym)==0 || isspace(buffer[i]) )	
			{
				
				f2=1;			
				k=0;
				while(bp!=fp)
				{
					
					temp[k]=*bp;
					bp++;
					k++;	
				}

				for(int m=0;m<32;m++)			//CHECKING IF CAPTURED STRING IS  A KEYWORD
				{
					if(strcmp(temp,key[m].kw)==0 && prev!=1)
					{
						f1=1;
						strcpy(u[ust_index].inp,temp);
						strcpy(u[ust_index].tab,"Keyword");
						strcpy(u[ust_index].token,key[m].token);
						u[ust_index].ind = m;
						ust_index+=1;
						break;	
					}
				}
				if(f1==0)
				{
			
					f3=0;
					if(prev!=1 && ((int(temp[0]) >= 65 && int(temp[0]) <= 90) || (int(temp[0]) >= 97 && int(temp[0]) <= 122)))
					{					//CHECKING FOR IDENTIFIER

						strcpy(u[ust_index].inp,temp);
						strcpy(u[ust_index].tab,"Identifier");

						
						for(int h=0;h<id_index;h++)
						{
							if(strcmp(id[h].name,temp)==0)
							{
								strcpy(u[ust_index].token,id[h].token);
								u[ust_index].ind = h;
								ust_index+=1;
								f3=1;
								break;
							}	
						}
						if(f3==0)
						{
							strcpy(id[id_index].name,temp);
							strcpy(id[id_index].token,"Id");
							sprintf(x,"%d",id_index);
							strcat(id[id_index].token,x);
							strcpy(u[ust_index].token,id[id_index].token);
							u[ust_index].ind = id_index;
							id_index+=1;
							ust_index+=1;
							
						}	

					}
					if(prev!=1 && (int (temp[0]) >=48 && int(temp[0])<=57))		
					{						////CHECKING FOR NUMERIC CONSTANT

						f4=0;
						
						for(int h=0;h<lit_index;h++)
						{
							if(strcmp(l[h].name,temp)==0)
							{
								strcpy(l[h].name,temp);
								strcpy(l[h].type,"Numeric Constant");
								strcpy(u[ust_index].inp,temp);
								strcpy(u[ust_index].tab,"Literal");
								strcpy(u[ust_index].token,l[h].type);
									u[ust_index].ind=h;
								ust_index+=1;
								f4=1;
								break;
							}
						}
						if(f4==0)
						{
							strcpy(l[lit_index].name,temp);
							strcpy(l[lit_index].type,"Numeric Constant");
							strcpy(u[ust_index].inp,temp);
							strcpy(u[ust_index].tab,"Literal");
							strcpy(u[ust_index].token,l[lit_index].type);
							u[ust_index].ind=lit_index;
							lit_index+=1;
							ust_index+=1;
						}
					}
				}
				bzero(temp,1000);
				if(!isspace(buffer[i]))			
				{						//COPYING TERMINAL TO UST
					strcpy(u[ust_index].inp,t[j].sym);
					strcpy(u[ust_index].tab,"Terminal");
					strcpy(u[ust_index].token,t[j].token);
					u[ust_index].ind=j;
					ust_index+=1;
				}
				
				fp=&buffer[i+1];		//SETTING FORWARD AND BACKWARD POINTERS TO NEXT WORD
				bp=fp;
				prev=1;
				break;

				
			}
		}
		if(f2==0)			//TERMINATING SYMBOL NOT FOUND
		{
			fp++;			//KEEP INCREMENTING FORWARD POINTER
			prev=0;
		}
	}


}


int readfun()
{
	string str;

	ifstream fin;
	fin.open("input.txt");
	do
	{
		getline(fin,str);	//READING A LINE FROM INPUT FILE
		char buffer[str.length()];
		strcpy(buffer,str.c_str());
		
		res= convert(buffer);		
		
	}
	while(fin);
	cout<<"\nIdentifier Table\n\nLexeme\tToken\n";		//PRINTING IDENTIFIER TABLE
	for(int i=0;i<id_index;i++)
	{
		cout<<"\n" << id[i].name << "\t" <<id[i].token;
	}
	cout<<"\n";
	cout<<"\nLiteral Table\n\nLexeme\tToken\n";		//PRINTING LITERAL TABLE
	for(int i=0;i<lit_index;i++)
	{
		cout<<"\n" << l[i].name << "\t" <<l[i].type;
	}
	cout<<"\n";
	cout<<"\nUNIFORM SYMBOL TABLE\n\nInput\tTable\tToken\tIndex\n";	//PRINTING UST
	for(int i=0;i<ust_index;i++)
	{
		cout<<"\n" <<u[i].inp<<"\t"<<u[i].tab<<"\t"<< u[i].token <<"\t"<<u[i].ind;
	}
	cout<<"\n";
	
}

int main()
{
	int *fp,*bp;
	cout<<"Lexical Analyser : -\n";
	res = readfun();
}
