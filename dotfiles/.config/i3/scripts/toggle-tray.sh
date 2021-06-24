#!/bin/bash

if [[ $(pgrep stalonetray -x) ]]; then
    killall stalonetray
else
    stalonetray &
fi
