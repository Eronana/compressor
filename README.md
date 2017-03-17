# compressor
This is a simply compressor, it implemented lz77 and huffman algorithm

`data` -> `lz77` -> `huffman` -> `save bit stream`

It read all data in memory and compress it, so don't compress huge file if you haven't enough memory.

## Build
```
make
```

## Run
```
./main
```

## Help
```
./main -h
```

## Test
```
./test.sh test.txt
```
