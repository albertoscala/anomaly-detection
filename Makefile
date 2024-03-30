CC = g++
CFLAGS = -Wall -Wextra -std=c++11

all: anomaly-detection

anomaly-detection: anomaly-detection.cpp 
	$(CC) $(CFLAGS) -o binaries/anomaly-detection anomaly-detection.cpp redis.cpp redis.hpp test-generator.cpp test-generator.hpp postgre.cpp postgre.hpp -lhiredis -lpqxx -lpq

clean:
	rm -f anomaly-detection
