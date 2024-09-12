#!/bin/bash
# Program:
#       This script exec init_58100.
# 2024/08/29 Charlie.Tsai

echo -e "[INFO] Run init_58100 scripts \n"

./etc/startup/init_58100

ret=$?

if [ $ret -ne 0 ]; then
    echo "[ERROR] init_58100 failed，ret: $ret"
else
    echo "[SUCCESS] init_58100 successfully，ret: $ret"
fi

