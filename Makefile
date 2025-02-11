a.out: main.o server.o client.o
	g++ -g main.o server.o client.o

server.o: server.cpp my_defs.h
	g++ -c -g server.cpp

client.o: client.cpp my_defs.h
	g++ -c -g client.cpp

main.o: main.cpp
	g++ -c -g main.cpp

clean:
	rm *.o a.out *.zip

zip:
	zip pipe_client_server.zip *.h *.cpp Makefile