COEN 177 - Operating Systems
====================

## Lab One
Part One: Basic Programming Task (up to 20 points)

The goal of this assignment is to make sure you fully comprehend (and are able to realize) the creation of processes with Unix-like operating systems. To this end you will be using the fork() system call.

You are to write a very simple shell program, similar to the example covered in lecture. The shell should terminate if the user enters “exit” at the command line, and should attempt to launch a program in response to any other input string. You do not have to parse any parameters, nor do you need to support background execution of processes. The simplest possible shell to demonstrate is all that is required. You may wish to write a “hello world” program, so that you have an executable file that you could launch from your shell.

Part Two: The Second Programming Task (up to 10 additional points):

You are to write a program that will create exactly eight child processes (including the initial program itself). You are not to allow any single process to create more than two child processes.

Part Three: The Third Programming Task (up to an additional 20 points)

You are to write a program that, when launched, will result in a total of twelve child processes to run. This is the same task as described above, but this time you are not to allow any single process which creates children to create less than two child processes, or more than three. In other words, the program you write can only launch a maximum of three child processes directly, and any other “children” will have to be created by the children of this parent process (subject to the restriction of only creating two or three processes each). Once again, any process that creates other processes must create either two or three processes only, no more and no less.

Part Four: The Fourth Programming Task (up to an additional 20 points)

You are to write a program that, when launched, will result in a total of sixteen child processes to run. This is the same task as described above, again this time you are not to allow any single process which creates children to create less than two child processes, or more than three. In other words, the program you write can only launch a maximum of three child processes directly, and any other “children” will have to be created by the children of this parent process (subject to the restriction of only creating two or three processes each). Once again, any process that creates other processes must create either two or three processes only, no more and no less.

## Lab Three

The Basics

The goal of this assignment is to gain experience with page replacement (and to a lesser extent, caching) algorithms. In this assignment your goal is to write programs that simulate page replacement algorithms. Your initial program is to accept at least one numeric command-line parameter, which it will use as the number of available page frames. 
For example:
 ./lru 7

should run a simulation of the LRU page replacement algorithm for a memory/cache size of 7 pages/blocks. But whence will page requests come? The answer is that your program should expect page requests to arrive on standard input (stdin, so a basic fgets(), or scanf(), call should suffice to read in the unsigned integer page numbers being requested). So assuming you have a sequence of page numbers in a text file called "accesses.txt" you should be able to run your simulator by typing:

$cat accesses.txt | lru 42

The output of your program will be every page number that was not found to be in the cache. In other words, the output of your program will be a sequence of page numbers that represents all the incoming requests that resulted in a page fault. Using your program, you should be able to get two numbers from the unix command line (by counting the number of lines read from the input file, and the number of lines produced by your simulator). The first of these numbers is the total number of page/block requests your simulator program has received (you get this by counting the number of valid lines in your input file), and the second number is how many of these page requests did result in a page fault (you get this by counting the number of lines produced as output by your program - which is faithfully reproducing the page replacement algorithm's behavior).

Your programs are to accept page requests on stdin as individual numbers, one per line, where each number indicates the requested page number. Each program is to further ignore any trailing text on the input lines, or any lines that do not start with a number. Your program terminates its simulation when it encounters an end-of-file. Once again, the size of the memory being managed by your program (the number of page frames, or the size of the cache if you treat this as a caching algorithm) is to be accepted as a command-line argument to your program. Any status output (e.g., messages you wish to print for debugging/user) should be sent to stderr (standard error, in other words, it should be possible to use your program and see nothing in standard output other than the page-faults/cache-misses, by redirecting only stdout).

You are to provide a program for each of the following replacement algorithms: Second-Chance, LRU, LFU, and a fourth algorithm of your choosing (but not FIFO).

Note that for LFU, if two pages have been requested an equal number of times, ties should be broken by ejecting whichever page was requested least recently.
