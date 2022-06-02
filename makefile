main: main.c compresor.c decompressor.c io.c resources.c
	- gcc -Wall -Wextra -Werror -std=c99 -g main.c compresor.c decompressor.c resources.c io.c -o main

testCompresor: tests/testCompressor.c compresor.c io.c resources.c io.c
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testCompressor.c compresor.c resources.c io.c -o testCompresor

testDecompressor: tests/testDecompressor.c decompressor.c io.c resources.c
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testDecompressor.c decompressor.c resources.c io.c -o testDecompressor

testResources: tests/testResources.c resources.c 
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testResources.c resources.c -o testResources
