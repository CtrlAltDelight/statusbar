# StatusBar
Creating my statusbar. Tested on dwm with status2d patch but I'm sure it can be adapted to many different purposes.

Requires a [Nerd Font](https://www.nerdfonts.com/#home) for the icons to display correctly.

## Quick start
Clone this repository:

```
git clone https://github.com/CtrlAltDelight/statusbar
```

Make the executable for the C code:
```
make
```

Run the shell script in the background:
```
./statusbar.sh &
```
Your dwm  statusbar should now display modules. If you see strange symbolds, make sure you patch your dwm with status2d or use my dwm fork [CtrlAltDelight/dwm](https://github.com/CtrlAltDelight/dwm).

## Currently there are modules for
- Weather 
- volume
- time and date

# TODO
- Make as many modules reactive as possible
    - less reliance on update timing and will feel more responsive
- volume level module
    - make it respond to an event instead of being run every second.
- email
    - how many unread
    - little email emoticon
- moon phase
    - shows respective emoji
- music player status
    - must work well with spotifyd
- calendar events
    - this will probably involve working with a specific calendar application
- task tracking softwares status
    - which task tracker to use?
- keyboard layout
    - language/qwerty-workman-etc.
- make a config file to read from that can toggle which modules are active
- make it so you can reorder it in the config
- make it so you don't have to run every module every time you want to update one of them
