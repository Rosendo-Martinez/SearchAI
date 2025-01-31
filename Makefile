./bin/main.exe : ./src/main.cpp ./bin/Shader.o ./bin/SquareRenderer.o ./bin/Grid.o
	g++ -o ./bin/main.exe ./src/main.cpp ./dep/glad/src/glad.c ./bin/Shader.o ./bin/SquareRenderer.o ./bin/Grid.o -I./dep/glad/include -lglfw -ldl

run : ./bin/main.exe
	./bin/main.exe

clean : 
	rm ./bin/main.exe ./bin/*.o

./bin/Shader.o : ./src/Shader.cpp ./src/Shader.h
	g++ -c ./src/Shader.cpp -o ./bin/Shader.o -I./dep/glad/include

./bin/SquareRenderer.o : ./src/SquareRenderer.cpp ./src/SquareRenderer.h
	g++ -c ./src/SquareRenderer.cpp -o ./bin/SquareRenderer.o -I./dep/glad/include

./bin/Grid.o : ./src/Grid.cpp ./src/Grid.h
	g++ -c ./src/Grid.cpp -o ./bin/Grid.o