# Firejail profile for arm
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/arm.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ${HOME}/.arm

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc

mkdir ${HOME}/.arm
whitelist ${HOME}/.arm
include /etc/firejail/whitelist-common.inc

caps.drop all
ipc-namespace
netfilter
no3d
nogroups
nonewprivs
noroot
nosound
novideo
protocol unix,inet,inet6
seccomp
shell none
tracelog

disable-mnt
# private-bin arm,tor,sh,python2,python2.7,ps,lsof,ldconfig
private-dev
private-etc tor,passwd
private-tmp

noexec ${HOME}
noexec /tmp
