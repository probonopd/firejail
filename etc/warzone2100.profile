# Firejail profile for warzone2100
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/warzone2100.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ~/.warzone2100-3.*

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc

# mkdir ~/.warzone2100-3.1
# mkdir ~/.warzone2100-3.2
whitelist ~/.warzone2100-3.1
whitelist ~/.warzone2100-3.2
include /etc/firejail/whitelist-common.inc

caps.drop all
netfilter
nogroups
nonewprivs
noroot
protocol unix,inet,inet6,netlink
seccomp
shell none
tracelog

disable-mnt
private-bin warzone2100
private-dev
private-tmp
