 ///////////////////////////////////////////////////////////////////////////////
 // file: crc.h
 // Project: ecclab
 // Description: 
 //
 // Change history: Apr. 15, 2018 - file created.
 // 				
 //
 ///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <bitset>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;


class CRC{

private:
	int num_crc_bit_;
	bool* crc_polynomial_;		// true as 1, MSB
	int num_input_;
	bool* in_arr_;				// ture as 1
	vector<bool*> reg_vect_;

public:
	CRC();
	
	void CoutCRCsetting();

};




