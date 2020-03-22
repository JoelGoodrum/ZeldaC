#!/bin/bash

gcc game.c collision.c -lSDL2 -lSDL2main -lSDL2_image -o game
./game
