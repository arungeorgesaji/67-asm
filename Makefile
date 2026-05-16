CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2 -g

BUILD_DIR := build
BIN_DIR := bin

SRC := $(shell find src -name '*.cpp')
OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

TARGET := $(BIN_DIR)/67asm

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

debug: CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0 -g3
debug: clean all

release: CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O3 -DNDEBUG
release: clean all

format:
	find src include -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i

-include $(DEP)

.PHONY: all run clean debug release format
