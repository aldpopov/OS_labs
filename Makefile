.PHONY: build run test

build: clean-build
	mkdir build
	git submodule init
	git submodule update
	cd ./build; cmake ..; make all

run:
	./build/CP8/cp8 ./config.yaml 2

run_5:
	./build/LW5-7/manage_node

run_4_dynamic:
	./build/LW4/lab4_dynamic -lm -ldl

run_4_static:
	./build/LW4/lab4_static -lm -ldl

run_3:
	./build/LW3/lab3

run_2:
	./build/LW2/lab2 

run_1:
	./build/LW1/lab1

test_1:
	./build/tests/LW1_test

test_2:
	./build/tests/LW2_test

test_3:
	./build/tests/LW3_test

test_4:
	./build/tests/LW4_test

test_5:
	./build/tests/LW5-7_test

test:
	./build/tests/CP8_test

valgrind:
	valgrind --tool=callgrind --collect-jumps=yes --dump-instr=yes ./build/tests/LW2_test

clean-build:
	rm -rf ./build/