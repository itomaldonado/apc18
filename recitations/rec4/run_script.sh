#! /bin/bash

for i in {1..32}; do
  export OMP_NUM_THREADS=$i
  RES=`./${1}`
  echo "Run $i -- $RES"
done