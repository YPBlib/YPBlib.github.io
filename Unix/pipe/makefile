target: Adversary WPA2



Adversary: Adversary.cpp genMd5 genRand
	g++ -std=c++11 -o Adversary -I/usr/include/openssl/ ./genMd5.o genRand.o ./Adversary.cpp -lcrypto

genMd5: genMd5.cpp
	g++ -c -I/usr/include/openssl/ -Wall genMd5.cpp -o genMd5.o -lcrypto

genRand: genRand.cpp
	g++ -std=c++11 -c -I/usr/include/openssl/ -Wall genRand.cpp  -o genRand.o -lcrypto

WPA2: WPA2.cpp genMd5 genRand
	g++ -std=c++11 -o WPA2 -I/usr/include/openssl/  ./genMd5.o genRand.o ./WPA2.cpp -lcrypto