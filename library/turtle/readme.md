# Turtle Graphics

Turtle Graphics implementation in Forth, meant to run on the [interpreter](../../interpreter/) and future VMs.

The Turtle begins at the center of the canvas, heading "North". You may `go` to another point or `head` in another direction (or use `pose` to accomplish both at once). `begin` to clear the canvas and reset the pose. Use `turn` and `move` to draw. There is no pen-up/down, but instead a `jump` which moves without plotting.
