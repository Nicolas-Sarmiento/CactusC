.PHONY: build clean 

build: 
	cmake -B build
	cmake --build build

clean:
	rm -rf build
