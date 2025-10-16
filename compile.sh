#!/bin/bash

# Pour lancer, utiliser sh compile.sh ou bash compile.sh ou ./compile.sh (nécessite autorisation (chmod))

mkdir -p build

SRC_FILES=$(find src/ -name '*.c')

gcc $SRC_FILES -o ./build/application -lSDL3 -Iinclude

./build/application
