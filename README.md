# i3blocks-scripts

My scripts for i3blocks.

# makefile

| command | description |
| - | - |
| make | compiles all c files |
| make compile | compiles all c files |
| make clean | removes all c compiles |
| make install | installs all executables and scripts to ~/.config/i3/blocks |
| make uninstall | removes all executables and scripts from ~/.config/i3/blocks |

# blocks

## executables

| name | dependencies | description |
| - | - | - |
| battery.c | | |
| cpu.c | | |
| fan.c | | |
| home.c | | |
| macspoof.c | ethtool | |
| mem.c | | |
| network.c | | |
| stopwatch.c | | |
| temp.c | | |
| userinfo.c | | |

## scripts

| name | dependencies | description |
| - | - | - |
| bluetooth.sh | bluetooth, blueman | |
| brightness.sh | brightnesscontrol (linux repository) | |
| capslock.sh  | xdotool | |
| gitstatus.sh | git | |
| helper.sh | | |
| keymap.sh | | |
| mic.sh | alsa-utils | |
| nextsong.sh | playerctl | |
| playpause.sh | playerctl | |
| previoussong.sh | playerctl | |
| spoofed.sh | macchanger | |
| volume.sh | volumecontrol (linux repository) | |
| xinput.sh | xorg-xinput | |

