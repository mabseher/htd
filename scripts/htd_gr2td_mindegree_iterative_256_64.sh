#!/bin/bash

STORAGE_DIRECTORY=`dirname "$(readlink -f "$0")"`

exec "${STORAGE_DIRECTORY}/htd_main" --input gr --output td --ordering min-degree --opt width --iterations 256 --non-improvement-limit 64 --print-opt-progress "$@" <&0
