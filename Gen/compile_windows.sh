#!/bin/bash

if [ ! -d "mariadb_windows" ]; then
  wget https://downloads.mariadb.com/Connectors/c/connector-c-3.3.5/mariadb-connector-c-3.3.5-win64.zip
  unzip mariadb-connector-c-3.3.5-win64.zip -d mariadb_windows
fi 

x86_64-w64-mingw32-gcc -Wall -Wextra -std=c99 -pedantic \
  -Isrc -Imariadb_windows/include \
  src/main.c src/database.c src/calculations.c \
  -Lmariadb_windows/lib \
  -lmariadb -lws2_32 -lshlwapi \
  -o NuGen.exe
echo "Done"
