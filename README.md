# Operating-Systems---Scheduling-System-Calls
Xv6 operating system - System calls and Scheduling policies implementation 

Assignment specifications: https://www.cs.bgu.ac.il/~os172/wiki.files/Assignment1.pdf

Support of Path environment variable.
System calls wait and exit implementation.
Processes scheduling policies implementation.

Running the project:
If already patched:
* git clone http://www.cs.bgu.ac.il/~os172/git/Assignment1
* make
* make clean qemu
* Shell is opened, can run programs within xv6 (sanity program for testing).

If not already patched:
* git clone http://www.cs.bgu.ac.il/~os172/git/Assignment1
* git apply 203695067_203751920.patch
* make
* make clean qemu
* Shell is opened, can run programs within xv6 (sanity program for testing).
