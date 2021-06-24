export XDG_SESSION_TYPE=x11
export GDK_BACKEND=x11

/usr/bin/numlockx on &
dbus-update-activation-environment --systemd DBUS_SESSION_BUS_ADDRESS DISPLAY XAUTHORITY &
otd &

spotblock &
NetworkManager &

flameshot &
blueman-applet &

/usr/lib/geoclue-2.0/demos/agent &
redshift &

setxkbmap -layout us,ru
setxkbmap -option 'grp:alt_shift_toggle'

~/.fehbg &
exec i3
