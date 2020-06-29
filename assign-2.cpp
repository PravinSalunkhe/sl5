#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include <typeinfo>
#include <stdlib.h>

using namespace std;


int res,size,lc;
char mn[20],mtype[20];

typedef struct reg	//REGISTER STRUCTURE
{
	char name[10];
	char opc[10];
}reg;

typedef struct mot	//MOT TABLE STRUCTURE
{
	char mnem[20];
	char opc[10];
	int size;
	char type[3];
}mot;
typedef struct out	//OUTPUT STRUCTURE
{
	int f1;
	char f2[10];
	char f3[10];
	char f4[10];
}out;

typedef struct inp	//INPUT STRUCTURE
{
	char label[10];
	char mnem[10];
	char op1[10];
	char op2[10];
}inp;

typedef struct sym	//SYMBOL TABLE STRUCTURE
{
	char name[10];
	int addr;
}sym;

typedef struct lit	//LITERAL TABLE STRUCTURE
{
	char name[10];
	int addr;
}lit;

reg r[10] = {{"AREG","01"},{"BREG","02"},{"CREG","03"},{"DREG","04"}};

mot m[17] = {
		{"MOVER","01",02,"IS"},{"MOVEM","02",02,"IS"},{"ADD","03",02,"IS"},{"SUB","04",02,"IS"},{"MULT","05",02,"IS"},{"DIV","06",02,"IS"},{"STOP","07",02,"IS"},
		{"START","01",02,"AD"},{"END","02",02,"AD"},{"EQU","03",02,"AD"},{"LTORG","04",02,"AD"},{"ORIGIN","05",02,"AD"},
		{"DC","01",02,"DL"},{"DS","02",02,"DL"}	
};


lit y[40];
sym z[40];



int lit_index=0,sym_index=0,pool_index=0;
int label(inp *p)		//HANDLING LABELS
{
	int i,flag=0;
	for(i=0;i<sym_index;i++)
	{
		if(strcmp(z[i].name,p->label)==0)
		{
			z[i].addr=lc;
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		
		strcpy(z[i].name,p->label);
		z[i].addr = lc;
		sym_index=i+1;
	}
	//cout<<"Symbol not declared";
	return 1;
	
	
}
int handle_mnem(inp *p,out *o)		//HANDLING MNEMONICS
{
	o->f1 = lc;
	for(int i=0;i<14;i++)
	{
		if(strcmp(p->mnem,m[i].mnem)==0)
		{
			//cout<<"1";
			strcpy(o->f2, "(");
			strcat(o->f2 , m[i].type);
			strcat(o->f2 , ",");
			strcat(o->f2 , (char*)m[i].opc);
			strcat(o->f2,")");
			size=m[i].size;	
			strcpy(mn,m[i].mnem);
			strcpy(mtype,m[i].type);
			return 1;			
		}			
	}
	return -1;	
}
int handle_op(inp *p,out *o)		//HANDLING OPERANDS
{
	char temp[2];
	int flag=0,t,f1=0,f2=0;
	int k=0,j,x;
	
	if(strcmp(p->op1,"-")==0 && strcmp(p->op2,"-")==0)		//NO OPERANDS
	{
		strcpy(o->f3,"00");
		strcpy(o->f4,"00");
		o->f1 = lc;
		
		if(strcmp(p->mnem,"LTORG")==0 || strcmp(p->mnem,"END")==0)		//LTORG AND END  
		{
			ofstream fout("output.txt",ios :: out | ios :: app);
			for(int i=pool_index;i<lit_index;i++)
			{
				o->f1 = lc;
				y[i].addr = lc;
				if(i > pool_index)
					strcpy(o->f2,"00");
				j=1,x=0;	
				while(y[i].name[j]!= '\'')
				{	
					o->f4[x]=y[i].name[j];
					x++;
					j++;			
				}
				fout<<o->f1 << " " << o->f2 << " "<<o->f3 << " "<< o->f4<<endl;
				lc=lc+1;			
			}
			pool_index=lit_index;
			fout.close();
		}	
		
		if(strcmp(p->mnem,"STOP")==0)
		{	
			lc=lc+size;
			ofstream fout("output.txt",ios :: out | ios :: app);
			fout<<o->f1 << " " << o->f2 << " "<<o->f3 << " "<< o->f4<<endl;
			fout.close();
		}	

		return 1;
	}
	else if(strcmp(p->op1,"-")!=0)	//1ST OPERAND
	{
	//cout<<"1";
		for(int i=0;i<4;i++)
		{
			if(strcmp(p->op1,r[i].name)==0)
			{
				strcpy(o->f3,"(R,");
				strcat(o->f3,r[i].opc);
				strcat(o->f3 ,")");
				f1=1;				
			}
			if(strcmp(p->op2,r[i].name)==0)	//INVALID OP2
			{
				f2=1;
				break;
			}
		}

		if(f2==1)
		{
			cout<<"Invalid Operand 2";
			return -1;
		}
		if(f1==0)
		{
			cout<<"Invalid Operand 1";
			return -1;
		}			
	}
	
	if(p->op2[0]=='\'')					
	{										//LITERAL
		
	//	cout<<"2";
		for(k=0;k<lit_index;k++)
		{
			//cout<<"3";
			if(strcmp(y[k].name,p->op2)==0)
			{
				flag=1;
				break;
			}
		}
		
		if(flag==0)
		{
			//cout<<"4";
			strcpy(y[k].name,p->op2);
			y[k].addr = -1;
			lit_index=k+1;
			//cout<<y[k].name;
		}
		strcpy(o->f4 , "(L,");
		sprintf(temp,"%d",k);
		strcat(o->f4 , temp);
		strcat(o->f4 , ")");
		
		if(strcmp(p->mnem,"START")!=0)
		{
			ofstream fout("output.txt",ios :: out | ios :: app);
			fout<<o->f1 << " " << o->f2 << " "<<o->f3 << " "<< o->f4<<endl;
			fout.close();
			lc=lc+size;
		}
		else
		{
			ofstream fout("output.txt",ios :: out);
			fout<<o->f1 << " " << o->f2 << " "<<o->f3 << " "<< o->f4<<endl;
			fout.close();
			lc=lc+size;
		}
			
	}
	else
	{
		t = atoi(p->op2);					//SYMBOL			
		if(t==0)						
		{
		
			k=0;
			for(k=0;k<sym_index;k++)
			{
				if(strcmp(z[k].name,p->op2)==0)
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				strcpy(z[k].name,p->op2);
				z[k].addr = -1;
				sym_index=k+1;
			}
			strcpy(o->f4 , "(S,");
			sprintf(temp,"%d",k);
			strcat(o->f4 , temp);
			strcat(o->f4 , ")");
		
			if(strcmp(p->mnem,"START")!=0)
			{
				ofstream fout("output.txt",ios :: out | ios :: app);
				fout<<o->f1 << " " << o->f2 << " "<<o->f3 << " "<< o->f4<<endl;
				fout.close();
				lc=lc+size;
			}
			else
			{
				ofstream fout("output.txt",ios :: out);
				fout<<o->f1 << " " << o->f2 << " "<<o->f3 << " "<< o->f4<<endl;
				fout.close();
				lc=lc+size;
			}	
		}
		else
		{
			
			//cout<<"constant";					//CONSTANT
			strcpy(o->f4,"(C,");
			strcat(o->f4,p->op2);
			strcat(o->f4,")");
			if(strcmp(mn,"ORIGIN")==0)
			{
				lc=t;
			}
			if(strcmp(mn,"START")==0)
			{	
				lc= t;	
				o->f1 = 00;
			}					
			else if(strcmp(mtype,"AD")!=0 && strcmp(p->mnem,"STOP")!=0)
			{	
				
				if(strcmp(mn,"DS")==0)
				{
					//cout<<"3"<<t;
					lc=lc+t;
				}
				else
					lc = lc+size;

			}	
			strcpy(o->f3,"00");
			ofstream fout("output.txt",ios :: out | ios :: app);
			fout<<o->f1 << " " << o->f2 << " "<<o->f3 << " "<< o->f4<<endl;
			fout.close();
			//cout<<lc;
			
		}

	}
	
	return 1;

}

int convert()
{
	int lc=-1;
	ifstream fin;
	fstream f;
	ofstream fout;
	f.open("literal.txt",ios ::out);
	f.close();
	f.open("symbol.txt",ios ::out);
	f.close();
	f.open("output.txt",ios ::out);
	f.close();

	fin.open("input.txt");
	
	do
	{
		
		inp p;
		out o;
		
		fin>>p.label;
		fin>>p.mnem;
		fin>>p.op1;
		fin>>p.op2;
		
		if(!fin)
			break;
		//cout<<p.mnem;
		
			
		if(strcmp(p.label,"-")!=0)
		{
			//cout<<"adsd"<<endl;
			res=label(&p);
			if(res==-1)
				return -1;
		}	
		res=handle_mnem(&p,&o);	
		if(res==-1)
		{
			 cout<<"Invalid Mnemonic";
			 return -1;
		}
		res= handle_op(&p,&o);
		if(res==-1)
			 return -1;
		
			
	}while(fin);

	fout.open("literal.txt",ios :: out | ios :: app);
	for(int i=0;i<lit_index;i++)
	{
		if(y[i].addr==-1)
		{
			cout<<"Literal "<< y[i].name << " used but not declared"; 
			return -1;
		}
		fout<<y[i].name<<" "<<y[i].addr<<endl;

	}
	fout.close();
	fout.open("symbol.txt",ios :: out | ios :: app);
	for(int i=0;i<sym_index;i++)
	{
		if(z[i].addr==-1)
		{
			cout<<"Symbol "<< z[i].name << " used but not declared"; 
			return -1;
		}
		fout<<z[i].name<<" "<<z[i].addr<<endl;
	}
	fout.close();
	return 1;
}
int main()
{

	fstream f;
	cout<<"The Assembly code is passed from the mnemonic.txt file and is converted into machine code as follows\n";
	
	int result = convert();	
	if(result == -1)
	{
		cout <<"\nInvalid Assembly code";
		f.open("literal.txt",ios ::out);
		f.close();
		f.open("symbol.txt",ios ::out);
		f.close();
		f.open("output.txt",ios ::out);
		f.close();
	}
		 
	return 0;
	
}	
	
