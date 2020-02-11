#include <iostream>
#include<fstream>
#include <string>
using namespace std;


void reverse(char *a, int b, int e)
{
   char ch;
	if (b >= e)
	{
      return;
	}
	ch= *(a+b);
   *(a+b) = *(a+e);
   *(a+e)   = ch;
	reverse(a, ++b, --e);
}

int main()
{
	ifstream fin;
	ofstream fout;
	fout.open("Output File.txt");
	bool flag = 1;
	fin.open("Input File.txt");
	if(fin.is_open())
	{
		cout<<"Successfully opened"<<endl;
	}
	char buf[100];
	int s=0;
	cin.ignore();
	while (!fin.eof())
	{
		buf[s]=fin.get();
		s++;
		for(int i = 0; flag==1 && buf[i]!='\0';i++)
		{
			if (buf[i] == 'a' || buf[i] =='e' || buf[i] =='i' || buf[i] =='o' || buf[i] =='u'||
				buf[i] == 'A' || buf[i] =='E' || buf[i] =='I' || buf[i] =='O' || buf[i] =='U')
			{
				flag = 0;
			}
		}
		int count=0;
		for(int i=0;buf[i]!='\0';i++)
		{
			count++;
		}


		if(flag==0)
		{
			reverse(buf, 0, count);
			fout<<buf<<" ";			
		}
		flag = 1;
	}
	return 0;
}





