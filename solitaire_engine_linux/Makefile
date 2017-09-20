CC=g++

BIN=bin
INCLUDE=include
TARGET=solitaireengine
SRC:=$(wildcard src/*.cpp)
OBJ:=$(patsubst src/%.cpp,bin/%.o,$(SRC))

CFLAGS=-g -Wall -I$(INCLUDE) -std=c++11

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(TARGET).cpp $^ $(CFLAGS)

$(OBJ): $(SRC)
	@mkdir -p bin
	$(CC) -c $(patsubst bin/%.o,src/%.cpp,$@) -o $@ $(CFLAGS)

clean:
	rm -rf $(TARGET) $(BIN)/*