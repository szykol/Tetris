SRC_FILES=$(wildcard src/*)

.PHONY: clean

SFML_DIR ?=
CMAKE_BUILD_TYPE ?= Debug

CMAKE_ARGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

ifneq ($(SFML_DIR),)
	CMAKE_ARGS += -DSFML_DIR=$(SFML_DIR)
endif

all: proj

build:
	mkdir -p $@
	touch $@

proj: build build/Tetris compile_commands.json

build/Tetris: $(SRC_FILES) CMakeLists.txt
	cd build && cmake $(CMAKE_ARGS) .. && make
	touch $@

compile_commands.json: build/Tetris
	cp build/$@ $@

clean:
	rm -rf build
