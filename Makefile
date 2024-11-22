.PHONY: build run test

build: clean-build
	mkdir build
	git submodule init
	git submodule update
	cd ./build; cmake ..; make all

run:
	cd ./LW1
	ls
	pwd

test:
	./build/*_test

clean-build:
	rm -rf ./build/