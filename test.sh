make
FILENAME=$1
echo "------[ compressing ]------"
./main "/tmp/test.compressed" "$FILENAME" -c -level 9
echo "------[ uncompressing ]------"
./main "/tmp/test.uncompressed" "/tmp/test.compressed" -x
echo "------[ cmp ]------"
echo "compare \"$FILENAME\" and \"/tmp/test.uncompressed\""
cmp "$FILENAME" "/tmp/test.uncompressed" && echo "OK"
