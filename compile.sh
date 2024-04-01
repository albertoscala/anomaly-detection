#!/bin/sh

g++ anomaly-detection.cpp postgre.cpp postgre.hpp redis.cpp redis.hpp test-generator.cpp test-generator.hpp statistics.hpp csv.hpp json.hpp -o binaries/anomaly-detection -lpqxx -lpq -lhiredis
