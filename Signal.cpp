//CMSC240 Project
//Team: Ningxi, Puran, Ryan
//Data Preprocessing, implemented by Ningxi

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Signal.h"

using namespace std;

vector< double > Signal::makeSignal(string inputFile){

  fileName = inputFile;
  ifstream inFile;
  inFile.open(fileName.c_str());  
  string currentLine;
  int numOfLine=0;

if ( !inFile.is_open() )
   	{
        
        cerr << "Error: Unable to open file."<< endl;
        exit(1);

    }

while(inFile.good())
	{
		while(getline(inFile,currentLine)){


			numOfLine++; // record number of rows


		}
		
		if ( inFile.fail() )
        {
            // If the fail flag is set by >>, something unexpected happened:
            //    e.g., wrong data type in file for reading;
            //    e.g., only thing left to read is end-of-file character 
            // If the former, one could (should) print an error message;
            // if the latter, the .eof() method can be used to identify and
            // break out.
            if (inFile.eof())
            {
            	// no problem here -- just exit loop and handle results
                break;
			}
           	else
			{
                // failed for some other reason (e.g., string or float input);
                // print a message and exit
                cerr << "There's an error while reading an integer datum..." << endl;
                exit(1);
            }
            break;
        }
        
	}

	inFile.close();
	//cout<<numOfLine<<endl; //get number of lines

	//construct a matrix contains all the data
	vector< vector<double> > myMatrix;
	myMatrix.resize(numOfLine);
	//cout<<"Form a 2-D vector with "<<numOfLine<<" columns."<<endl;

	vector< double > result;
	ifstream inFile1(fileName.c_str());
	string currentLine1;
	int i=0;
	while(i<numOfLine)
	{

			getline(inFile1,currentLine1);
			//cout<<"Row"<<" " << i << ": "<<currentLine1<<endl;
			
			stringstream ss (currentLine1);
			double myDouble;
			double min;
			double max; //To normalize data
			double temp[17];
			for(int j=0; j<17; j++){
			
				ss>>myDouble;
				//cout<<"Row"<<" " <<i <<" Column: "<<j<<" : "<<myDouble<<endl;
				temp[j]=myDouble;
				
			}
			min = *min_element(temp, temp+17);
			max = *max_element(temp, temp+17);

			//cout<< "Min Value: "<< min << endl;
			//cout<< "Max Value: "<< max <<endl;
			//Normalizing data

			for(int k=0; k<17; k++){
			
				temp[k]=(temp[k]-min)/(max-min);
				//cout<<"Row"<<" " <<i <<" Column: "<<k<<" : "<<temp[k]<<endl;
				myMatrix[i].push_back(temp[k]); //2-D table just in case needed
				result.push_back(temp[k]); // make final result a row vector
				
				
			}

			
			i++;
					
		
	}
	
	/*
	for(int m=0; m < result.size(); m++){

		cout<<"Entry "<< m << " : "<< result[m]<< endl;
			
	}
	
	*/	

  return result;

}

Signal::Signal(){

	fileName = "";
	dataOut = dataOut;
	cout<< "No file is given."<< endl;
}


Signal::Signal(string inputFile){

	fileName = inputFile;
	dataOut = makeSignal(inputFile);

}

Signal::~Signal(){

	fileName = "";
	dataOut.clear();

}

vector< double> Signal::getData()
{
	return dataOut;
}

