/*William Jarboe
*-CMPS 1044 - Ranette Halverson
*-Program 3 - Division of Nlogonia
*-10/11/2017
*-This program will take in a proposed division point,
*-and then any number of house locations, and will display
*-what country the house is in.
*/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	//declare division point location and current location
	int divisionX, divisionY;
	int currentX, currentY;
	//holds data about position of house
	char h;
	//declare+open input and output file
	ifstream infile;
	ofstream outfile;
	infile.open("input.txt");
	outfile.open("output1.txt");
	//header on output file
	outfile << "William Jarboe \n\n";
	//get the division point location
	infile >> divisionX >> divisionY;
	//print out the division point location to the file
	outfile << "The division point is " << divisionX <<
		", " << divisionY << "\n";
	while (!infile.eof()) //loop for every line in input file
	{
		//get current house location
		infile >> currentX >> currentY;
		//print current house location and a little space
		outfile << setw(5) << currentX << setw(5) <<
			currentY << "  ";
		if (currentX > divisionX) //if to the right of d.p.
		{
			if (currentY > divisionY) //if above d.p.
			{
				//is in kiowa
				h = 'k';
			}
			else if (currentY < divisionY) //if below d.p.
			{
				//is in tepee
				h = 't';
			}
			else //if is equal to d.p.
			{
				//borders kiowa and tepee
				h = 'x';
			}
		}
		else if (currentX < divisionX) //if to the left of d.p.
		{
			if (currentY > divisionY) //if above d.p.
			{
				//is in comanche
				h = 'c';
			}
			else if (currentY < divisionY) //if below d.p.
			{
				//is in nocona
				h = 'n';
			}
			else //if is equal to d.p.
			{
				//borders comanche and nocona
				h = 'z';
			}
		}
		else //is vertically aligned with d.p.
		{
			if (currentY > divisionY) //is above d.p.
			{
				//borders comanche and kiowa
				h = 'w';
			}
			else if (currentY < divisionY) //is below d.p.
			{
				//borders nocona and tepee
				h = 'y';
			}
			else //is on d.p.
			{
				h = 'd';
			}
		}
		//switch statement checks the
		//held value to determine city
		//location.
		switch (h)
		{
		case 'k' :
			//is in kiowa
			outfile << "Kiowa\n";
			break;
		case 'x':
			//borders kiowa and tepee
			outfile << "Kiowa and Tepee\n";
			break;
		case 't':
			//is in tepee
			outfile << "Tepee\n";
			break;
		case 'y':
			//borders tepee and nocona
			outfile << "Nocona and Tepee\n";
			break;
		case 'n':
			//is in nocona
			outfile << "Nocona\n";
			break;
		case 'z':
			//borders nocona and comanche
			outfile << "Comanche and Nocona\n";
			break;
		case 'c':
			//is in comanche
			outfile << "Comanche\n";
			break;
		case 'w':
			//borders comanche and kiowa
			outfile << "Comanche and Kiowa\n";
			break;
		case 'd':
			//is on division point..
			outfile << "Division Point.\n";
			break;
		}
	} //end while; reached end of input file after this line
	  //it is always important to close your files.
	infile.close();
	outfile.close();
}