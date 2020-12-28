#pragma once
#include <string>
using namespace std;

//***************************************************************************************
// CMPS 1063    											  Program Assignment : 03	*
// Catherine Stringfellow                                                               *
// This file declares the SyfyPerson class                                              *
// Due date : 09-17-2014																*
//***************************************************************************************

//SyfyPerson class 
class SyfyPerson
{ 
	private:
		string name;
		double epSalary;
	
	public:
		//constructor and destructor
		SyfyPerson ();
		SyfyPerson(string nname, double esal);
		SyfyPerson(const SyfyPerson & otherPerson);   //not necessary
		~SyfyPerson ();
		
		// getting the SyfyPersons information
		string provideName() const;
		double provideSalary() const;
	
		//modifying the name and sales
	    void changeName(string newName);
		void changeSalary(double esal);

		//swap this persons' info with the other person's info
		void swapInfo(SyfyPerson & other);

};
		