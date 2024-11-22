.PHONY: build run test

build: clean-build
	mkdir build
	git submodule init
	git submodule update
	cd ./build; cmake ..; make all

run:
	./build/LW1/lab1
	
test:
	./build/tests/*_test

clean-build:
	rm -rf ./build/