/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << YOUR NAME >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;

void swapint(int &x, int &y){
	int temp = x;
	x = y;
	y = temp;
}

void swapstring(string &x, string &y){
	string temp = x;
	x = y;
	y = temp;
}

void bubbleSort(vector<string> &plato, vector<int> &fino, int x){
	for(int i = 0; i < x; i++){
		for(int m = i; m < x; m++){
			if(plato[i] > plato[m]){
				swapstring(plato[i], plato[m]);
				swapint(fino[i], fino[m]);				
			}
		}
	}
}


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}



int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  
  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();
  
//   for(int i = 0; i < plates.size(); i++){
// 	  cout << "Plate " << i << " is " << plates[i] << endl;
// 	  cout << "Amount " << i <<" is" << amounts[i] << endl;
//   }
	
  int n = plates.size();
  cout << "Sorting..." << endl;
  bubbleSort(plates, amounts, n);
	
//   for (size_t i = 0; i < plates.size(); ++i)
//   {
//     cout << plates[i] << ", " << amounts[i] << endl;
//   }
	
	
// WRITING FILE
  string str2 = "-output.txt";
  string fileRes = basename.append(str2);
  //cout << fileRes << endl;
  ofstream outfile(fileRes);
  cout << "Writing '"<< fileRes << "'" << endl;
  
	
	for(int i = 0; i < n; i++){
		outfile << "\"" << plates[i] << "\"" << " "<< "$" << amounts[i] << endl;
	}
  

  //
  // done:
  //
  return 0;
}