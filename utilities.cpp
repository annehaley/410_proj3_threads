/*
 * utilities.cpp
 *
 *  Created on: Jan 15, 2020
 *      Author: Anne Haley
 */

#include "utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

//global vector holding process_stats structs
vector<process_stats> myvector;

//clears vector holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to a vector
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename){

	fstream myfile;
	myfile.open(filename);
	if(myfile.is_open()){

		//clear vector
		myvector.clear();

		//process lines in file
		string line;
		while(getline(myfile, line)){
			process_stats curr;
			stringstream ss(line);
			string pnum="";
			string stime="";
			string cputime="";
			getline(ss, pnum, ',');
			getline(ss, stime, ',');
			getline(ss, cputime, ',');
			curr.process_number=stoi(pnum);
			curr.start_time=stoi(stime);
			curr.cpu_time=stoi(cputime);
			myvector.push_back(curr);
		}

		return SUCCESS;
	}

	return COULD_NOT_OPEN_FILE;
}

//attempt to open file 'filename' to write, and serialize a
//vector full of process_stats structs to it.  Should be in the same
//format as original file but not necessarily the same order or length
//if the file exists, overwrite its contents.
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int saveData(const char* filename){

	fstream output;
	output.open(filename, fstream::out);
	if(output.is_open()){

		//write contents of vector to file
		for(process_stats x : myvector){
			output << x.process_number<<","<<
					x.start_time<<","<<
					x.cpu_time<<endl;
		}

		output.close();
		return SUCCESS;
	}

	return COULD_NOT_OPEN_FILE;
}

//helper method to compare process_stats in the vector sorting
bool compareProcesses(process_stats one, process_stats two){
	return one.cpu_time < two.cpu_time;
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder){
	sort(myvector.begin(), myvector.end(), compareProcesses);
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext(){
	process_stats ret;
	ret=myvector.front();
	myvector.erase(myvector.begin());
	return ret;
}


