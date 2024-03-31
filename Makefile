# Makefile to compile the anomaly detection program

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c++11

# Source files 
SRC = anomaly-detection.cpp postgre.cpp postgre.hpp redis.cpp redis.hpp test-generator.cpp test-generator.hpp statistics.hpp csv.hpp

# Libraries such as libpqxx and hiredis
LIBS = -lpqxx -lpq -lhiredis

# Executable name
EXE = binaries/anomaly-detection

# Makefile rules
all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(LIBS)

clean:
	rm -f $(EXE)
