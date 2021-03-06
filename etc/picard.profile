# Firejail profile for picard
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/picard.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ${HOME}/.cache/MusicBrainz
noblacklist ${HOME}/.config/MusicBrainz

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-devel.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc

caps.drop all
no3d
nogroups
nonewprivs
noroot
nosound
novideo
protocol unix,inet,inet6
seccomp
shell none

private-dev
private-tmp

noexec ${HOME}
noexec /tmp
