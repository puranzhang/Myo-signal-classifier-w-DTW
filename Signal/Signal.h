#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include <string>

using namespace std;

class Signal{

private:

	string fileName;
	vector< double > dataOut;

	vector< double > makeSignal(string inputFile);

public:

	Signal();
	
	Signal(string fileName);
	vector< double> getData();
	~Signal();

};

#endif
