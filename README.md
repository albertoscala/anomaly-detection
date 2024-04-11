# Anomaly Detection

## Table of Contents
- [Anomaly Detection](#anomaly-detection)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Project Requirements](#project-requirements)
  - [Installation and Usage](#installation-and-usage)
  - [Implementation](#implementation)
    - [Test Generator](#test-generator)
    - [Databases](#databases)
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

In this section, I will explain the implementation of the macro components of the project, how they work and how they interact with each other.

### Test Generator

Let's start with the test generator, which in the book [Software Engineering by Ian Sommerville](https://amzn.eu/d/dkWiTLj) is defined as: "A test generator is a program that generates test data for a system or component. The test generator may be used to generate test data for a range of different purposes, including unit testing, system testing, and acceptance testing."

In our case, the test generator reads a data stream from csv files and sends it to as many Redis streams. The data stream is a csv file with real data provided by the teacher, and the Redis streams are used to send the data to the other components of the system.

The actual implementation of the test generator is a local library made following the C++ style.
We made a class called `TestGenerator` that has a constructor that takes the path of the csv file and a `Redis` object as parameters.

In the same class we have just three methods:

- `bool readDataset()`: reads the data from the csv file and saves it locally in a vector of strings;
- `bool laodDataset()`: sends the data to the Redis streams with key equal to the timestamp of the data and value as the data itself;
- `int getTestSize()`: returns the size of the dataset (total number of lines).

### Databases

Now let's move one to the databases used in the project. These are just support libraries, in most of the cases they just wrap existing libraries and simplifies the usage of them.

#### Redis

For the Redis database, we used the `hiredis.h` library, and we made a libary called `Redis` that wraps the library and simplifies the usage of it.

The `Redis` library is always a class based library.

The `Redis` class has a constructor that takes the host and port of the Redis server as parameters, and it has the following methods:

- `bool alive()`: checks if the connection to the Redis server is alive;
- `bool sendData(string key, string value)`: sends a key-value pair to the Redis server;
- `bool getData(string key)`: receives the value mapped at the key from the Redis server.

#### Postgresql

For the Postgresql database, we used the `pqxx` library, a modern C++ library that provides a better interface to the Postgresql database.

The `Postgre` library is also a class based library.

The `Postgre` class has a constructor that takes as parameters:

- `string dbname`: the name of the database;
- `string user`: the user of the database;
- `string password`: the password of the user;
- `string hostname`: the address of the host;
- `string port`: the port of the host.

The class has the following methods:

- `bool tableExists(string table)`: checks if a table exists in the database;
- `bool flushTable(string table)`: deletes all the rows of a table;
- `bool createTable(string query)`: creates a table in the database give the query;
- `void postData(string table, int timestamp, string json_data)`: posts data to the database;

### Statistics

The statistics component is the core of the project, it calculates the mean value of each stream and the covariance of the set of streams (seen as a multivariate time series) over a time window of configurable amplitude W.

It is a class based library called `Statistics` and only contains static methods.

The class has the following methods:

- `static double mean(vector<double>& data)`: calculates the mean of a vector of doubles;
- `static double covariance(vector<double>& actual, vector<double>& precedent, double m_act, double m_prec)`: calculates the covariance of two vectors of doubles;
- `static vector<double> calculateDistance(vector<vector<double>>& values_a, vector<double>& mean_p)` : calculates the distance of the values from the mean.

### Anomaly Detector

The anomaly detector is the main component of the project, it calculates the mean value of each stream and the covariance of the set of streams (seen as a multivariate time series) over a time window of configurable amplitude W. Whenever one of the mean values or covariances deviates significantly from the current values, an alarm is triggered.

## License

[MIT](https://choosealicense.com/licenses/mit/)
