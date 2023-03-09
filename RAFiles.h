//************************************************************************** 
//
// Programming Excerise 3   
// CLASS: COSC 2336.S01
// AUTHOR: TYLER ECHOLS 
// DAtE: Oct 2017  
//
//************************************************************************** 

#ifndef RA_FILE_H
#define RA_FILE_H

#include <fstream>
#include <string>
#include <string.h>
#include "WCS_Pointer.h" 
#include "UBArray.h"
#include <vector>

using namespace std;

class RAFiles
{
private:
	struct RecInfo
	{
		streamoff Offset; 
		size_t	  Length;  
	};
public:
	RAFiles();
	~RAFiles();
	bool Closefile();
	bool Openfile(string);

	bool Get(size_t, string &);
	bool Replace(size_t, string);
	bool Insert(size_t, string);
	int size();
	bool		IsOpen() const;


private:
	RAFiles(const RAFiles &);
	RAFiles &	operator =	(const RAFiles &);
	bool addNewRecord(size_t, string);

	int							NumRecords;
	streampos						EndOfDataRecords;
	fstream							File;
	UBArray <RecInfo, size_t>	recordData;
	vector<string> stringVector;



};

inline bool RAFiles::IsOpen() const
{
	return File.is_open();
}

#endif

