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
-   `SHIFT + SPACE` - previous keyframe
-   `C` - copy current pose
-   `V` - paste copied pose to current keyframe

# TODO:

-   import/export:

    -   file dialogs
    -   error handling (cleanup)

-   editor:

    -   move KF

-   sim:

    -   adjust forces
    -   give bro a spine

-   dev:
    -   add raygui and json.hpp as submodules
