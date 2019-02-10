target: server client

genMd5: genMd5.cpp
	g++ -c -I/usr/include/openssl/ -Wall genMd5.cpp -o genMd5.o -lcrypto

genRand: genRand.cpp
	g++ -std=c++11 -c -I/usr/include/openssl/ -Wall genRand.cpp  -o genRand.o -lcrypto


server: genMd5 genRand serverWap2.h serverWap2.c
	g++ -o server serverWap2.h common.h serverWap2.c genMd5.o genRand.o

client: genMd5 genRand clientWap2.c
	g++ -o client common.h clientWap2.c genMd5.o genRand.o

test: test.c
	gcc -o test test.c 
boostClient: boostClient.cpp
	g++ -std=c++11 -o boostClient ./boostClient.cpp -lpthread -lboost_system
boostServer: boostServer.cpp
	g++ -std=c++11 -o boostServer ./boostServer.cpp -lboost_system


clean: 
	rm test server client
