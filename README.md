# Anomaly Detection

## Table of Contents
- [Anomaly Detection](#anomaly-detection)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Project Requirements](#project-requirements)
  - [Installation and Usage](#installation-and-usage)
  - [Implementation](#implementation)
    - [Test Generator](#test-generator)
    - [Redis](#redis)
    - [Postgresql](#postgresql)
    - [Statistics](#statistics)
  - [Anomaly Detector](#anomaly-detector)
  - [License](#license)

## Introduction

This repository is showcasing our Anomaly Detection System (made by me and my [collegue](https://github.com/yaraoyoussef)), developed as our final project in the software engineering course. We utilized basic statistical techniques like mean and covariance to detects anomalies in a stream of data, and to build the system we used redis, postgresql, with c++ as the main programming languages.

## Project Requirements

The project request given from the professor was:

You should design a simple anomaly detection system for a data stream. The anomaly detector calculates the mean value of each stream and the covariance of the set of streams (seen as a multivariate time series) over a time window of configurable amplitude W. Whenever one of the mean values or covariances deviates significantly from the current values, an alarm is triggered. The design must include the following components:

1. A model (test generator) that reads a data stream from csv files and sends it to as many Redis streams. A possible csv file with real data will be provided by the teacher;
2. A system which calculates the average value for each stream from the Redis streams and saves it in the DB;
3. A system which from the Redis streams calculates the coviarance for each pair of streams and saves it in the DB;
4. Monitors for at least three functional properties;
5. Monitors for at least two non-functional properties.

## Installation and Usage

To run the project, you need to first of all clone the repository:

```bash
git clone https://github.com/albertoscala/anomaly-detection.git
```

Then if you are running on arch linux, you can install the dependencies with the following command:

```bash
chmod +x dependencies.sh
./dependencies.sh
```

Create the binaries folder with the following command:

```bash
mkdir binaries
```

After that, you can compile and run the project with the following command:

```bash
# Compile the project
chmod +x compile.sh
./compile.sh

# Run the project
./binaries/anomaly-detection
```

## Implementation

### Test Generator

### Redis

### Postgresql

### Statistics

## Anomaly Detector

## License

[MIT](https://choosealicense.com/licenses/mit/)
