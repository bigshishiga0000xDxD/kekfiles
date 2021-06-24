#!/bin/bash

# Terminate already running bar instances
killall -q polybar

# Wait until the proceses have been shutdown
while pgrep -u $UID -x polybar >/dev/null; do sleep 1; done

# Launch Polybar, using default config ~/.config/polybar/config
polybar bar &

# Symlink spotify config
rm /tmp/ipc-bottom
ln -s /tmp/polybar_mqueue.$! /tmp/ipc-bottom

echo message >/tmp/ipc-bottom
