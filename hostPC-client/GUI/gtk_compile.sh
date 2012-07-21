#!/bin/bash

gcc proj1.c -o base `pkg-config --cflags --libs gtk+-2.0`
