# Firejail profile for weechat
# This file is overwritten after every install/update
# Persistent local customizations
include /etc/firejail/weechat.local
# Persistent global definitions
include /etc/firejail/globals.local

noblacklist ${HOME}/.weechat

include /etc/firejail/disable-common.inc
include /etc/firejail/disable-programs.inc

caps.drop all
netfilter
nonewprivs
noroot
protocol unix,inet,inet6
seccomp

# no private-bin support for various reasons:
# Plugins loaded: alias, aspell, charset, exec, fifo, guile, irc,
# logger, lua, perl, python, relay, ruby, script, tcl, trigger, xferloading plugins
