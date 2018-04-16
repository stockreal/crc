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
	crc_polynomial_[0] = 1;		// LSB
	crc_polynomial_[1] = 1;
	crc_polynomial_[2] = 0;
	crc_polynomial_[3] = 0;
	num_input_ = 8;
	in_arr_ = new bool[num_input_];
	// in_arr_[0] = 1;				// MSB
	// in_arr_[1] = 1;
	// in_arr_[2] = 1;
	// in_arr_[3] = 1;
	// in_arr_[4] = 1;
	// in_arr_[5] = 1;
	// in_arr_[6] = 1;
	// in_arr_[7] = 1;
	for(int i=0; i<num_input_; i++){
		in_arr_[i] = 1;
	}
	reg_vect_.resize(num_crc_bit_);
	for(int i=0; i<num_crc_bit_; i++){
		reg_vect_[i].resize(num_input_);
		for(int j=0; j<num_input_; j++){
			reg_vect_[i][j] = 0;
		}
	}
	state_ = 0;
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

void CRC::CoutReg(vector<bool> reg_arr){
	// string in = "in";
	// string xor_str = " ^ ";
	bool flag = false;
	for(int i=0; i<num_input_; i++){
		if(reg_arr[i]){
			if(flag){
				cout << " ^ ";
			}
			cout << "in" << i;
			flag = true;
		}
	}
	if(!flag){
		cout << "0";
	}
	cout << endl;
}

void CRC::CoutRegVect(vector< vector<bool> >& reg_vect){
	for(int i=0; i<num_crc_bit_; i++){
		cout << "Reg" << i << " = ";
		CoutReg(reg_vect[i]);
	}
	cout << endl;
}

void CRC::CRCnext(){
	
	if(state_ < num_crc_bit_){		// right shift
		rotate(reg_vect_.begin(),reg_vect_.begin()+num_crc_bit_-1,reg_vect_.end());
		if(in_arr_[state_]){
			reg_vect_[0][state_] = ~reg_vect_[0][state_];
		}
	}else{
		vector< vector<bool> > reg_vect_tmp(reg_vect_);
		// InitRegVect(reg_vect_tmp);
		// reg_vect_tmp.assign(reg_vect_);
		rotate(reg_vect_tmp.begin(),reg_vect_tmp.begin()+num_crc_bit_-1,reg_vect_tmp.end());
		if(in_arr_[state_]){
			reg_vect_tmp[0][state_] = ~reg_vect_tmp[0][state_];
		}
		for(int i=1; i<num_crc_bit_; i++){
			if(crc_polynomial_[i]){
				// cout << "reg_vect_tmp" << i << " = ";
				// CoutReg(reg_vect_tmp[i]);
				// cout << "reg_vect_" << num_crc_bit_-1 << " = ";
				// CoutReg(reg_vect_[num_crc_bit_-1]);
				for(int j=0; j<num_input_; j++){
					if(reg_vect_[num_crc_bit_-1][j]){
						reg_vect_tmp[i][j] = ~reg_vect_tmp[i][j];
					}
				}
				// cout << "reg_vect_tmp" << i << " = ";
				// CoutReg(reg_vect_tmp[i]);
			}			
		}
		reg_vect_.assign(reg_vect_tmp.begin(),reg_vect_tmp.end());
	}
	++state_;
}

void CRC::CRCrun(){
	cout << "CRC start running!!!\n";
	cout << "The initial state of reg:\n";
	CoutRegVect(reg_vect_);
	
	for(int i=0; i<num_input_; i++){
		CRCnext();
		cout << "state " << i << ":\n";
		CoutRegVect(reg_vect_);
	}
}

void CRC::InitRegVect(vector< vector<bool> > reg_vect){
	reg_vect.resize(num_crc_bit_);
	for(int i=0; i<num_crc_bit_; i++){
		reg_vect[i].resize(num_input_);
		for(int j=0; j<num_input_; j++){
			reg_vect[i][j] = 0;
		}
	}
}