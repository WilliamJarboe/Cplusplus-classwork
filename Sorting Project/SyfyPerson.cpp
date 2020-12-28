//Catherine Stringfellow and   ???
#include "SyfyPerson.h"
using namespace std;

//constructors and destructor
SyfyPerson::SyfyPerson ()
{
	name ="";
	epSalary = 0;
}

SyfyPerson::SyfyPerson(string newName, double esal)
{
	name = newName;
	epSalary = esal;
}

SyfyPerson::SyfyPerson(const SyfyPerson & otherPerson)
{
	name = otherPerson.name;
	epSalary = otherPerson.epSalary;
}

SyfyPerson::~SyfyPerson ()
{
}

// getting the SyfyPersons information
string SyfyPerson::provideName()const
{
	return name;
}

double SyfyPerson::provideSalary()const
{
	return epSalary;
}

//modifying the name and sales
void SyfyPerson::changeName(string newName) 
{
	name = newName;
}

void SyfyPerson::changeSalary (double esal)
{
	epSalary = esal;
}

void SyfyPerson::swapInfo(SyfyPerson & other)
{
	string tempname = other.name;
	double tempsalary = other.epSalary;
	other.changeSalary(this->epSalary);
	other.changeName(this->name);
	this->changeSalary(tempsalary);
	this->changeName(tempname);
}



