# Firejail profile for claws-mail
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/claws-mail.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ~/.claws-mail
noblacklist ~/.gnupg
noblacklist ~/.signature

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
protocol unix,inet,inet6
seccomp
shell none

private-dev
private-tmp
