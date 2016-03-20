FOR ASSIGNMENT 4

TO USE:
run rake to install this version of urcc as a gem

run urcc on whatever c file you want to compile

IMPLEMENTATION:
pass is in bin/config/PASSES/lvn.rb

Reused the BasicBlock creation for the CFG creator, so any errors there
are likely due to that.

I probably abused the "c_dump" function to create a hash value, but it ended up 
working out find so whatever. A better way would have been to define a hashing
function for Node, though that might have been more tricky than it would have
been worth. 

I didn't implement the steward extension

All I did was replace a math expression with a variable which already stores
it's value. I figured that this is all we really needed to do so I stopped
there. It does handle commutivity however.
