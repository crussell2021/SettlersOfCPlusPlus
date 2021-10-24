SDL2_SHARED_DIR_PATH = C:\SDL2_w64-mingw32
OBJS = main.cpp # src files
CXX = g++# compiler
SDL2_INCLUDE_PATHS = -I${SDL2_SHARED_DIR_PATH}\include# SDL2 includes
SDL2_LIBRARY_PATHS = -L${SDL2_SHARED_DIR_PATH}\lib# SDL2 library path
COMPILER_FLAGS = -w -Wall
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ_NAME = bin/main.exe #output file

CXX      := -c++
CXXFLAGS := -Wall -Wextra #-Werror # -pedantic-errors
LDFLAGS  := ${SDL2_LIBRARY_PATHS} ${LINKER_FLAGS} #-L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := bin
TARGET   := main.exe
INCLUDE  := -Iinclude/ ${SDL2_INCLUDE_PATHS}
SRC      := $(wildcard src/*.cpp) # $(wildcard src/module1/*.cpp) $(wildcard src/module2/*.cpp) 

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

# all : src/$(OBJS)
# 	$(CXX) src/$(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/$(TARGET)

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
   


