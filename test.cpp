 ///////////////////////////////////////////////////////////////////////////////
 // file: test.cpp
 // Project: ecclab
 // Description: 
 //
 // Change history: May. 22, 2018 - file created.
 //					
 //
 ///////////////////////////////////////////////////////////////////////////////


#include "crc.h"

using namespace std;


int main(int argc, char **argv){
	
	// create time
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,80,"%F_%T",timeinfo);
	
	cout << "test start!!!" << endl;
	cout << "start time = " << buffer << endl;
	
	bool a = 1;
	bool b = ~a;
	cout << "a = " << a << endl;
	cout << "~a = " << ~a << endl;
	cout << "!a = " << !a << endl;
	cout << "b = ~a = " << b << endl;
	
	return 0;
}


