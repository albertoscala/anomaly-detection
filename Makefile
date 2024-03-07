CC = g++
CFLAGS = -Wall -Wextra -std=c++11

all: test-generator anomaly-detection

test-generator: test-generator.cpp
	$(CC) $(CFLAGS) -o test-generator test-generator.cpp -lhiredis

anomaly-detection: anomaly-detection.cpp
	$(CC) $(CFLAGS) -o anomaly-detection anomaly-detection.cpp 

clean:
	rm -f test-generator anomaly-detection
