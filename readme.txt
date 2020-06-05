COM S 352
Project # 1
Jooseung Song
shear.cpp

shear.cpp
-Added rowsort, rowrevsort, colsort, shear_sort_thread and shear_sort
this reads 2d array input from text file and sort it using multiple threads
It prints the same result in any possible case. Tested multiple nxn arrays.
Printed same result in any thread running order.
	rowsort, rowrevsort, colsort
	-separated sort function into 3 direction
	shear_sort_thread
	-use conditional variable to wait until all thread run one phase each time together
	shear_sort
	-create and terminate thread, initialize conditional variable

Makefile
-"make shear" command will make file 'shear'
	command line: make shear
	command line: ./shear

input.txt
-text file with 4x4 array

input_2.txt
-text file with 5x5 array

pyrite access denied
could not test file on pyrite. Tried to access IT support, but did not respond.

15/03/2019