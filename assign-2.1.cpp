#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include <typeinfo>
#include <stdlib.h>
#include <sstream>

using namespace std;

int res,lit_index=0,sym_index=0;
typedef struct inp1	//INPUT STRUCTURE
{
	int label;
	char mnem[10];
	char op1[10];
	char op2[10];
}inp1;
typedef struct out	//OUTPUT STRUCTURE
{
	int f1;
	string f2;
	string f3;
	string f4;
}out;
typedef struct sym	//SYMBOL STRUCTURE
{
	char name[10];
	int addr;
}sym;

typedef struct lit	//LITEERAL STRUCTURE
{
	char name[10];
	int addr;
}lit;


sym s[40];
lit l[40];


int handle_mnem(inp1 *p,out *o)		//HANDLING MNEMONICS
{
	
	o->f1 = p->label;
	string m;
	string mn(p->mnem);
	
	if(mn.compare("00")!=0)		
	{
		if(mn.substr(1,2).compare("AD")!=0)	//IMPERATIVE STATEMENT
		{
			int x=m.find(")");
			m  = mn.substr(4,x-4);
			
			o->f2=m;				
		}
		else				//ASSEMBLER DIRECTIVE(LTORG OR END)
			o->f2="00";	
	}
	else			//LITERAL LOCATION INSTRUCTIONS
	{
		o->f2="00";
	}	
	
	return 1;
}

int handle_op(inp1 *p,out *o)		//HANDLING OPERANDS
{
	
	string operand1(p->op1);
	string operand2(p->op2);
	int k;
	string str;
	string mn(p->mnem);
	
	if(operand1.substr(1,1).compare("R")==0)	//1ST OPERAND
	{
		
		string m = operand1.substr(3,2);
		o->f3=m;
		
	}
	else
		o->f3="00";		
	
	if(operand2.substr(1,1).compare("L")==0)	//2ND OPERAND
	{					//LITERAL
		
		k=operand2.find(")");
		stringstream z(operand2.substr(3,k-3));	
		cout<<"5";
		
		int key;
		z >> key; 
		stringstream ss;
		ss<<l[key].addr;
		ss>>str;
		o->f4 = str;
	}
	else if(operand2.substr(1,1).compare("S")==0)
	{
					//SYMBOL
		k=operand2.find(")");
		stringstream z(operand2.substr(3,k-3));		
		
		int key;
		z >> key; 
		stringstream ss;
		ss<<s[key].addr;
		ss>>str;
		o->f4 = str;
	}
	else if(operand2.substr(1,1).compare("C")==0)
	{
					//CONSTANT
		k=operand2.find(")");
		o->f4 = operand2.substr(3,k-3);
	}
	else if(mn.compare("(AD,04)")==0 || mn.compare("(AD,02)")==0 || mn.compare("00")==0)
	{				//HANDLING LTORG OR END OR LITERAL LOCATION INSTRUCTIONS AFTER THEM
		o->f3 = operand1;
		o->f4 = operand2;
	}
	else
	{
		o->f4="00";
	}
	return 1;	
}
int convert()		//PASS2 CONVERSION FUNCTION
{
	ifstream fin;
	ofstream fout; 
	string s1;
	fin.open("literal.txt");	//COPYING VALUES FROM LITERAL TABLE TO STRUCTURE
	do
	{
		fin>>l[lit_index].name;
		fin>>l[lit_index].addr;
		if(!fin)
			break;
		lit_index++;
		
	}while(fin);
	fin.close();
	
	fin.open("symbol.txt");		//COPYING VALUES FROM SYMBOL TABLE TO STRUCTURE
	do
	{
	
		fin>>s[sym_index].name;
		fin>>s[sym_index].addr;	
		if(!fin)
			break;
		sym_index++;	
		
	}while(fin);
	fin.close();
	for(int i=0;i<lit_index;i++)
	{
		cout<<l[i].name<<" "<<l[i].addr<<endl;
	}
	for(int i=0;i<sym_index;i++)
	{
		cout<<s[i].name<<" "<<s[i].addr<<endl;
	}
	
	fin.open("output.txt");
	fout.open("output1.txt");
	do
	{
		inp1 p;	
		out o;
		fin>>p.label;
		fin>>p.mnem;
		fin>>p.op1;
		fin>>p.op2;

		if(!fin)
		{
			fin.close();
			break;			
		}
		
		
		 
		string str(p.mnem);	 
		
		if(str.substr(1,2).compare("AD")!=0 || str.compare("(AD,04)")==0 || str.compare("(AD,02)")==0)		//IF ASSEMBLER DIRECTIVES , DO NOT COPY THEM TO MACHINE CODE
		{	
			s1=handle_mnem(&p,&o);
			
			res=handle_op(&p,&o);
		
			fout<<o.f1<<" "<<o.f2<<" "<<o.f3<<" "<<o.f4<<"\n";					
		}
		
		
	}while(fin);
	fin.close();
	fout.close();
	return 1;
}
int main()
{
	cout<<"PASS 2";
	res = convert();
	if(res==1)
	{
		cout<<"success";
	}
}
