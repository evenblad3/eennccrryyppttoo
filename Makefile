CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHandling -Isrc/app/processes

MAIN_TARGET = encrypt_decrypt
CRYPTION_TARGET = cryption

OMMON_SRC = src/app/fileHandling/ReadEnv.cpp
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)

MAIN_SRC = main.cpp \
           src/app/processes/ProcessManagement.cpp \
           src/app/fileHandling/IO.cpp \
           src/app/encryptDecrypt/Cryption.cpp

CRYPTION_SRC = src/app/encryptDecrypt/CryptionMain.cpp \
               src/app/encryptDecrypt/Cryption.cpp \
               src/app/fileHandling/IO.cpp 

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
CRYPTION_OBJ = $(CRYPTION_SRC:.cpp=.o)

all: $(MAIN_TARGET) $(CRYPTION_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ) $(COMMON_OBJ)
	@echo "Building $(MAIN_TARGET)..."
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CRYPTION_TARGET): $(CRYPTION_OBJ) $(COMMON_OBJ)
	@echo "Building $(CRYPTION_TARGET)..."
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

ifeq ($(OS),Windows_NT)
    RM = cmd /c del /Q /F
else
    RM = rm -f
endif

clean:
	@echo "Cleaning up..."
	$(RM) main.o \
          src\app\processes\ProcessManagement.o \
          src\app\fileHandling\IO.o \
          src\app\fileHandling\ReadEnv.o \
          src\app\encryptDecrypt\Cryption.o \
          src\app\encryptDecrypt\CryptionMain.o \
          encrypt_decrypt cryption

.PHONY: clean all
