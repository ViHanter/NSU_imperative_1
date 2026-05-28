gcc -o checked_solution.exe -I./zlib -I./zlib/minizip -DUSE_CRYPT ./zlib/*.c ./zlib/minizip/unzip.c ./zlib/minizip/ioapi.c test.c
pause