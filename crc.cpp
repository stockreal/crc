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
		
		if(i % 4 == 0){
			cout << "------------stage "<< i/4 <<"--------------" << endl;
		}
		CoutReg(reg_vect_[i],i);
	}
	cout << "--------------end----------------\n" << endl;
}

void CRC::CoutFinalRegVect(){
	for(unsigned int i=0; i<reg_vect_.size(); i++){
		
		if(i % 4 == 0){
			cout << "------------stage "<< i/4 <<"--------------" << endl;
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

// void CRC::CRCnext(){
	
	// if(state_ < num_crc_bit_){		// right shift
		// rotate(reg_vect_.begin(),reg_vect_.begin()+num_crc_bit_-1,reg_vect_.end());
		// if(in_arr_[state_]){
			// reg_vect_[0][state_] = ~reg_vect_[0][state_];
		// }
	// }else{
		// vector< vector<bool> > reg_vect_tmp(reg_vect_);
		// rotate(reg_vect_tmp.begin(),reg_vect_tmp.begin()+num_crc_bit_-1,reg_vect_tmp.end());
		// if(in_arr_[state_]){
			// reg_vect_tmp[0][state_] = ~reg_vect_tmp[0][state_];
		// }
		// for(int i=1; i<num_crc_bit_; i++){
			// if(crc_polynomial_[i]){
				// for(int j=0; j<num_input_; j++){
					// if(reg_vect_[num_crc_bit_-1][j]){
						// reg_vect_tmp[i][j] = ~reg_vect_tmp[i][j];
					// }
				// }
			// }			
		// }
		// reg_vect_.assign(reg_vect_tmp.begin(),reg_vect_tmp.end());
	// }
	// ++state_;
// }

// void CRC::CRCrun(){
	// cout << "CRC start running!!!\n";
	// cout << "The initial state of reg:\n";
	// CoutRegVect(reg_vect_);
	
	// for(int i=0; i<num_input_; i++){
		// CRCnext();
		// cout << "state " << i << ":\n";
		// CoutRegVect(reg_vect_);
	// }
// }

// void CRC::InitRegVect(vector< vector<bool> > reg_vect){
	// reg_vect.resize(num_crc_bit_);
	// for(int i=0; i<num_crc_bit_; i++){
		// reg_vect[i].resize(num_input_);
		// for(int j=0; j<num_input_; j++){
			// reg_vect[i][j] = 0;
		// }
	// }
// }
