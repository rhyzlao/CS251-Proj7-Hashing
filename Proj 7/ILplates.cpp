/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << YOUR NAME >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>

#include "ILplates.h"

using namespace std;

bool Vanity(string plate){
	int numbers = 0;
	int letters = 0;
	int spaces = 0;
	for(unsigned int i = 0; i < plate.size(); i++){
		if(islower(plate[i])){
				return false;
		}
		else if(plate[i] == ' '){
			spaces++;
		}
		else if(isalpha(plate[i])){
			letters++;
		}
		else if(isdigit(plate[i])){
			numbers++;
		}
		else{
		  return false;
		}
	}

// Format: 1-3 numbers
	if((numbers > 0 && numbers < 4) &&
	   (letters == 0) &&
	   (spaces == 0)){
		return true;		
	}
// 	Format: 1-7 letters
	if((letters > 0 && letters < 8) &&
		(numbers == 0) &&
		(spaces == 0)){
		return true;
	}
	if(spaces > 0){
		return false;
	}
	
	return false;
}

bool Personalized(string plate){
	int numbers = 0;
	int letters = 0;
	int spaces = 0;
	for(unsigned int i = 0; i < plate.size(); i++){
		if(islower(plate[i])){
				return false;
			}
// 		If index is a space
		else if(plate[i] == ' '){		
			spaces++;
		}
		else if(isalpha(plate[i])){
			letters++;
// 		Checks for letters after a space
			  if(spaces != 0){
// 		cout << "plate is" << plate << endl;
				return false;
			  }
		}
		else if(isdigit(plate[i])){
			numbers++;
		}
		else{
		  return false;
		}
	}
// 	If there is a space in the front or the end
	if((isspace(plate[0])) || (isspace(plate[plate.size()-1]))){
		return false;
  }
	//Format: 1-5 letters plus 1-99
	if((letters > 0 && letters < 6) &&
	   (numbers > 0 && numbers < 3) &&
	   (spaces == 1)){
		return true;
	}
	//Format: 6 letters plus 1-9
	if((letters == 6) &&
	   (numbers > 0 && numbers < 2) &&
	   (spaces == 1)){
		return true;
	}
	else{
		return false;
	}
	
}

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate)
{
  long long index = -1;
  index = 0;
  string license;
  int licenseSize = 0;
  
  licenseSize = plate.size();
  if(Vanity(plate) == true ||
	 Personalized(plate) == true){
	 
	 for(unsigned int i = 0; i < plate.size(); i++){
		 
		 if(isalpha(plate[i])){
			 index += (int(plate[i]) + 1) * (pow(36, licenseSize- i));				
		 }
		 else if(isdigit(plate[i])){
			 index += (int(plate[i]) + 1) * (pow(36, licenseSize - i));
		 }
		 else{
			 continue;
		 }
	 }		  
   } // end if statement
	else{
		return -1;
	}

  return index % HT.Size();
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{	
	int bucket = Hash(plate);
	int bucketsProbed = 0;
	
	bool empty;
	string forKey;
	int forValue;
	
	HT.Get(bucket, empty, forKey, forValue);
	
	while(!empty &&
		  (bucketsProbed < HT.Size())){
		if(forKey == plate){
			return forValue;
		}
		
		bucket++;		
		if(bucket == HT.Size()){
		   bucket = 0;
		}
		
		HT.Get(bucket, empty, forKey, forValue);
	}
  
  

  return -1;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
	int bucket = Hash(plate);
	int bucketsProbed = 0;
	
	bool empty;
	string forKey;
	int forValue;
	
	HT.Get(bucket, empty, forKey, forValue);
	
  
  while(!empty){
	  if(forKey == plate){
		 // forValue = forValue + newValue;
		  HT.Set(bucket, plate, newValue);
		  return;
	  }
  
  bucket++;
	  
  if(bucket == HT.Size()){
           bucket = 0;
  }
	HT.Get(bucket, empty, forKey, forValue);  
  }
	HT.Set(bucket, plate, newValue);
  return;
}
