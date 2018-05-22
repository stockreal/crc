RM	=rm -rf

gpp:
	g++ main.cpp crc.cpp -o main.out
	
test:
	g++ test.cpp crc.cpp -o test.out