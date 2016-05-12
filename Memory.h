#include <iostream>
#include <string>

using namespace std;

class memory
{
private:
	int StartAddress;
	int EndAddress;
	int size;
	string name;
public:
	//setters 
	void SetStartAddress(int x)
	{
		StartAddress = x;
	}
	void SetEndAddress(int x)
	{
		EndAddress = x;
	}
	void SetSize(int x)
	{
		size = x;
	}
	void SetName(string s)
	{
		name = s;
	}
	//getters
	int GetStartAddress()
	{
		return StartAddress;
	}
	int GetEndAddress()
	{
		return EndAddress;
	}
	int GetSize()
	{
		return size;
	}
	string GetName()
	{
		return name;
	}
};