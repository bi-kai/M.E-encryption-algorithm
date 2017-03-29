#include<stdio.h>
#include<iostream.h>
#include<string.h>

const int size=10;

void Display()
{
	cout<<"\nselect what you want to do:"<<endl;
	cout<<"0.Exit";
	cout<<"1.Manchester encoding."<<endl;
	cout<<"2.Differential Manchester encoding."<<endl;
	cout<<"3.Translate the Manchester code into original one."<<endl;
	cout<<"4.Translate the Differential Manchester code into original one."<<endl;
}

void Encipher_M(char code[])   //Manchester Encoding
{
	int i,len;
	len=strlen(code);
	cout<<"the Manchester code is: ";
	for(i=0;i<len;i++)
	{
		if(code[i]=='1')
			cout<<"10";
		else cout<<"01";
	}
	cout<<endl;
}
/*
void Encipher_DM(char code[])  //Differential Manchester Encoding
{
	int i,len,a[2*size];
	len=strlen(code);
	cout<<"the Differential Manchester code is: ";
	if(code[0]=='1')
	{
		a[0]=1; a[1]=0;
	}
	else {
		a[0]=0; a[1]=1;
	}
	for(i=1;i<len;i++)
	{
	   if(code[i]=='0')
	    if(a[2*i-1]==0){
				a[2*i]=1; a[2*i+1]=0;
			}
		   else{
				a[2*i]=0; a[2*i+1]=1;
			}
	   else
		if(a[2*i-1]==0){
				a[2*i]=0; a[2*i+1]=1;
			}
			else{
				a[2*i]=1; a[2*i+1]=0;
			};
		
	}
	for(i=0;i<2*len;i++)
		cout<<a[i];
	cout<<endl;
}*/

void Decipher_M(char code[]) //translate the Manchester code to original one.
{
	int i,len,a[size];
	len=strlen(code);

	while(len%2)
	{
		cout<<"the Manchester code input is wrong.please input again:"<<endl;
		cin>>code;
		len=strlen(code);
	}
	while(len>size*2) 
	{
		cout<<"the code input is beyond length limit.please input again:"<<endl;
		cin>>code;
		len=strlen(code);
	}
    for(i=0;i<len;i+=2)
	{
		if(code[i]=='0'&&code[i+1]=='1') 
		{
			a[i/2]=0;
		}
		else 
			if(code[i]=='1'&&code[i+1]=='0')
			{
				a[i/2]=1;
			}
		    else 
			{
				cout<<"the Manchester code input is wrong,can't translate into original code."<<endl;
				return;//想在如果出现这个ELSE情况的时候就跳出FOR循环。。。。

			}
	}    
	for(i=0;i<len/2;i++)
	{
		cout<<a[i];
	} 

	cout<<endl;
}

/*void Decipher_DM(char code[]) //translate Differential Manchester code into original one.
{
	int i,len,a[size];
	len=strlen(code);
	while(len%2)
	{
		cout<<"the Differential Manchester code input is wrong.please input again:"<<endl;
		cin>>code;
		len=strlen(code);
	}
	while(len>size*2) 
	{
		cout<<"the code input is beyond length limit.please input again:"<<endl;
		cin>>code;
		len=strlen(code);
	}
	if(code[0]=='0'&&code[1]=='1') a[0]=0;
	else if(code[0]=='1'&&code[1]=='0') a[0]=1;
	else cout<<"the code input is wrong.can't translate into original code."<<endl;
	for(i=2;i<len;i+=2)
	{
		if(code[i-1]=='0')
			if(code[i]=='0'&&code[i+1]=='1') a[i/2]=1;
			else if(code[i]=='1'&&code[i+1]=='0') a[i/2]=0;
			     else cout<<"the code input is wrong.can't translate into original code."<<endl;
		else if(code[i-1]=='1')
			if(code[i]=='1'&&code[i+1]=='0') a[i/2]=1;
			else if(code[i]=='0'&&code[i+1]=='1') a[i/2]=0;
			     else cout<<"the code input is wrong.can't translate into original code."<<endl;
	}
	for(i=0;i<len/2;i++)
		cout<<a[i];
	cout<<endl;
}*/


void main()
{
	int choice;
	char code[size];

	Display();
	cin>>choice;
	cout<<"input a binary string: ";
	cin>>code;
	while(choice)
	{
		switch(choice)
		{
			case 1: Encipher_M(code); break;
//			case 2: Encipher_DM(code); break;
			case 3: Decipher_M(code);break;
//			case 4: Decipher_DM(code);break;
			default: cout<<"false input.:"<<endl;
		}
		Display();
		cin>>choice;
	}
} 