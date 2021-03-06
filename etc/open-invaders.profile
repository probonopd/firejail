# Firejail profile for open-invaders
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/open-invaders.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ~/.openinvaders

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc

mkdir ~/.openinvaders
whitelist ~/.openinvaders
include /etc/firejail/whitelist-common.inc

caps.drop all
net none
nogroups
nonewprivs
noroot
protocol unix,netlink
seccomp
shell none

# private-bin open-invaders
private-dev
# private-etc none
private-tmp
