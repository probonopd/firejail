# Firejail profile for filezilla
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/filezilla.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ${HOME}/.config/filezilla
noblacklist ${HOME}/.filezilla

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-programs.inc

caps.drop all
netfilter
nonewprivs
noroot
nosound
protocol unix,inet,inet6
seccomp
shell none

private-bin filezilla,uname,sh,bash,dash,python,lsb_release,fzputtygen,fzsftp
private-dev
private-tmp
