# mortal

started as backflip madness clone, got sidetracked into animation editor

![](https://github.com/xTarzx/mortal/blob/master/docs/img/mortal.gif)

## info

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

-   editor:
    -   toggle motor
    -   move KF (can be done by copying and pasting)

-   sim:
    -   give bro a spine
