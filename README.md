# VirtualMachine

This project works on the command line as requested by the professor of the capstone class. Run the vm.exe file and add proj4.asm. The proj4.asm file is the assembly language file that runs a Fibonacci Function on multiple threads. Here are the instructions:     

1. Recursive Fibonacci Function Test     
Implement a recursive Fibonacci function by using a run-time stack to both pass parameters and return a result. You must place an activation record on a run-time stack! Repeatedly compute and printout the Fibonacci value for an integer entered from the keyboard. The key to stop computing values is when the value 0 is entered. Output MUST look like:
Fibonacci of X is Y
Where X is the value entered and Y is the computed Fibonacci value.     
2. Addressing Mode Test     
Create an array with space for 30 integer values. Each time an integer is entered for the recursive Fibonacci function above place it (the X value) into the array (start at the beginning location). Place the of the value (the Y value) into the array at the next available position (X1,Y1,X2,Y2,X3,Y3,…,Xn ≤ 30,Yn ≤ 30). When the value of 0 is entered print the integers that were entered into the array as follows, (CNT is the next free location in the array).
Array[0], Array[CNT-1], Array[1], Array[CNT-2], …, Array[CNT-(CNT/2 +1)], Array[CNT- (CNT/2)]
3. Multi-Threaded VM     
Implement a multi-Threading architecture for your VM using the following instructions. Note, this is a simplified multi-Threading (not complete) architecture.
- RUN REG, LABEL
Run signals to the VM to create a new thread.
REG will return a unique thread identifier (number) that will be associated with the thread. The register is to be set by your VM, not by the programmer calling the RUN instruction. You can determine what action to perform if all available identifiers are in use (throwing an exception is fine). Running out of identifiers means you have created two many threads and are out of Stack
Space.
The LABEL will be jumped to by the newly created thread. The current thread will continue execution at the statement following the RUN.
- END
End will terminate the execution of a non-MAIN thread. In functionality END is very similar to TRP 0, but only for a non-MAIN threads. END should only be used for non-MAIN threads. END will have no effect if called in the MAIN Thread.
- BLK
Block will cause the MAIN thread (the initial thread created when you start executing your program) to wait for all other threads to terminate (END) before continuing to the next instruction following the block. Block is only to be used on the MAIN thread. BLK will have no effect if called in a Thread which is not the MAIN thread.
- LCK LABEL
Lock will be used to implement a blocking mutex lock. Calling lock will cause a Thread to try to place a lock on the mutex identified by Label. If the mutex is locked the Thread will block until the mutex is unlocked. The data type for the Label is .INT
- ULK LABEL
Unlock will remove the lock from a mutex. Unlock should have no effect on a mutex if the Thread did not lock the mutex (a.k.a., only the Thread that locks a mutex should unlock the mutex). Once you implemented the new instructions create the following test code to CLEARLY shows that your multi-threading architecture works by reusing the code from parts 1 and 2 above to call your Fibonacci function on multiple Threads (you must have at least 4 threads plus the main thread).
