#!/bin/sh

g++ anomaly-detection.cpp postgre.cpp postgre.hpp redis.cpp redis.hpp test-generator.cpp test-generator.hpp statistics.hpp csv.hpp json.hpp monitor.hpp monitor.cpp -o binaries/anomaly-detection -lpqxx -lpq -lhiredis
