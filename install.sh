#!/bin/bash
# install.sh
# etar125

./build.sh
LIB_DIR=/usr/lib
INCLUDE_DIR=/usr/include

install -d ${DESTDIR}${LIB_DIR}
install -d ${DESTDIR}${INCLUDE_DIR}
install -m 644 bin/libe1l.a ${DESTDIR}${LIB_DIR}/
install -m 755 bin/libe1l.so ${DESTDIR}${LIB_DIR}/
install -m 644 include/*.h ${DESTDIR}${INCLUDE_DIR}/
