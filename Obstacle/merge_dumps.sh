#!/bin/bash

echo -ne    ""              > test.csv
cat         "obst_00.csv"  >> test.csv 
tail -n +2  "obst_01.csv"  >> test.csv
tail -n +2  "obst_02.csv"  >> test.csv
tail -n +2  "obst_03.csv"  >> test.csv
tail -n +2  "obst_04.csv"  >> test.csv
tail -n +2  "obst_05.csv"  >> test.csv
tail -n +2  "obst_06.csv"  >> test.csv
tail -n +2  "obst_07.csv"  >> test.csv
tail -n +2  "obst_08.csv"  >> test.csv
tail -n +2  "obst_09.csv"  >> test.csv
tail -n +2  "obst_10.csv"  >> test.csv
tail -n +2  "obst_11.csv"  >> test.csv
tail -n +2  "obst_12.csv"  >> test.csv
tail -n +2  "obst_13.csv"  >> test.csv
tail -n +2  "obst_14.csv"  >> test.csv
tail -n +2  "obst_15.csv"  >> test.csv
tail -n +2  "obst_16.csv"  >> test.csv
tail -n +2  "obst_17.csv"  >> test.csv
tail -n +2  "obst_18.csv"  >> test.csv
dos2unix test.csv
rm -f obst_*.csv

