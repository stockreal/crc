 ///////////////////////////////////////////////////////////////////////////////
 // file: main.cpp
 // Project: ecclab
 // Description: 
 //
 // Change history: Apr. 15, 2018 - file created.
 //
 ///////////////////////////////////////////////////////////////////////////////


#include "xinyo.h"
#include "polar_code.h"

using namespace std;

 ///////////////////////////////////////////////////////////////////////////////
 // file: polar_lsc_crc_decode.cpp
 // Project: PolarCode
 // Description: 
 //
 // Change history: Mar. 09, 2018 - file copied from polarLSC.
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
	
	cout << " start!!!" << endl;
	cout << "start time = " << buffer << endl;
	
	
	
	return 0;
}


