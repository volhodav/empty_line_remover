#!/bin/sh

# this script is for testing purposes
# It will create a file and will write for 0 to 10 in it
# on each line skipping one line in between


# create a file in the same directory as the script
touch test.txt

for i in {0..10}
do
    echo $i >> test.txt
    echo "" >> test.txt
done

# print the file
cat test.txt
