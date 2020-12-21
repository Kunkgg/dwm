# Kunkgg’s build of dwm

Fork of [LukeSmithxyz](https://github.com/lukesmithxyz/dwm)

## Patches and features

xrdb

*   read colors from xrdb (.Xresources)

scratchpads

*   scratchpad0: alacritty terminal, mod+shift+enter

*   scratchpad1: ranger fm, mod+grave

sticky

*   windows can be made sticky

stacker

*   provides comprehensive utilities for managing the client stack.

noborder

*   Remove the border when there is only one window visible.

dwmc

*   Simple dwmc client using a fork of fsignal to communicate with dwm

vanitygaps

*   like i3-gaps around windows and bar

shiftview

*   shiftview to cycle tags

center

*   Add an iscentered rule to automatically center clients on the current monitor.

save floats

*   Saves size and position of every floating window before it is forced into tiled mode.
    If the window is made floating again, the old dimensions will be restored.

layouts patches

*   fibonacci

*   centeredmaster(centeredmaster and centeredfloatingmaster)

*   pertag, keeps layout, mwfact, barpos and nmaster per tag.

fullscreen patches

*   actualfullscreen

    +   Actually toggle fullscreen for a window, instead of toggling the
        status bar and the monocle layout.

*   alwaysfullscreen

    +   Do not allow the focus to drift from the active fullscreen
        client when using focusstack().
