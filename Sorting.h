#include <iostream>
#include <string>
#include "Memory.h"
#include <list>
using namespace std;


bool CompFirstSize(memory a,memory b) 
{
	return a.GetSize() < b.GetSize();
}
bool CompFirstAddress(memory a, memory b)
{
	return a.GetStartAddress() < b.GetStartAddress();
}



list<memory> SortMainMemory(list<memory>SortedFullList, list<memory>SortedEmptyList)
{
	list<memory> MainMemory;
	list<memory>::iterator FullListIterator = SortedFullList.begin();
	list<memory>::iterator EmptyListIterator = SortedEmptyList.begin();
	for (FullListIterator; FullListIterator != SortedFullList.end(); ++FullListIterator)
	{
		for (EmptyListIterator; EmptyListIterator != SortedEmptyList.end(); ++EmptyListIterator)
		{

			if (EmptyListIterator->GetStartAddress() < FullListIterator->GetStartAddress())
			{
				MainMemory.push_back(*EmptyListIterator);

			}
			else
			{
				goto PushFull;
			}
		}
	PushFull:
		MainMemory.push_back(*FullListIterator);
	}
	return MainMemory;
}
void PrintTheList(list<memory> SortedEmptyList)
{
	cout << "Process Name / Empty        StartAddress        EndAddress" << endl;
	for (list<memory>::iterator i = SortedEmptyList.begin(); i != SortedEmptyList.end(); ++i)
	{
		if (i->GetName() != "Empty")
		{
			cout << i->GetName() << "                              ";
		}
		else
		{
			cout << i->GetName() << "                           ";
		}
		cout << i->GetStartAddress() << "                   ";
		cout << i->GetEndAddress() << "                   ";
		cout << endl;
	}
}

void ReplaceAProcess(list<memory> &SortedEmptyList,memory NewProcess)
{
	
	memory current;
	memory next;
	list<memory>::const_iterator second = SortedEmptyList.begin(),
		end = SortedEmptyList.end();
	for (std::list<memory>::const_iterator first = second++;second != end;first++, second++)
	{
		current = *first;
		next = *second;
		if (current.GetSize() >= NewProcess.GetSize())
		{
			int SizeAfterAdding = 0;
			NewProcess.SetStartAddress(current.GetStartAddress());
			NewProcess.SetEndAddress(NewProcess.GetStartAddress() + NewProcess.GetSize());
			SizeAfterAdding = current.GetSize() - NewProcess.GetSize();
			SortedEmptyList.erase(first);
			SortedEmptyList.push_back(NewProcess);
			//adding an empty slot
			if (SizeAfterAdding != 0)
			{
				memory temp;
				temp.SetName("Empty");
				temp.SetStartAddress(NewProcess.GetEndAddress());
				temp.SetSize(SizeAfterAdding);
				temp.SetEndAddress(temp.GetStartAddress() + temp.GetSize());
				SortedEmptyList.push_back(temp);
			}
			return;
		}
		else if ((current.GetSize() + next.GetSize() >= NewProcess.GetSize()) && (next.GetName()=="Empty"|| current.GetName()=="Empty") && (current.GetEndAddress()==next.GetStartAddress()))
		{
			int SizeAfterAdding = 0;
			NewProcess.SetStartAddress(current.GetStartAddress());
			NewProcess.SetEndAddress(NewProcess.GetStartAddress() + NewProcess.GetSize());
			SizeAfterAdding = current.GetSize()+next.GetSize() - NewProcess.GetSize();
			SortedEmptyList.erase(first);
			SortedEmptyList.erase(second);
			SortedEmptyList.push_back(NewProcess);
			//adding an empty slot
			if (SizeAfterAdding != 0)
			{
				memory temp;
				temp.SetName("Empty");
				temp.SetStartAddress(NewProcess.GetEndAddress());
				temp.SetSize(SizeAfterAdding);
				temp.SetEndAddress(temp.GetStartAddress() + temp.GetSize());
				SortedEmptyList.push_back(temp);
			}
			//still to make logic here
			return;
		}

	}
}