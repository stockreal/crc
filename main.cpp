 ///////////////////////////////////////////////////////////////////////////////
 // file: main.cpp
 // Project: ecclab
 // Description: 
 //
 // Change history: Apr. 15, 2018 - file created.
 //					May. 16, 2018 - multi-bit crc.
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
	
	cout << "crc start!!!" << endl;
	cout << "start time = " << buffer << endl;
	
	CRC crc(8);		// can enter 4 for crc4, 6, 8, 11, 16, 24
	crc.CoutCRCsetting();
	crc.CRCcal();
	crc.CoutRegVect();
	crc.SimplifyRegVect();
	crc.CoutFinalRegVect();
	
	cout << "Verification:\n";
	crc.RandomizedInput(16);
	crc.CoutInput();
	crc.CRCcheck();
	crc.CoutCRCcyclic();
	
	return 0;
}


