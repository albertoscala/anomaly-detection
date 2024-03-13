# Anomaly Detection

## Table of Contents
- [Anomaly Detection](#anomaly-detection)
  - [Table of Contents](#table-of-contents)
  - [Project Requirements](#project-requirements)
  - [Instructions](#instructions)

## Project Requirements

Si progetti un semplice sistema di anomaly detection per uno stream di dati. Il rilevatore di anomalie calcola il valor medio di ogni stream e la covarianza dell’insieme di streams (visto come una serie temporale multivariata) su una finestra temporale di ampiezza W configurabile. Ogni volta che uno dei valori medi o delle covarianze si discosta significativamente da quelli correnti lancia un allarme. Il progetto deve includere i seguenti componenti:
1. Un modello (test generator) che legge uno stream di dati da file csv e lo manda su altrettante streams Redis. Un possibile file csv con dati reali verr`a fornito dal docente. 
2. Un sistema che dalle stream Redis calcola il valor medio per ogni stream e lo salva nel DB.
3. Un sistema che dalle stream Redis calcola la coviaranza per ogni coppia di stream e la salva nel DB.
4. Monitors per almeno tre propriet`a funzionali.
5. Monitors per almeno due propriet`a non-funzionali.

## Instructions

Per farlo funzionare devi prima scaricare il progetto usando github desktop.
Successivamente ti scarichi il dataset da questo link: https://drive.google.com/file/d/1bWWsa7J1ttX_Muz-zIAD1P2BW-Zg0VeX/view?usp=drive_link

Una volta scaricato il dataset, lo devi mettere nella cartella `dataset` del progetto.

Nel file zip ci sono dei file csv:
1. `dataset_clean.csv` è il file dataset completo
2. gli altri è il dataset spezzetato per comodità

