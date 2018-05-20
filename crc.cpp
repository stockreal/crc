 ///////////////////////////////////////////////////////////////////////////////
 // file: crc.cpp
 // Project: ecclab
 // Description: 
 //
 // Change history: Apr. 15, 2018 - file created.
 //
 ///////////////////////////////////////////////////////////////////////////////

#include "crc.h"

// to be noticed: crc_polynomial_ is the invese array of the following one. 
bool crc_4[4] = {0,0,1,1};
bool crc_6[6] = {1,1,0,0,0,1};
bool crc_11[11] = {1,1,0,0,0,1,0,0,0,0,1};
bool crc_16[16] = {0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};
bool crc_24[24] = {1,0,1,1,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,1,0,1,1,1};
// vector< bool* > _crc_vector;

CRC::CRC(){
	
	// _crc_vector.resize(5);
	// _crc_vector[0] = crc_4;
	// _crc_vector[1] = crc_6;
	// _crc_vector[2] = crc_11;
	// _crc_vector[3] = crc_16;
	// _crc_vector[4] = crc_24;
	
	num_crc_bit_ = 4;
	crc_polynomial_ = new bool[num_crc_bit_];
	for(int i=0; i<num_crc_bit_; i++){
		crc_polynomial_[i] = crc_4[num_crc_bit_-i-1];
		// crc_polynomial_[i] = _crc_vector[0][num_crc_bit_-i-1];
	}
	
	int n = num_crc_bit_ * num_crc_bit_;
	reg_vect_.resize(n);		// num_crc_bit_**2 items
	for(int i=0; i<n; i++){
		reg_vect_[i].resize(num_crc_bit_*2);
		for(int j=0; j<num_crc_bit_*2; j++){
			reg_vect_[i][j] = 0;
		}
	}
	state_ = 0;
}

CRC::CRC(int sel){
	
	if(sel == 6){
		num_crc_bit_ = 6;
		crc_polynomial_ = new bool[num_crc_bit_];
		for(int i=0; i<num_crc_bit_; i++){
			crc_polynomial_[i] = crc_6[num_crc_bit_-i-1];
		}
	}else if(sel == 11){
		num_crc_bit_ = 11;
		crc_polynomial_ = new bool[num_crc_bit_];
		for(int i=0; i<num_crc_bit_; i++){
			crc_polynomial_[i] = crc_11[num_crc_bit_-i-1];
		}
	}else if(sel == 16){
		num_crc_bit_ = 16;
		crc_polynomial_ = new bool[num_crc_bit_];
		for(int i=0; i<num_crc_bit_; i++){
			crc_polynomial_[i] = crc_16[num_crc_bit_-i-1];
		}
	}else if(sel == 24){
		num_crc_bit_ = 24;
		crc_polynomial_ = new bool[num_crc_bit_];
		for(int i=0; i<num_crc_bit_; i++){
			crc_polynomial_[i] = crc_24[num_crc_bit_-i-1];
		}
	}else{
		num_crc_bit_ = 4;
		crc_polynomial_ = new bool[num_crc_bit_];
		for(int i=0; i<num_crc_bit_; i++){
			crc_polynomial_[i] = crc_4[num_crc_bit_-i-1];
		}
	}
	
	int n = num_crc_bit_ * num_crc_bit_;
	reg_vect_.resize(n);		// num_crc_bit_**2 items
	for(int i=0; i<n; i++){
		reg_vect_[i].resize(num_crc_bit_*2);
		for(int j=0; j<num_crc_bit_*2; j++){
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
	cout << "Initial register vector:\n";
	
	CoutRegVect();
}

void CRC::SimplifyReg(vector<bool>& reg_arr, int index){
	// int reg = index % num_crc_bit_;
	int stage = index / num_crc_bit_;
	vector<bool> temp_reg_vect;
	temp_reg_vect.resize(num_crc_bit_);
	for(int i=0; i<num_crc_bit_; i++){
		temp_reg_vect[i] = reg_arr[num_crc_bit_+i];
		reg_arr[num_crc_bit_+i] = 0;
	}
	for(int i=0; i<num_crc_bit_; i++){
		if(temp_reg_vect[i]){
			int temp_index = (stage-1) * num_crc_bit_ + i;
			for(int j=0; j<num_crc_bit_*2; j++){
				if(reg_vect_[temp_index][j]){
					reg_arr[j] = ~reg_arr[j];
				}
			}
		}
	}
}

void CRC::SimplifyRegVect(){
	for(unsigned int i=num_crc_bit_; i<reg_vect_.size(); i++){
		SimplifyReg(reg_vect_[i],i);
	}
}

void CRC::CoutReg(vector<bool> reg_arr, int index){
	int reg = index % num_crc_bit_;
	int stage = index / num_crc_bit_ + 1;
	cout << "R" << reg << "," << stage << " = ";
	bool flag = false;
	for(int i=0; i<num_crc_bit_; i++){
		if(reg_arr[i]){
			if(flag){
				cout << " ^ in" << setw(2) << i;
			}else{
				cout << "in" << setw(2) << i;
				flag = true;
			}
		}
	}
	for(int i=num_crc_bit_; i<2*num_crc_bit_; i++){
		if(reg_arr[i]){
			if(flag){
				cout << " ^ r" << i-num_crc_bit_ << "," << stage-1;
			}else{
				cout << "r" << i-num_crc_bit_ << "," << stage-1;
				flag = true;
			}
		}
	}
	
	cout << endl;
}

void CRC::CoutRegFinal(vector<bool> reg_arr, int index){
	int reg = index % num_crc_bit_;
	int stage = index / num_crc_bit_ + 1;
	cout << "R" << reg << "," << stage << " = ";
	bool flag = false;
	for(int i=0; i<num_crc_bit_; i++){
		if(reg_arr[i]){
			if(flag){
				cout << " ^ in" << setw(2) << i;
			}else{
				cout << "in" << setw(2) << i;
				flag = true;
			}
		}
	}
	for(int i=num_crc_bit_; i<2*num_crc_bit_; i++){
		if(reg_arr[i]){
			if(flag){
				cout << " ^ r" << i-num_crc_bit_ << "," << 0;
			}else{
				cout << "r" << i-num_crc_bit_ << "," << 0;
				flag = true;
			}
		}
	}
	
	cout << endl;
}

void CRC::CoutRegVect(){
	
	for(unsigned int i=0; i<reg_vect_.size(); i++){
		
		if(i % num_crc_bit_ == 0){
			cout << "------------stage "<< i/num_crc_bit_ <<"--------------" << endl;
		}
		CoutReg(reg_vect_[i],i);
	}
	cout << "--------------end----------------\n" << endl;
}

void CRC::CoutFinalRegVect(){
	for(unsigned int i=0; i<reg_vect_.size(); i++){
		
		if(i % num_crc_bit_ == 0){
			cout << "------------stage "<< i/num_crc_bit_ <<"--------------" << endl;
		}
		CoutRegFinal(reg_vect_[i],i);
	}
	cout << "--------------end----------------\n" << endl;
}

void CRC::CRCcal(){
	for(unsigned int i=0; i<reg_vect_.size(); i++){
		CRCcalReg(reg_vect_[i],i);
	}
}

void CRC::CRCcalReg(vector<bool>& reg_arr, int index){
	int reg = index % num_crc_bit_;
	int stage = index / num_crc_bit_;
	if(reg == 0){
		reg_arr[stage] = ~reg_arr[stage];
	}else{
		reg_arr[num_crc_bit_+reg-1] = ~reg_arr[num_crc_bit_+reg-1];
	}
	if(crc_polynomial_[reg]){
		reg_arr[2*num_crc_bit_-1] = ~reg_arr[2*num_crc_bit_-1];
	}
}

