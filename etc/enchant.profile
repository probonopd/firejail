# Firejail profile for enchant
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/enchant.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ~/.config/enchant

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc

caps.drop all
netfilter
nogroups
nonewprivs
noroot
nosound
protocol unix
seccomp
shell none
tracelog

# private-bin enchant
# private-dev
# private-etc fonts
# private-tmp
