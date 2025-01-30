./bin/main.exe : ./src/main.cpp
	g++ -o ./bin/main.exe ./src/main.cpp

run : ./bin/main.exe
	./bin/main.exe

clean : 
	rm ./bin/main.exe