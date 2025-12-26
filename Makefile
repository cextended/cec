CXX := g++
BUILD := build
BIN := bin
TARGET := $(BIN)/segvc

STD := -std=c++17
INCLUDES := -I./include

MODE ?= release

COMMON_FLAGS := $(STD) $(INCLUDES)

ifeq ($(MODE),release)
    CXXFLAGS := $(COMMON_FLAGS) \
        -O3 \
        -march=native \
        -flto \
        -DNDEBUG
else ifeq ($(MODE),dev)
    CXXFLAGS := $(COMMON_FLAGS) \
        -Og \
        -g3 \
        -fno-omit-frame-pointer \
        -DDEBUG \
        -fsanitize=address,undefined
else
    $(error Unknown MODE: $(MODE))
endif

# ========================
# SOURCES
# ========================

SRCS_PROGRAM := programs/compiler.cxx
SRCS_SRC := $(shell find src -type f -regex '.*\.\(cxx\|cpp\)$$')
SRCS := $(SRCS_PROGRAM) $(SRCS_SRC)

OBJS := $(patsubst %, $(BUILD)/%.o, $(SRCS:/=_))

# ========================
# RULES
# ========================

.PHONY: all dev clean

all: $(TARGET)

dev:
	$(MAKE) MODE=dev

$(TARGET): $(OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD)/%.o: %
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) $(BUILD)
