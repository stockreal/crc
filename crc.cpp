 ///////////////////////////////////////////////////////////////////////////////
 // file: crc.cpp
 // Project: ecclab
 // Description: 
 //
 // Change history: Apr. 15, 2018 - file created.
 //
 ///////////////////////////////////////////////////////////////////////////////

#include "crc.h"

// int crc_4[17] = {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
// int crc_8[17] = {1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0};
// int crc_16[17] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1};

CRC::CRC(){
	num_crc_bit_ = 4;
	crc_polynomial_ = new bool[num_crc_bit_];
	crc_polynomial_[0] = 0;
	crc_polynomial_[1] = 0;
	crc_polynomial_[2] = 1;
	crc_polynomial_[3] = 1;
	num_input_ = 8;
	in_arr_ = new bool[0];
	in_arr_[0] = 1;
	in_arr_[1] = 0;
	in_arr_[2] = 1;
	in_arr_[3] = 0;
	in_arr_[4] = 1;
	in_arr_[5] = 0;
	in_arr_[6] = 1;
	in_arr_[7] = 0;
	reg_vect_.resize(num_crc_bit_);
	for(int i=0; i<num_crc_bit_; i++){
		reg_vect_[i] = new bool[num_input_];
		for(int j=0; j<num_input_; j++){
			reg_vect_[i][j] = 0;
		}
	}
}

void CRC::CoutCRCsetting(){
	cout << "Number of CRC bit = \t" << num_crc_bit_ << endl;
	cout << "CRC polynomial: \n1";
	for(int i=0; i<num_crc_bit_; i++){
		cout << noboolalpha << crc_polynomial_[i];
	}
	cout << endl;
	cout << "Number of input bit = \t" << num_input_ << endl;
	cout << "input bit array = \n";
	for(int i=0; i<num_input_; i++){
		cout << noboolalpha << in_arr_[i];
	}
	cout << endl;
	cout << "register vector:\n";
	for(int i=0; i<num_crc_bit_; i++){
		cout << "register " << i << " = ";
		for(int j=0; j<num_input_; j++){
			cout << noboolalpha << reg_vect_[i][j];
		}
		cout << endl;
	}
}