#!/bin/bash
for i in {1..10}
do
    echo "Spawning client $i"
    ./build/Debug/example-qt-tcp-client &
done
echo "All clients spawned."
# Wait for all background processes to finish
wait
echo "All clients have finished."