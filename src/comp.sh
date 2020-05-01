#!/bin/bash

gcc game.c collision.c loadtextures.c loadMapObjs.c -lSDL2 -lSDL2_ttf -lSDL2main -lSDL2_image -o game
./game
