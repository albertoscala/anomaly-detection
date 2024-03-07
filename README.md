# Anomaly Detection

## Table of Contents
- [Anomaly Detection](#anomaly-detection)
  - [Table of Contents](#table-of-contents)
  - [Project Requirements](#project-requirements)

## Project Requirements

Si progetti un semplice sistema di anomaly detection per uno stream di dati. Il rilevatore di anomalie calcola il valor medio di ogni stream e la covarianza dell’insieme di streams (visto come una serie temporale multivariata) su una finestra temporale di ampiezza W configurabile. Ogni volta che uno dei valori medi o delle covarianze si discosta significativamente da quelli correnti lancia un allarme. Il progetto deve includere i seguenti componenti:
1. Un modello (test generator) che legge uno stream di dati da file csv e lo manda su altrettante streams Redis. Un possibile file csv con dati reali verr`a fornito dal docente. 
2. Un sistema che dalle stream Redis calcola il valor medio per ogni stream e lo salva nel DB.
3. Un sistema che dalle stream Redis calcola la coviaranza per ogni coppia di stream e la salva nel DB.
4. Monitors per almeno tre propriet`a funzionali.
5. Monitors per almeno due propriet`a non-funzionali.