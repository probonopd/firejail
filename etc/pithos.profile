# Firejail profile for pithos
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/pithos.local
# Persistent global definitions
include /etc/firejail/globals.local


include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc
include /etc/firejail/whitelist-common.inc

caps.drop all
netfilter
no3d
nogroups
nonewprivs
noroot
novideo
protocol unix,inet,inet6
seccomp
shell none

disable-mnt
private-dev
private-tmp

noexec ${HOME}
noexec /tmp
