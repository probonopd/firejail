# Firejail profile for idea.sh
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/idea.sh.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ${HOME}/.IdeaIC*
noblacklist ${HOME}/.android
noblacklist ${HOME}/.gitconfig
noblacklist ${HOME}/.gradle
noblacklist ${HOME}/.java
noblacklist ${HOME}/.local/share/JetBrains
noblacklist ${HOME}/.ssh
noblacklist ${HOME}/.tooling

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-passwdmgr.inc
include /etc/firejail/disable-programs.inc

caps.drop all
netfilter
nogroups
nonewprivs
noroot
novideo
protocol unix,inet,inet6
seccomp
shell none

private-dev
# private-tmp

noexec /tmp
