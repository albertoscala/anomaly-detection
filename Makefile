CC = g++
CFLAGS = -Wall -Wextra -std=c++11

all: anomaly-detection

anomaly-detection: anomaly-detection.cpp 
	$(CC) $(CFLAGS) -o anomaly-detection anomaly-detection.cpp test-generator.cpp test-generator.hpp -lhiredis

clean:
	rm -f test-generator anomaly-detection
