./bin/main.exe : ./src/main.cpp ./bin/Shader.o
	g++ -o ./bin/main.exe ./src/main.cpp ./dep/glad/src/glad.c ./bin/Shader.o -I./dep/glad/include -lglfw -ldl

run : ./bin/main.exe
	./bin/main.exe

clean : 
	rm ./bin/main.exe

./bin/Shader.o : ./src/Shader.cpp ./src/Shader.h
	g++ -c ./src/Shader.cpp -o ./bin/Shader.o -I./dep/glad/include