# mortal

##

frame duration: how long a keyframe lasts

When a KF reaches its end, it will automatically switch to the next KF (wrapping around if necessary)

KFs with a duration of 0 will not automatically switch to the next KF, requiring manual input

## keybinds

-   `WASD` - move camera
-   `QE` - zoom camera
-   `P` - toggle between 'play' mode and 'edit' mode
-   `R` - reset (play mode: starts from first keyframe; edit mode: stays on current keyframe)
-   `SPACE` - next keyframe

# TODO:

-   import/export:

    -   file dialog
    -   error handling

-   editor:
    -   copy/paste
    -   insert
    -   move KF
