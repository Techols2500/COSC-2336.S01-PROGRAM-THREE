//************************************************************************** 
//
// Programming Excerise 3   
// CLASS: COSC 2336.S01
// AUTHOR: TYLER ECHOLS 
// DAtE: Oct 2017  
//
//************************************************************************** 

#include "RAFiles.h"
#include <iostream>

RAFiles::RAFiles() : NumRecords(0)
{
}

RAFiles::~RAFiles()
{
	Closefile();
}

bool RAFiles::Closefile()
{
	if (!File.is_open())
	{
		return false;
	}
	else
	{
		File.seekp(0);
		File.write((const char *)&NumRecords, sizeof(NumRecords));
		File.seekp(EndOfDataRecords);
		for (int k = 0; k < NumRecords; k++)
		{
			File.write((const char *)&recordData[k], sizeof(RecInfo));
		}
		return true;
	}
}

bool RAFiles::Openfile(string FileName)
{
	if (File.is_open())
	{
		return false;
	}
	else
	{
		File.open(FileName, ios_base::in | ios_base::out | ios_base::binary);
		if (!File.is_open())
		{
			File.clear();
			File.open(FileName, ios_base::out | ios_base::binary);
			if (File.is_open())
			{
				NumRecords = 0;
				File.write((char *)&NumRecords, sizeof(size_t));
				File.close();
				File.open(FileName, ios_base::in | ios_base::out | ios_base::binary);
				if (!File.is_open())
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		File.read((char *)&NumRecords, sizeof(size_t));
		File.seekg(-(int)(NumRecords * sizeof(RecInfo)), ios_base::end);
		EndOfDataRecords = File.tellg();
		for (int k = 0; k < NumRecords; k++)
		{
			File.read((char *)&recordData[k], sizeof(RecInfo));
		}
		return true;
	}
}


bool RAFiles::Get(size_t Index, string & Data)
{
	if (File.is_open())
		if (Index < NumRecords)
		{
			if (recordData[Index].Length > 0)
			{
				char *	pChar;
				pChar = new char[recordData[Index].Length + 1];
				File.seekg(recordData[Index].Offset);
				File.read(pChar, recordData[Index].Length);
				pChar[recordData[Index].Length] = '\0';
				Data = pChar;
				delete[] pChar;
			}
			else
				Data = "";
			return true;
		}
		else
			return false;
	else
		return false;
}


bool RAFiles::Replace(size_t x, string y)
{
	if (!File.is_open())
	{
		return false;
	}
	else
	{
		if ((x <= NumRecords) && (x >= 0))
		{
			if (y.length() <= recordData[x].Length)
			{	// the new data will fit into where the record is now
				File.seekp(recordData[x].Offset);
				File.write(y.c_str(), y.length());
				recordData[x].Length = y.length();
				return true;
			}
			else
			{	// data does not fit
				addNewRecord(x, y);
				NumRecords--;
				return true;
			}
		}
		else
		{
			for (int k = NumRecords; k < x; k++) //adds blank records to fill in the spaces in the array for the empty indeces between the end of the current records and the index inputted for the new one
			{
				recordData[k].Offset = 0;
				recordData[k].Length = 0;
				NumRecords++;
			}
			addNewRecord(x, y);
			return true;
		}
	}
	return false;
}


bool RAFiles::Insert(size_t i, string s)
{
	if ((NumRecords < i) && (i > 0))//inserts it at the end and makes empty indeces to fill any blank spaces in the array
	{
		for (int k = NumRecords; k < i; k++) //adds blank records to fill in the spaces in the array for the empty indeces between the end of the current records and the index inputted for the new one
		{
			recordData[k].Offset = 0;
			recordData[k].Length = 0;
			NumRecords++;
		}
		addNewRecord(i, s);
		return true;
	}
	else
	{
		if (NumRecords == 0) //if the array was empty. 
		{
			for (int k = NumRecords; k < i; k++) //adds blank records to fill in the spaces in the array for the empty indeces between the end of the current records and the index inputted for the new one
			{
				recordData[k].Offset = 0;
				recordData[k].Length = 0;
				NumRecords++;
			}
			addNewRecord(i, s);
			return true;
		}
		else
		{
			int newIndex = recordData.Size() + 1;

			recordData[newIndex];//makes a new slot so that we can shift the records. 
			recordData[newIndex].Offset = 0;
			recordData[newIndex].Length = 0;

			for (int k = newIndex; k > i; k--)
			{
				recordData[k] = recordData[k - 1];
			}
			addNewRecord(i, s);
			return true;
		}
	}
}

int RAFiles::size()
{
	return NumRecords;
}

bool RAFiles::addNewRecord(size_t i, string s)
{
	File.seekp(EndOfDataRecords);
	File.write(s.c_str(), s.length());
	recordData[i].Offset = EndOfDataRecords;
	recordData[i].Length = s.length();
	EndOfDataRecords = File.tellp();
	NumRecords++;
	return true;
}