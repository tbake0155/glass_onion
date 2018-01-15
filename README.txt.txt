



*****************************************************************************************************
README

*****************************************************************************************************

There seems to be a bug on the school windows server that causes the math.h library to be unable to 
compile using codeblocks while compiling a release executable.  The program compiles fine with dedug
executables.  This is very strange to me.  It throws an error about "_hypot", where apparently there
is some compatibility issue.  I have read you can modify math.h so that "_hypot" becomes "hypot" to
solve the problem, but if you compile using the debug selection then you shouldn't have any problems.
Perhaps this should be brought to someones attention.




#####################################################################################################

*****************************************************************************************************
Percentages Changes

*****************************************************************************************************

The percentages had to be changed so that the simulation would not run infinitely.


Explanation:

Because the odds of any crack terminating is only 20%, but the odds of the crack doubling
into two cracks is 40%, the number of cracks will continuously grow in a linear fashion as 
time increases towards infinity.

Consider the example where the initial number of cracks is 5.  The odds of the simulation terminating
on turn one is about 1/32000.  The odds that the simulation will progress to the next time step
with less cracks than it has at the current time step is about 3%.  The odds of having more cracks
is about 16%.

	termination odds = 0.20^5    = 0.00032

	less crack odds = 0.20*0.6^4 = 0.02592

	more crack odds = 0.40*0.8^4 = 0.16384



In a simulation where outcomes tend to represent the statistical odds, this simulation will 
never terminate.  There is some chance that it will, so that if run an infinite number of times 
the simulation will end an infinite number of times.  However, in my finite testing the number 
of cracks quickly got to hundreds of thousands. Once at that point the odds of termination become
all but entirely impossible.

Therefore, in order to produce a simulation that creates a desirable effect, and a terminal one,
I will adjust the odds in a fashion so as to maximize the effect as best as possible.  




#####################################################################################################
