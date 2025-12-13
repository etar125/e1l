#!/bin/bash
# build.sh
# etar125

CC=gcc
CFLAGS="-O2 -Wall -Wextra -Iinclude -fPIC"

clean () {
    rm -rf build
    rm -rf bin/*e1l*
}

objs () {
    mkdir -p build
    for src in $(ls -1 src); do
        $CC -c $CFLAGS src/$src -o build/$(basename $src .c).o
    done
}

static () {
    ar rcs bin/libe1l.a build/*
    ranlib bin/libe1l.a
}

shared () {
    $CC -shared build/* -o bin/libe1l.so
}

tests () {
    for src in $(ls -1 tests); do
        $CC $CFLAGS build/* tests/$src -o bin/$(basename $src .c)
    done
}

start () {
    clean
    if [ -z "$1" ] || [ "$1" = "all" ]; then
        objs
        static
        shared
    elif [ "$1" = "static" ]; then
        objs
        static
    elif [ "$1" = "shared" ]; then
        objs
        shared
    elif [ "$1" = "tests" ]; then
        objs
        tests
    else
        objs
        static
        shared
    fi
}

start $1
