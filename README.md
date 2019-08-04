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

  -d          git directory *[not yet modified, wait until i get to the office]*

  -b          Bug commit: The commit hash or version where the bug is solved.
  
  -n          Check commit: The commit hash or version where the bug commit is
              displayed.

An ordinary usage goes like this:
```
python3 patchtool.py -d [directory] -b [bugHash] -n [displayHash]
```

