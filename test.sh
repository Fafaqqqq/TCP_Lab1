#!/bin/bash

RESULT=example/bin/result.txt

TEST1=(
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

TEST2=(
    "--matrix 1 2 --matrix 2 1 --threads 2"
    "--matrix 2 5 --matrix 5 2 --threads 2"
    "--matrix 10 5 --matrix 5 10 --threads 2"
    "--matrix 10 10 --matrix 10 10 --threads 2"
    "--matrix 10 500 --matrix 500 10 --threads 2"
    "--matrix 1000 500 --matrix 500 2000 --threads 2"
    "--matrix 200 500 --matrix 500 200 --threads 2"
    "--matrix 190 50 --matrix 50 190 --threads 2"
    "--matrix 10000  5 --matrix 5 10000 --threads 2"
    "--matrix 1000 1000 --matrix 1000 1000 --threads 2"
    "--matrix 5 5000 --matrix 5000 5 --threads 2"
    "--matrix 1500 500 --matrix 500 1500 --threads 2"
  )

TEST3=(
      "--matrix 1 2 --matrix 2 1 --threads 1"
      "--matrix 2 5 --matrix 5 2 --threads 2"
      "--matrix 10 5 --matrix 5 10 --threads 3"
      "--matrix 10 10 --matrix 10 10 --threads 4"
      "--matrix 10 500 --matrix 500 10 --threads 5"
      "--matrix 1000 500 --matrix 500 2000 --threads 6"
      "--matrix 200 500 --matrix 500 200 --threads 7"
      "--matrix 190 50 --matrix 50 190 --threads 8"
      "--matrix 10000  5 --matrix 5 10000 --threads 9"
      "--matrix 1000 1000 --matrix 1000 1000 --threads 10"
      "--matrix 5 5000 --matrix 5000 5 --threads 11"
      "--matrix 1500 500 --matrix 500 1500 --threads 12"
      )

TEST4=(
      "--matrix 1 2 --matrix 2 1 --threads 1"
      "--matrix 1 2 --matrix 2 1 --threads 12"
      )

TEST5=(
      "--matrix 1000 200 --matrix 200 1000 --threads 1"
      "--matrix 1000 200 --matrix 200 1000 --threads 12"
      )

[ ! -z "$1" ] && RESULT=$1

cat /dev/null > $RESULT

echo "Discription:" >> $RESULT
echo "[P] - parallel calculating." >> $RESULT
echo "[NP] -not parallel calculating." >> $RESULT
echo >> $RESULT

echo "Test 1: Same size, different thread count." >> $RESULT
for i in ${!TEST1[@]}; do
  echo "Test 1.$i:" >> $RESULT
  echo "Programm arguments: ${TEST1[$i]}" >> $RESULT
  ./example/bin/lab1 ${TEST1[$i]} >> $RESULT
  echo >> $RESULT
done

echo "Test 2: Same thread number [2], different size." >> $RESULT
for i in ${!TEST2[@]}; do
  echo "Test 2.$i:" >> $RESULT
  echo "Programm arguments: ${TEST2[$i]}" >> $RESULT
  ./example/bin/lab1 ${TEST2[$i]} >> $RESULT
  echo >> $RESULT
done

echo "Test 3: Different size, different thread number." >> $RESULT
for i in ${!TEST3[@]}; do
  echo "Test 3.$i:" >> $RESULT
  echo "Programm arguments: ${TEST3[$i]}" >> $RESULT
  ./example/bin/lab1 ${TEST3[$i]} >> $RESULT
  echo >> $RESULT
done

echo "Test 4: A little size, min/maximum thread number." >> $RESULT
for i in ${!TEST4[@]}; do
  echo "Test 4.$i:" >> $RESULT
  echo "Programm arguments: ${TEST4[$i]}" >> $RESULT
  ./example/bin/lab1 ${TEST4[$i]} >> $RESULT
  echo >> $RESULT
done

echo "Test 5: A large size, min/maximum thread number." >> $RESULT
for i in ${!TEST5[@]}; do
  echo "Test 5.$i:" >> $RESULT
  echo "Programm arguments: ${TEST5[$i]}" >> $RESULT
  ./example/bin/lab1 ${TEST5[$i]} >> $RESULT
  echo >> $RESULT
done