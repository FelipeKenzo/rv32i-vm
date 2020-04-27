rv32i-vm: build/objects/main.o build/objects/rv32i.o build/objects/memory.o
	g++ build/objects/main.o build/objects/rv32i.o build/objects/memory.o -o build/rv32i-vm

build/objects/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/objects/main.o

build/objects/rv32i.o: src/rv32i.cpp
	g++ -c src/rv32i.cpp -o build/objects/rv32i.o

build/objects/memory.o: src/memory.cpp
	g++ -c src/memory.cpp -o build/objects/memory.o

clean:
	rm build/objects/*.o build/rv32i-vm