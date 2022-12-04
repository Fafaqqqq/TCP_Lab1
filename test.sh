#!/bin/bash

RESULT=example/bin/result.txt

ARGS=(
      "--matrix 1000 500 --matrix 500 2000 --threads 1"
      "--matrix 1000 500 --matrix 500 2000 --threads 2"
      "--matrix 1000 500 --matrix 500 2000 --threads 3"
      "--matrix 1000 500 --matrix 500 2000 --threads 4"
      "--matrix 1000 500 --matrix 500 2000 --threads 5"
      "--matrix 1000 500 --matrix 500 2000 --threads 6"
      "--matrix 1000 500 --matrix 500 2000 --threads 7"
      "--matrix 1000 500 --matrix 500 2000 --threads 8"
      "--matrix 1000 500 --matrix 500 2000 --threads 9"
      "--matrix 1000 500 --matrix 500 2000 --threads 10"
      "--matrix 1000 500 --matrix 500 2000 --threads 11"
      "--matrix 1000 500 --matrix 500 2000 --threads 12"
    )

[ ! -z "$1" ] && RESULT=$1

cat /dev/null > $RESULT

echo "Discription:" >> $RESULT
echo "[P] - parallel calculating." >> $RESULT
echo "[NP] -not parallel calculating." >> $RESULT
echo >> $RESULT

for i in ${!ARGS[@]}; do
  echo "Test $i:" >> $RESULT
  ./example/bin/lab1 ${ARGS[$i]} >> $RESULT
  echo >> $RESULT
done
