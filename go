#!/bin/bash

BINARY=nuts333

[ -f syslog ] && mv syslog syslog.$(date +%Y%m%d_%H%M%S)

[ -x ${BINARY} ] && ./${BINARY} || { echo "Executable binary '${BINARY}' not found!" ; exit 1 ; }
