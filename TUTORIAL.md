# T-LANG TUTORIAL

This is a really simple implementation of a turing machine.

Feel free to view examples for examples of turing programs.

The turing tape is a 1000-long wrapping tape of ones, zeros, and blanks.

## Comments

Use // for commenting (C Style).

## Initial tape

The initial tape can be defined as such:

```cpp
> 000111... //0 for 0, 1 for 1, . for blank.
```

## States

```cpp
//This program NOTs all the bits in the input.
> 100100011001

state main: //Programs start here
//turn 0 into 1, and continue in main (head will be moved forward)
0 -> 1 -> main
//turn 1 into 0, and continue in main
1 -> 0 -> main
//when we reach a blank (end of input), halt.
. -> . -> halt
```

## Multiple States.

```cpp
//This program finds the successor of the input number.
> 00101

//Change nothing until the end, and move to the succ state.
state main:
0->0->main
1->1->main
.->.->$succ //The $ means to reverse the direction of the head when switching to this state.

//Gets the successor of the input number.
state succ:
0 -> 1 -> halt //If we can change a 0 to 1, halt
1 -> 0 -> succ //If it's a 1, turn it to a 0 and continue
. -> 1 -> halt //Halt the program at a blank, setting it to 1 (carry bit)
```

## Examples

These examples will be in examples/ (feel free to create pull requests to add more).