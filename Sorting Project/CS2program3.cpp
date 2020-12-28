//***************************************************************************************
// CMPS 1063    											  Program Assignment : 03	*
// William Jarboe			   															*
// This progam will search and order SyfyPersons data                                   *
// Date : 02-14-2018																    *
//***************************************************************************************
//Catherine Stringfellow and  William Jarboe
//Program 3:  This program sorts an array after reading it in, then gives options
//to efficiently search and sort the array.

#include "SyfyPerson.h"
#include "List.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

//prototypes

//opens files
void openFiles (ifstream & infile, ofstream & outfile);

//prints the heading of the program to the file
void printHeading(ofstream & outfile);

//gets SyfyPeople from the input file
void getSyfyPeople(ifstream & infile, List & spList);

//print the Syfy person list (names and salaries)
void printList (const List & spList, ofstream & outfile, int headerID);

//perform Lookups
void performLookups(const List & spList);

//prints the results of finding the  Syfy Person
void printResult (const SyfyPerson & p, bool found, int numComp);


//main function
int main ()
{
	//variables for input and output streams, a SyfyPerson and a List
	ifstream infile;
	ofstream outfile;
	List mylist = List(62);

	//Open files and print headings
	openFiles(infile, outfile);
	printHeading(outfile);
	//read in ALL Syfy People
	getSyfyPeople(infile, mylist);
	//print list
	printList(mylist, outfile, 1);
	//call a function to perform lookups
	performLookups(mylist);
	//sort list in descending order of Salary
	mylist.SalarySort();
	//print list again
	printList(mylist, outfile, 2);
	//Close the files
	infile.close();
	outfile.close();
	return 0;
}


//printing the heading using out file
void printHeading(ofstream & outfile)
{
	//printing out heading
	outfile <<"William Jarboe \nProgram 3" << endl<<endl;
	outfile<<"Welcome to the SyfyPersons Program."<<endl;
	outfile<<"============================================"<<endl<<endl;
	//print out the column headings
	outfile << "Sorted Syfy Entries by Name:\n";
	outfile<<setw(25) << left <<"SyfyPerson"<<setw(20)<<"Salary ($)"<<" "<<endl<<endl;
}

//FUNCTION DONE


//opening files
void openFiles (ifstream & infile, ofstream & outfile)
{
	char infileName[30];
	char outfileName[30];

	//print heading to the display
	cout << "Welcome to the  SyfyPerson Program " << endl << endl;

	//asking for infile name and opening infile
	cout<<"Enter name of input file: ";
	cin>>infileName;
	infile.open(infileName);
	
	//asking for outfile name and opening outfile
	cout<<"Enter name of output file: ";
	cin>>outfileName;
	outfile.open(outfileName);

	cout<<endl<<endl;
}

//FUNCTION DONE

//get a SyfyPerson from the file
void getSyfyPeople(ifstream & infile, List & spList)
{   
	SyfyPerson p;
	string name;
	double eSal;
	char junk;

	//get a name
	getline(infile, name);

	//while more SyFyPersons and the spLIst is not full
	while (!infile.eof())
	{
		infile >> eSal;
		infile.get(junk); //get that last space on the line getline later

		//set the SyfyPerson and add to the list

		p.changeName(name);
		p.changeSalary(eSal);
		spList.addSyfyPerson(p);


		//get another name
		getline(infile, name);
	}
}

//FUNCTION DONE




//Perform Lookups
void performLookups(const List & spList)
{
	

	SyfyPerson p;
	int numComparisons = 0;
	cout << "Looked up using Linear Search:\n";
	//loop 3 times
	for (int count = 1; count <= 3; count++)
	{
		cout << "\n\n";
		//prompt for name, input it and store in p
		string tempname;
		bool found = false;
		cout << "Please enter a name to look up:\t";
		cin >> tempname;
		p.changeName(tempname);
		//call Lookup1
		found = spList.Lookup1(p, numComparisons);
		//print result
		printResult(p, found, numComparisons);
		numComparisons = 0;
	}
	cout << "\nLooked up using Binary Search:\n";
	for (int count = 1; count <= 3; count++)
	{
		cout << "\n\n";
		//prompt for name, input it and store in p
		string tempname;
		bool found = false;
		cout << "Please enter a name to look up:\t";
		cin >> tempname;
		p.changeName(tempname);
		//call Lookup1
		found = spList.Lookup2(p, numComparisons);
		//print result
		printResult(p, found, numComparisons);
		numComparisons = 0;
	}
	cout << "\n\nP.S. I was assuming the back of the sheet was intended to purely be 'cout', as it" <<
		"seemed to deal a lot more with it, and the front page only the list, sorted.";
}




void printResult(const SyfyPerson & p, bool found, int numComp)
{
	cout << left << setw(20) << p.provideName();
	if (found)
	{
		cout << setw(15) << p.provideSalary();
	}
	else
	{
		cout << setw(15) << "..not in the list..";
	}
	cout << setw(8) << numComp << " comparisons were made.";
}




void printList(const List & spList, ofstream & outfile, int headerID)
{
	outfile << "\n\n\n";
	if (headerID == 2)
	{
		outfile << "============================================" << endl << endl;
		//print out the column headings
		outfile << "Sorted Syfy Entries by Salary:\n";
		outfile << setw(25) << left << "SyfyPerson" << setw(20) << "Salary ($)" << " " << endl << endl;
		//1 is already taken care of for this prog.. had the program been any bigger,
		//a unique case would be an extinct concept
	}
	SyfyPerson q;
	for (int i = 0; i < spList.getSize(); i++)
	{
		spList.getSyfyPerson(i, q);
		outfile << left << setw(20) << q.provideName() << "   $ " << setw(8) << q.provideSalary() << "\n";
	}
}