./bin/main.exe : ./src/main.cpp
	g++ -o ./bin/main.exe ./src/main.cpp ./dep/glad/src/glad.c -I./dep/glad/include -lglfw -ldl

run : ./bin/main.exe
	./bin/main.exe

clean : 
	rm ./bin/main.exe