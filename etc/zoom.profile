# Firejail profile for zoom
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/zoom.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ~/.config/zoomus.conf

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-programs.inc

mkdir ~/.zoom
whitelist ~/.cache/zoom
whitelist ~/.zoom
include /etc/firejail/whitelist-common.inc

caps.drop all
netfilter
nonewprivs
noroot
protocol unix,inet,inet6
seccomp

private-tmp
