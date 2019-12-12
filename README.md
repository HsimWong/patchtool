# patchtool
## Prerequisite

Here I will simply list the packages on which the tool is implemented. It should be working fine with similar environment

**OS**: Linux

**Interpreter**: 3.6.8

**Version Controller**: git 2.18.1

**Compiler**: gcc-8.3.1

**Kernel**: 4.18.0-128.el8.x86_64

## Installation
### Install via pip
```
pip install patchtool
```

## How to use
```
usage: patchtool [-h] -d D -p P [-s]

optional arguments:
  -h, --help  show this help message and exit
  -d D        The directory where this patch tool is hoped to be used
  -p P        Directory of the patch file
  -s S        The style in which you would like the updated file to be output

```
The patchtool provides with two modes where you can choose either to let the tool verify if the code in patch still exists and unmodified, or just do not check their validity, and output the line-number-modified patches. To verify the code, add ```-s verify``` after the command, and the output will tell you at the command whether each commit is verified. As the excecution finishes, two files will be generated with verified and unverified separately in each file.

An ordinary usage goes like this:
```
patchtool -d [git_directory] -p [patchfile_path]
```
Directly output the updated line number to the terminal.
```
patchtool -d [git_directory] -p [patchfile_path] -s verify

```
This will generate three files:
1. <oriFileName>.unverified.patch: patches that has the possibility where there might be discrepancies from the reality and what the updated-patch shows
2. <oriFileName>.verified.patch: patches showing the codes that are identical to the real code
3. verification_info.log: a file showing the results of verification

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


