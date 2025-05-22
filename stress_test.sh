#!/bin/bash

BINARY=./test_B
ITERATIONS=10000
LOG_DIR=helgrind_logs
mkdir -p $LOG_DIR

echo "Running $ITERATIONS times on $BINARY"

for i in $(seq 1 $ITERATIONS); do
  # OUTFILE=$LOG_DIR/run_$i.txt
  echo "Run $i..."
  # valgrind --tool=helgrind --quiet --log-file=$OUTFILE $BINARY
  $BINARY

  # if grep -q "Possible data race" $OUTFILE || grep -q "Conflicting" $OUTFILE || grep -q "deadlock" $OUTFILE; then
  # echo "!!! Issue found on run $i — see $OUTFILE"
  # fi
done

echo "Done."
