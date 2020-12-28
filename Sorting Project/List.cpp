#include "List.h"
#include <iostream>
#include <iomanip>
using namespace std;

//constructors
List::List()
{
	count = 0;
	size = SIZE;
	sfpersons = new SyfyPerson[size];
}

List::List(int newSize)
{
	count = 0;
	size = newSize;
	sfpersons = new SyfyPerson[size];
}

List::List(const List & other)
{
	count = 0;
	size = other.size;
	sfpersons = new SyfyPerson[size];
	for (int i = 0; i < count; i++)
	   addSyfyPerson(other.sfpersons[i]);
}

//destructor
List::~List()
{
	count = 0;
	size = 0;
	delete[] sfpersons;
}

//adding SyfyPerson
void List::addSyfyPerson (SyfyPerson sp)
{
	if (count < SIZE)
	{
		sfpersons[count] = sp;
		count++;
	}
	else 
		cout<<"Error! Exceeded size of array."<<endl;

	for (int i = count-1; i > 0; i--)
	{
		if (sfpersons[i].provideName() < sfpersons[i - 1].provideName())
		{
			sfpersons[i].swapInfo(sfpersons[i - 1]);
		}
	}

}
/*removing SyfyPerson
void List::removeSyfyPerson (int index)
{ 
	for (int i=index; i <count-1; i++)
	{
		sfpersons[i] = sfpersons [i+1];
	}
	count--;
} 
*/

//getting SyfyPerson from SyfyPerson class
void List ::getSyfyPerson(int index, SyfyPerson & sp) const
{
	if (index < count)
	{
		sp.changeName (sfpersons [index].provideName());
		sp.changeSalary(sfpersons[index].provideSalary());
	}
	else
		cout<<"Error! Cannot access SyfyPerson " << index << "." <<endl;
}

//returning count of number people in list
int List::getNumSFPeople() const
{ 							
	return count;			
}							
							
//returning capacity of list 
int List::getSize() const	
{							
	return size;			
}							
							
//sort the list by salary	
void List::SalarySort()
{
	for (int sorteduntil = 1; sorteduntil < count; sorteduntil++)
	{
		for (int i = sorteduntil; i > 0; i--)
		{
			if (sfpersons[i].provideSalary() > sfpersons[i - 1].provideSalary())
			{
				sfpersons[i].swapInfo(sfpersons[i - 1]);
			}
		}
	}
}

//FUNCTION COMPLETED

//look up person in list using linear search
bool List::Lookup1(SyfyPerson & p, int & numComp)const
{		
	for (int i = 0; i < getSize(); i++)
	{	
		numComp++;
		if (p.provideName() == sfpersons[i].provideName())
		{
			p.changeSalary(sfpersons[i].provideSalary());
			return true;
		}
	}
	return false;
}

//FUNCTION COMPLETED

//look up person in list using binary search
bool List::Lookup2(SyfyPerson & p, int & numComp)const
{
	int low = 0;
	int high = count;
	int mid = count / 2;

	string comp = sfpersons[mid].provideName();



	while (comp.compare(p.provideName()) != 0)
	{
		numComp++;
		cout << comp << "\n";


		if (comp.compare(p.provideName()) < 0)
		{
			low = mid;
		}
		else
		{
			high = mid;
		}
		mid = (low + high) / 2;
		comp = sfpersons[mid].provideName();

		//handles when the numbers are extremely close together.
		if (mid == low || mid == high)
		{
			if (sfpersons[low].provideName() == p.provideName())
			{
				p = sfpersons[low];
				return true;
			}
			else if (sfpersons[high].provideName() == p.provideName())
			{
				p = sfpersons[high];
				return true;
			}
			else
			{
				return false;
			}
		}
	}
		p = sfpersons[mid];
		return true;
}

