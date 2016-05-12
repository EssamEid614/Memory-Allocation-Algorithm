#include <iostream>
#include <string>
#include <math.h>
#include "Sorting.h"
using namespace std;

void main()
{
	int NumberOfEmpty = 0;
	cout << "enter the Number of Empty memory locations" << endl;
	cin >> NumberOfEmpty;
	memory ToPushList;
	list<memory> SortedEmptyList;
	string TempString;
	int TempInt;
	int counter = 0;
	//getting inputs loop
	while (counter < NumberOfEmpty)
	{
		ToPushList.SetName("Empty");
		cout << "enter the starting address of Empty" << endl;
		cin >> TempInt;
		ToPushList.SetStartAddress(TempInt);
		cout << "enter the size of Empty" << endl;
		cin >> TempInt;
		ToPushList.SetSize(TempInt);
		ToPushList.SetEndAddress(ToPushList.GetSize() + ToPushList.GetStartAddress());
		counter++;
		SortedEmptyList.push_back(ToPushList);
	}

	//getting process input from user
	cout << "enter the number of entering new processes" << endl;
	int NumberOfProcesses;
	cin >> NumberOfProcesses;
	int counter1 = 0;
	memory *NewProcess = new memory[NumberOfProcesses];
	while (counter1 < NumberOfProcesses)
	{
	cout << "enter the name of process" << endl;
	cin >> TempString;
	NewProcess[counter1].SetName(TempString);
	cout << "enter the size of process" << endl;
	cin >> TempInt;
	NewProcess[counter1].SetSize(TempInt);
	counter1++;
	}
	int Choice;
	ReEnterChoice:
	cout << "Choose the algorithm ... 1 for first fit , 2 for best fit" << endl;
	cin >> Choice;
	if(Choice==1)
	{ 
		//first fit algorithm
		//sort empty with address
		SortedEmptyList.sort(CompFirstAddress);
		int TempHolderForSize = 0;
		for (int counter = 0; counter < NumberOfProcesses; counter++)
		{
			for (list<memory>::iterator i = SortedEmptyList.begin(); i != SortedEmptyList.end(); ++i)
			{
				if (i->GetSize() >= NewProcess[counter].GetSize() && i->GetName()=="Empty")
				{
					int SizeAfterAdding = 0;
					NewProcess[counter].SetStartAddress(i->GetStartAddress());
					NewProcess[counter].SetEndAddress(NewProcess[counter].GetStartAddress() + NewProcess[counter].GetSize());
					SizeAfterAdding = i->GetSize() - NewProcess[counter].GetSize();
					SortedEmptyList.erase(i);
					SortedEmptyList.push_back(NewProcess[counter]);
					//adding an empty slot
					if (SizeAfterAdding != 0)
					{
						memory temp;
						temp.SetName("Empty");
						temp.SetStartAddress(NewProcess[counter].GetEndAddress());
						temp.SetSize(SizeAfterAdding);
						temp.SetEndAddress(temp.GetStartAddress()+temp.GetSize());
						SortedEmptyList.push_back(temp);
					}
					goto SortEmptyAndRepeat;
				}
			}

			//replacment code is here
			//if condition to check if current process size > new process size OR if current process size > new process size +next if next is empty 
			
			ReplaceAProcess(SortedEmptyList, NewProcess[counter]);
		SortEmptyAndRepeat:
			//call a function to remove the empty and make them 1 slot
			//function has to check not only for next is empty but also for current end address and next start address are equal to merge both slots into 1 otherwise it doesnt edit
			SortedEmptyList.sort(CompFirstAddress);
			cout << "After Process number " << counter + 1 <<"the memory will be " << endl << endl;
			//print here
			PrintTheList(SortedEmptyList);
		}
	}
	else if (Choice == 2)
	{
		//best fit algorithm
		//sort empty with resepct to size
		int TempHolderForSize = 0;
		for (int counter = 0; counter < NumberOfProcesses; counter++)
		{
			SortedEmptyList.sort(CompFirstSize);
			for (list<memory>::iterator i = SortedEmptyList.begin(); i != SortedEmptyList.end(); ++i)
			{
				if (i->GetSize() >= NewProcess[counter].GetSize() && i->GetName() == "Empty")
				{
					int SizeAfterAdding = 0;
					NewProcess[counter].SetStartAddress(i->GetStartAddress());
					NewProcess[counter].SetEndAddress(NewProcess[counter].GetStartAddress() + NewProcess[counter].GetSize());
					SizeAfterAdding = i->GetSize() - NewProcess[counter].GetSize();
					SortedEmptyList.erase(i);
					SortedEmptyList.push_back(NewProcess[counter]);
					//adding an empty slot
					if (SizeAfterAdding != 0)
					{
						memory temp;
						temp.SetName("Empty");
						temp.SetStartAddress(NewProcess[counter].GetEndAddress());
						temp.SetSize(SizeAfterAdding);
						temp.SetEndAddress(temp.GetStartAddress() + temp.GetSize());
						SortedEmptyList.push_back(temp);
					}
					goto SortEmptyAndRepeatBestFit;
				}
			}
		SortEmptyAndRepeatBestFit:
			SortedEmptyList.sort(CompFirstAddress);
			cout << "After Process number " << counter + 1 << " the memory will be " << endl << endl;
			//print here
			PrintTheList(SortedEmptyList);
		}
		
	}
	else
	{
		cout << "Invalid Choice" << endl;
		goto ReEnterChoice;
	}
	
	system("pause");
	}
