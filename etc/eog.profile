# Firejail profile for eog
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/eog.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ~/.Steam
noblacklist ~/.config/eog
noblacklist ~/.local/share/Trash
noblacklist ~/.steam

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc

caps.drop all
net none
no3d
nogroups
nonewprivs
noroot
nosound
novideo
protocol unix
seccomp
shell none

private-bin eog
private-dev
private-etc fonts
private-tmp

memory-deny-write-execute
noexec ${HOME}
noexec /tmp
