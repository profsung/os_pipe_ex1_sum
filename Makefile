a.out: main.o server.o client.o
	g++ -g main.o server.o client.o

server.o: server.cpp
	g++ -c -g server.cpp

client.o: client.cpp
	g++ -c -g client.cpp

main.o: main.cpp
	g++ -c -g main.cpp