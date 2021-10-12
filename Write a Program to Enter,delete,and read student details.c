#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include <string>
using namespace std;
int main()
{
	string rollno;
	string name;
	string email;
	ifstream fin;
	ofstream fout;
	
	int opt = 0;
	cout << "Press 1 to enter students details:\n";
	cout << "Press 2 to delete students details:\n";
	cout << "Press 3 to read  students details:\n";
	cout<< "Press -1 to exit the Menu\n";
	cin >> opt;
		while (opt != -1)
		{
			if (opt == 1)
			{
				fout.open("output.txt");
				if (fout.is_open())
				{
					cout << "File opened successfully"<<endl<<endl;
				}
                cin.ignore();
				cout<<"PLEASE ENTER YOUR DESIRE DATA"<<"\n"<<"\n";
				cout << "enter roll no"<<"\n";
				getline(cin, rollno);
				cout << "enter name "<<"\n";
				getline(cin, name);
				cout << "enter email"<<"\n";
				getline(cin, email);
					fout <<rollno << "\t" << name << "\t" << email;
					fout << endl;
				fout.close();
			}
			if(opt==2)
			{
				cout << "enter rollno =";
				string rollno;
				string line;
				cin.ignore();
				getline(cin, rollno);
				fout.open("output.txt");
				if (fout.is_open())
				{
					while (getline(fin, line))
					{
						if (line == rollno)
						{
							line.replace(line.find(rollno), rollno.length(), "");
							fout << line;
						}
					}
					fout.close();
				}
				else
				{
					cout << "not opening" << endl;
				}
			}


			if (opt == 3)
			{
				cout << "enter rollno =";
				string rollcall;
				string line;
				cin.ignore();
				getline(cin, rollcall);
				fin.open("output.txt");
				if(fin.is_open())
				{
					while(!fin.eof())
					{
						getline(fin,line);
						size_t found = line.find(rollcall); 
						if (found != string::npos) 
						{
							cout<<line;
						}
					}
					cout<<"\n";
					fin.close();
				}
				else
				{
					cout<<"not opening"<<endl;
				}
				}
				

			
			cout << "Press 1 to enter students details:\n";
			cout << "Press 2 to delete students details:\n";
			cout << "Press 3 to read  students details:\n";
			cout<< "Press -1 to exit the Menu\n";
			cin >> opt;
		}
}
