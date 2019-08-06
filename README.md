# patchtool
## Prerequisite

Here I will simply list the packages on which the tool is implemented. It should be working fine with similar environment

**OS**: Ubuntu 19.04

**Interpreter**: 3.7.3

**Version Controller**: git 2.20.1

**Compiler**: gcc-8.3.0

**Kernel**: 5.0.0-21

## How to use

--h, --help   show this help message and exit

-d          git directory 

-b          Bug commit: The commit hash or version where the bug is solved.

-n          Check commit: The commit hash or version where the bug commit is
displayed.

An ordinary usage goes like this:
```
python3 patchtool.py -d [directory] -b [bugHash] -n [displayHash]
```
A normal output will be:
```
=============================================
File dir when un-debugged:	a/cm1.txt
File dir after debugged:	b/cm1.txt
File dir right now:		c/cm1.txt
ori	mod	now	exist	content
1	1	1	True	aaaaaaaaaaaaaaaaaaa
2	2	2	True	aaaaaaaaaaaaaaaaaaa
3	3	3	True	modification0
3	4	4	True	modification1
3	5	5	True	modification0
3	6	6	True	aaaaaaaaaaaaaaaaaaa
4	7	7	True	aaaaaaaaaaaaaaaaaa
5	8	7	False	aaaaaaaaaaaaaaaaa
6	9	10	True	aaaaaaaaaaaaaaaaaaaa
7	10	11	True	aaaaaaaaaaaaaaaaaaaa
8	11	12	True	--------------
8	12	13	True	--------------
8	13	14	True	--------------
8	14	15	True	aaaaaaaaaaaaaaa

```
## Implementation in C++
I also tried to parse the git info in c++ at the very beginning, but failed in segmentation fault
Source codes are in cpp_history dir
