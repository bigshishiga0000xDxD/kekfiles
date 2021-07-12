export XDG_SESSION_TYPE=x11
export GDK_BACKEND=x11

/usr/bin/numlockx on &
dbus-update-activation-environment --systemd DBUS_SESSION_BUS_ADDRESS DISPLAY XAUTHORITY &
otd &

udisksctl mount --no-user-interaction -b /dev/sdb1 &
udisksctl mount --no-user-interaction -b /dev/sdb3 &

spotblock &
NetworkManager &
flameshot &
blueman-applet &
/usr/lib/geoclue-2.0/demos/agent &
redshift &
dunst &

setxkbmap -layout us,ru
setxkbmap -option 'grp:alt_shift_toggle'

~/.fehbg &
exec i3
