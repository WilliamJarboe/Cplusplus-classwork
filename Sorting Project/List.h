#include "SyfyPerson.h"

const int SIZE = 100;

//class created to read the x and y for each SyfyPerson
class List 
{ 
	private:
		//number of people in list
		int count; 

		//size of array allocated
		int size;

		//using SyfyPersons as an array
		SyfyPerson * sfpersons;
	
	public:
		//constructor and destructor
		List();
		List(int newSize);
		List(const List & other);
		~List();
		
		//add SyfyPerson into list in alphabetical order
		void addSyfyPerson (SyfyPerson SyfyPerson);
		
		//remove a person from the list - we will not be implementing this
		//void removeSyfyPerson(int index);

		//getting the SyfyPerson at the location index in the list
		void getSyfyPerson(int index, SyfyPerson & sp)const;

		//get the number of people in the array SyfyPersons
		int getNumSFPeople()const;

		//get max capacity
		int getSize()const;

		//sort the list by salary
		void SalarySort();

		//look up name of SyfyPerson in list using linear search
		//return:  name and esal of SyfyPerson (if found) and numComp
		//         and return true if founc, false otherwise
		bool Lookup1(SyfyPerson & p, int & numComp) const;

		//look up name person in list using binary search
		//return:  name and esal of SyfyPerson (if found) and numComp
		//         and return true if founc, false otherwise
		bool Lookup2(SyfyPerson & p,int & numComp) const;

}; 