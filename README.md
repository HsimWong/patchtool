-s          output style, [patch] for patch style, while [comp] for
              comparison style

python3 main.py -d [directory] -b [bugHash] -n [displayHash] -s [style]
A normal comparison output will be:


A normal patch output will be:
```
diff --git a/README.md b/README.md
new file mode 100644
index 0000000..d3a28e9
--- /dev/null
+++ b/README.md
@@ -0,0 +1,53 @@
+# patchtool
+## Prerequisite
+
+Here I will simply list the packages on which the tool is implemented. It should be working fine with similar environment
+
+**OS**: Ubuntu 19.04
+
+**Interpreter**: 3.7.3
+
+**Version Controller**: git 2.20.1
+
+**Compiler**: gcc-8.3.0
+
+**Kernel**: 5.0.0-21
+
+## How to use
+
+--h, --help   show this help message and exit
...
```