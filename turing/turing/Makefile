TM_parser.o : TM_parser.cpp TM_parser.hpp
	g++ -c TM_parser.cpp

TM_simulator.o : TM_simulator.cpp TM_simulator.hpp TM_parser.hpp
	g++ -c TM_simulator.cpp

main.o : main.cpp TM_parser.hpp TM_simulator.hpp
	g++ -c main.cpp

turing : TM_parser.o TM_simulator.o main.o
	g++ TM_parser.o TM_simulator.o main.o -o turing
	sudo cp -r /home/nelly/Workspace/FLA_project/NJU-FLA/turing/turing/turing /bin

clean : 
	rm TM_parser.o TM_simulator.o main.o

update:
	make clean
	sudo rm turing
	make turing
	sudo rm /bin/turing
	sudo cp -r /home/nelly/Workspace/FLA_project/NJU-FLA/turing/turing/turing /bin




