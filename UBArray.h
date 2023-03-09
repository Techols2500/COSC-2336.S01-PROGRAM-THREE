//************************************************************************** 
//
// Programming Excerise 3   
// CLASS: COSC 2336.S01
// AUTHOR: TYLER ECHOLS 
// DAtE: Oct 2017  
//
//************************************************************************** 

#ifndef UBARRAY_H
#define UBARRAY_H

#include "WCS_Pointer.h"


template <class DATA, class INDEX = int>
class UBArray
{

public:
	enum Exceptions { OK, InvalidIndex, ArrayEmpty, NoNextElement, NoPrevElement, InteratorNotInitiailized };
protected:
	struct Node : public RefCount
	{
		INDEX				index;
		DATA				Data;
		WCS_Pointer <Node>	pNext;
		WCS_Pointer <Node>	pPrev;

		Node(const INDEX &);
		~Node();
	};
	//______________________ Methods _______________________________________
public:
	UBArray();
	virtual ~UBArray();
	DATA &								At(const INDEX &);

	const DATA &						At(const INDEX &) const;

	const DATA &						GetFirst()const;


	const DATA &						GetNext()const;


	const DATA &						GetPrev()const;


	const DATA &						GetLast()const;


	void								DeleteAll();


	bool						Remove(INDEX);
	int							Size() const;
	DATA &						operator []	(const INDEX &);
	DATA &				operator [] (const INDEX &) const;
	//______________________ Properties _______________________________________
protected:
	UBArray(const UBArray <DATA, INDEX> &);
	UBArray <DATA, INDEX> &	operator =	(const UBArray <DATA, INDEX> &);

	WCS_Pointer <Node>			pHead;
	WCS_Pointer <Node>			pTail;
	mutable	WCS_Pointer <Node>			pCurrent;
	size_t							numElements;
};
//______________________ Method Definitions _______________________________________
template <class DATA, class INDEX>
UBArray <DATA, INDEX>::Node::Node(const INDEX & i) : index(i)
{

}

template <class DATA, class INDEX>
UBArray <DATA, INDEX>::Node::~Node()
{
#ifdef _DEBUG

	cout << "Node has been deleted" << endl;
#endif
}

template <class DATA, class INDEX>
UBArray <DATA, INDEX>::UBArray() : numElements(0)
{

}

template <class DATA, class INDEX>
UBArray <DATA, INDEX>::~UBArray()
{

}

template <class DATA, class INDEX>
inline DATA & UBArray <DATA, INDEX>::At(const INDEX & i)
{

	return operator [] (i);
}

template <class DATA, class INDEX>
const DATA & UBArray <DATA, INDEX>::GetFirst() const
{
	if (!pHead)
		throw ArrayEmpty;
	else
	{
		pCurrent = pHead;
		return (*pHead).Data;
	}
}


template <class DATA, class INDEX>
const DATA & UBArray <DATA, INDEX>::GetNext() const
{
	if (pCurrent)
	{
		if ((*pCurrent).pNext)
		{
			pCurrent = (*pCurrent).pNext;
			return (*pCurrent).Data;
		}
		else
		{
			throw NoNextElement;
		}
	}
	else
	{
		throw InteratorNotInitiailized;
	}
}




template <class DATA, class INDEX>
const DATA & UBArray <DATA, INDEX>::GetPrev() const
{
	if (pCurrent)
	{
		if ((*pCurrent).pPrev)
		{
			pCurrent = (*pCurrent).prev;
			return (*pCurrent).Data;
		}
		else
		{
			throw NoPrevElement;
		}
	else
	{
		throw InteratorNotInitiailized;
	}
	}
}




template <class DATA, class INDEX>
const DATA & UBArray <DATA, INDEX>::GetLast() const
{
	if (!pTail)
		throw ArrayEmpty;
	else
	{
		pCurrent = pTail;
		return (*pTail).Data;
	}
}



template <class DATA, class INDEX>
bool UBArray <DATA, INDEX>::Remove(INDEX i)
{
	{
		WCS_Pointer <Node>	pNode;
		if (!pHead) //if it doesn't exist
		{
			return false;
		}

		if ((i > (*pTail).index) || (i < (*pHead).index)) //if the index is too big or too small
		{
			return false;
		}

		if (i == (*pTail).index) //if we are deleting and moving the tail
		{
			if ((*pTail).index == (*pHead).index) //if we are at the last element in the array
			{
				pHead.SetToNull();
				pTail.SetToNull();
				numElements--;
				return true;
			}
			else
			{
				(*(*pTail).pPrev).pNext = (*pTail).pPrev;
				pTail = (*pTail).pPrev;
				numElements--;
				return true;
			}
		}

		if (i == (*pHead).index) //if we are deleting and moving the head
		{
			if ((*pHead).index == (*pTail).index) //if we are at the last element in the array
			{
				pHead.SetToNull();
				pTail.SetToNull();
				numElements--;
				return true;
			}
			else
			{
				(*(*pHead).pNext).pPrev = (*pHead).pNext;
				pHead = (*pHead).pNext;
				numElements--;
				return true;
			}
		}

		for (pNode = (pHead); i >= (*pNode).index; pNode = (*pNode).pNext) //checking if the index exists
		{
			if (i == (*pNode).index) //if the index exists, move the pointers and let refcount delete the node. 
			{
				(*(*pNode).pPrev).pNext = (*pNode).pNext;
				(*(*pNode).pNext).pPrev = (*pNode).pPrev;
				numElements--;
				return true;
			}
		}
		return false; //if I didn't find the index 
	}

}

template <class DATA, class INDEX>
int UBArray <DATA, INDEX>::Size() const
{
	return numElements;
}

template <class DATA, class INDEX>
DATA & UBArray <DATA, INDEX>::operator [] (const INDEX & i)
{
	WCS_Pointer <Node>		pTemp;
	WCS_Pointer <Node>		pTemp2;

	if (!pHead)
	{
		pHead = WCS_Pointer <Node>(new Node(i));
		numElements++;
		pTail = pHead;
		return (*pHead).Data;
	}
	else
		if (i == (*pHead).index)
		{
			return (*pHead).Data;
		}
		else
		{
			if (i < (*pHead).index)
			{
				pTemp = WCS_Pointer <Node>(new Node(i));
				numElements++;
				(*pTemp).pNext = pHead;
				(*pHead).pPrev = pTemp;
				pHead = pTemp;
				return (*pHead).Data;
			}
			else
			{
				if (i == (*pTail).index)
				{
					return (*pTail).Data;
				}
				else
				{
					if (i > (*pTail).index)
					{
						pTemp = WCS_Pointer <Node>(new Node(i));
						numElements++;
						(*pTemp).pPrev = pTail;
						(*pTail).pNext = pTemp;
						pTail = pTemp;
						return (*pTail).Data;
					}
					else
					{
						for (pTemp = (*pHead).pNext; i > (*pTemp).index; pTemp = (*pTemp).pNext);
						if (i == (*pTemp).index)
						{
							return (*pTemp).Data;
						}
						else
						{
							pTemp2 = WCS_Pointer <Node>(new Node(i));
							numElements++;
							(*pTemp2).pNext = pTemp;
							(*pTemp2).pPrev = (*pTemp).pPrev;
							(*pTemp).pPrev = pTemp2;
							(*(*pTemp2).pPrev).pNext = pTemp2;
							return (*pTemp2).Data;
						}
					}
				}
			}
		}
}


template <class DATA, class INDEX>
DATA & UBArray <DATA, INDEX>::operator [] (const INDEX & i) const
{
	WCS_Pointer <Node>	pNode;
	if (!pHead)
	{
		throw ArrayEmpty;
	}
	if ((i > (*pTail).index) || (i < (*pHead).index))
	{
		throw InvalidIndex;
	}
	for (pNode = (pHead); i >= (*pNode).index; pNode = (*pNode).pNext)
	{
		if (i == (*pNode).index)
		{
			return (*pNode).Data;
		}
	}
	throw InvalidIndex;
}

template <class DATA, class INDEX>
void UBArray <DATA, INDEX>::DeleteAll()
{
	WCS_Pointer <Node> pNode;
	if (pHead)
	{
		for (pNode = (*pHead).pNext; (*pHead).index < (*pTail).index; pNode = (*pNode).pNext)
		{
			(*pNode).pPrev = (*(*pNode).pPrev).pNext;
			pHead = pNode;
			numElements--;
		}

		pHead.SetToNull();
		pTail.SetToNull();
		numElements--;
	}
	pCurrent.SetToNull();
}


#endif
