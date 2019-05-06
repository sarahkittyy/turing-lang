//This program NOTs all the bits in the input.
> 100100011001

state main: //Programs start here
//turn 0 into 1, and continue in main (head will be moved forward)
0 -> 1 -> main
//turn 1 into 0, and continue in main
1 -> 0 -> main
//when we reach a blank (end of input), halt.
. -> . -> halt