/*process file with hashing function
search using keys in search.dat against hashed dataset
A collission occurs when two data keys generate the same hash.
Overflow buckets are supposed to handle this problem.


Program Design -> Data Design + Alrogithm Design
					|		
				Hash Table 
					Primary Bucket
						Slot(3)
							Key(10 bytes)
							Data(20 bytes)

						Overflow(index)


					Overflow Bucket
					

"Illustration" of multiple key collisions.

Bucket 13
=========
Overflow 	| Count    	Grab a free Bucket
------------|------    	------------------>	Overflow 	| Count   									   
Key1		| ---                           ------------|------
Key2		| ---							Key4     	| ---
Key3		| ---




Hashing is similar to the concept of key-value pairs found in many modern programming langauage

Design
======
Hashtable 
	Bucket
		3 slots
			10 byte key
			20 byte data
		Count
		Overflow


Slot
STR10 	| STR20
key 	| value (data)

Implementation
==============
*/
#include <iostream>
#include <cstdio>
#include <string>

typedef char STR10[10+1];
typedef char STR20[20+1];

//typdef struct Slot
class Slot
{
	private:
		STR10 key;
		STR10 value;
};

/*
=================

Slot S1 = {"Doe", "1235 East E Street" };
					F700:1300

					S1
					Doe	| 1235.....
					
					pS [  F700  :1300] -> Points to first record of S1
	S1.key
	S1.value

Slot * pS = &S1;  // Look up for more notes on this line.

pS->key; = (*pS).key;
pS->value; = (*pS).value;

=================
*/
// #define MAX_SLOTS 3 // Handled by the preprocessor (cannot be scoped)
const int MAX_SLOTS = 3; // Handles by the compiler (can be scoped)
const int MAX_BUCKETS = 30;
//typedef struct Bucket
class Bucket
{
	private:	
		short int count;
		short int overflow;
		Slot slots[MAX_SLOTS]; // Slot must be defined first.
};
//struct Bucket b; // instance of structure
//Bucket b; // instance of class Bucket
typdef Bucket HashTable[MAX_BUCKETS];
HashTable ht; // instance of a HashTable
/*i = 0 .... 29
// j = 0 .... 2
ht[i]
	slots[j]
		key
		value
	count
	overflow

Program Design (Assign1)
========================
Data Design
	Hashtable ht

Alrogithm Designs
	Hierarchy Decomposition of Modules
*//*
Primary (20)
	Initialize ht; // 3.1
	HashFunction() // 3.2
	Insert() // 3.3 
	Search() // 3.4
	DrawStats() // 3.5 // Computing hash effiency statistics
	ReportHashTable() // 3.6
	SaveHashTable() // 3.7
	RestoreHashTable() // 3.8

Overflow(10)

Use count for how many slots there are (decrement every time you use a slot)
*/

/*
Data Design 
	STR10 -> Programmer Defined data type
	STR20
	Slot
	Bucket
		typedef struct Bucket {
			Slot slots[MAX_SLOTS];
			short int count; // records "loading"
			int overflow; // index to overflow
		} Bucket;

	HashTable
		typedef Bucket HashTable[MAX_BUCKETS];

Algorithm Design
3.0 Assign 1 (main module)
 	3.1 InitializeHashTable (out ht as HashTable)
 	3.2 HashFunction (in key as STR10, out hash_index as int)
 	3.3 InsertIntoHashTable (inout ht as HashTable, in key as STR10, in data as STR20)
 	3.4 GenerateHashTableReport (in ht as HashTable)
 	3.5 SaveRawContentsOfHashTable (in ht as HashTable)
 	3.6 RestoreHashTableToMemory (inout ht as HashTable)
 	3.7 SearchHashTable (in search_key as STR10, in ht as HashTable)
	3.8 GenerateHashTableStatistics (in ht as HashTable)
*/

DataIn
	For Loop As Max Buckets 
		Read From File 
		Get Key And Value From File 
		Hash Key
		Call Insert(Hashed Key) 
	End For
Insert
	# Check Available Slots 
	# If No Available Slots
	# 	Insert In Overflow 
	# 	Connect Overflow to Slot
	# Else
	# 	Insert In Next Available Slot
	# End If
	Call CollissionCheck (Hashed Key)
	If Count > MaxSlots 
		OverFlow = True
	End If
	Insert Hash Key Into Correct Spot (Count)

CollissionCheck(in hash_index, out count as int )
	For Each Bucket
		For Each Slot
			If Match Is Found 
				Return Count
			Else 
				Return 0
			End If
		End For
	End For


