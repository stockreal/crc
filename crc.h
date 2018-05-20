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
	int num_crc_bit_;					// also mean the input size and state size
	bool* crc_polynomial_;				// true as 1, LSB
	vector< vector<bool> > reg_vect_;	// num_crc_bit_ * (num_crc_bit_ * 2) of matrix
	int state_;							// start from 0 end with num_crc_bit_
	
	int num_of_input_;
	bool* input_;						// random input bit for verification
	bool* crc_multi_;					// crc bits gen by multi bits
	bool* crc_cyclic_;					// crc bits gen by cyclic shift

public:
	CRC();
	CRC(int);
	
	void CoutCRCsetting();
	void SimplifyReg(vector<bool>&, int);
	void SimplifyRegVect();
	void CoutReg(vector<bool> reg_arr, int);
	void CoutRegFinal(vector<bool> reg_arr, int);
	void CoutRegVect();
	void CoutFinalRegVect();
	void CRCcal();
	void CRCcalReg(vector<bool>& , int);
	
	// verification
	void RandomizedInput(int num_of_input);
	void CoutInput();
	void CRCcheck();
	void CoutCRCcyclic();
	// void CRCmultiCal();
	// void CoutCRCcyclic();
};




