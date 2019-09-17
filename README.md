# patchtool
## Prerequisite

Here I will simply list the packages on which the tool is implemented. It should be working fine with similar environment

**OS**: RHEL-8.1.0

**Interpreter**: 3.6.8

**Version Controller**: git 2.18.1

**Compiler**: gcc-8.3.1

**Kernel**: 4.18.0-128.el8.x86_64

## How to use
```
usage: main.py [-h] -d D -p P

optional arguments:
  -h, --help  show this help message and exit
  -d D        The directory where this patch tool is hoped to be used
  -p P        Directory of the patch file

```
An ordinary usage goes like this:
```
python3 main.py -d [git_directory] -p [patchfile]
```

## Requirements for input patch file
A standard input has a format as follow, which can be automatically generated by virtcov, a tool used for libvirt coverage test:
```
From <commit_hash> 
[headers]
<neck_information>
<body>
--
<version>
```
where ```<commit hash>``` is a hexadecimal integer generated by the submission where the bug was solved. ```[headers]``` represents header information of the commit. ```<neck_information>``` is necessary for separating header and body, with a format shown as below:
```
\s[0-9]*\sfile(s)?\schanged,\s[0-9]*\s(insertions\(\+\)|deletions\(\-\))(,\s[0-9]*\sdeletions\(\-\))?
```
The ```<body>``` part shows the diff information of the bug commit, whose format is given below:
```
diff --git a/<sorce_directory> b/<dir_after_effect>
index <hash> <operation_code>
--- a/<sorce_directory>
+++ b/<dir_after_effect>
@@ -[0-9]{1,},[0-9]{1,} +[0-9]{1,},[0-9]{1,} @@ [other_info]
...
```
which can be repeated multiple times.


