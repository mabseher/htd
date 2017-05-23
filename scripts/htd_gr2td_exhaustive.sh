#!/bin/bash

STORAGE_DIRECTORY=`dirname "$(readlink -f "$0")"`

exec "${STORAGE_DIRECTORY}/htd_main" --input gr --output td --opt width --iterations 0 --print-progress --preprocessing full --strategy challenge "$@" <&0
