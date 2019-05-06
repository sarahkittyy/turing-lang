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