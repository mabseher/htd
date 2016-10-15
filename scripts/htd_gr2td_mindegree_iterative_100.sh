#!/bin/bash

STORAGE_DIRECTORY=`dirname "$(readlink -f "$0")"`

exec "${STORAGE_DIRECTORY}/htd_main" --input gr --output td --ordering min-degree --opt width --iterations 100 --print-opt-progress "$@" <&0
