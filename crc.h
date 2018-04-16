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
	bool* crc_polynomial_;		// true as 1, LSB
	int num_input_;
	bool* in_arr_;				// ture as 1
	vector<bool*> reg_vect_;
	
	int state_;					// start from 0 end with num_input_

public:
	CRC();
	
	void CoutCRCsetting();
	void CoutReg(bool* reg_arr);
	void CoutRegVect(vector<bool*>&);
	void CRCnext();
	void CRCrun();
	void InitRegVect(vector<bool*>);

};




