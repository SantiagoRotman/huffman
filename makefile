main: main.c compressor.c decompressor.c io.c resources.c
	- gcc -Wall -Wextra -Werror -std=c99 -g main.c compressor.c decompressor.c resources.c io.c -o main

testCompressor: tests/testCompressor.c compressor.c io.c resources.c io.c
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testCompressor.c compressor.c resources.c io.c -o testCompressor

testDecompressor: tests/testDecompressor.c decompressor.c io.c resources.c
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testDecompressor.c decompressor.c resources.c io.c -o testDecompressor

testResources: tests/testResources.c resources.c 
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testResources.c resources.c -o testResources
