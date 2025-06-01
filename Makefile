.PHONY:  build clean

BUILD_DIR := build


build:
	@mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)



clean:
	rm -rf $(BUILD_DIR)