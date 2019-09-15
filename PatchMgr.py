import re

# modific: a dictionary
# {""}

# Filechange:
'''
fc = {
    "ori_dir":str, "new_dir":str, "modifs":{modif}
}
modif = {
    "ori_start": int, "ori_offset": int,
    "new_start": int, "new_offset": int,
    "func_name": str, "lines": {line}
}
line = {
    "ori_line_num":int, "new_line_num":int,
    "type":{"addition", "deletion"}
}
'''

def make_modi(modi_git):
    # print(modi_git)
    raw_lines = modi_git.split('\n')
    # print(lines[0])
    # print(lines[1])
    # print(lines[2])
    
    int_raw = re.findall('[0-9]*', raw_lines[0])
    ori_start = int(int_raw[1])
    ori_offst = int(int_raw[3])
    new_start = int(int_raw[6])
    new_offst = int(int_raw[8])
    # print(ori_start, ori_offst, new_start, new_offst)
    lines = []
    cur_off_old = 0
    cur_off_new = 0
    for raw_line in raw_lines[1:]:
        # print(line)
        if len(raw_line) == 0:
            continue 
        if raw_line[0] == '+':
            cur_off_new += 1 
                         
        elif raw_line[0] == '-':
            cur_off_old += 1
        elif raw_line[0] == ' ':
            cur_off_new += 1
            cur_off_old += 1
        apd = {"ori_line_num":ori_start + cur_off_old,
         "new_line_num":new_start + cur_off_new,
         "type":"addition", "content":raw_line}
        lines.append(apd)
        print(apd)
    
    return {
        "ori_start":ori_start, "ori_offset":ori_offst,
        "new_start":new_start, "new_offset":new_offst,
        "func_name":raw_lines[0][raw_lines[0].find("@@")+3:],
        "lines":lines
    }

def make_file(file_git):
    ori_dir_span = re.search(r"\-\-\- ", file_git).span()
    new_dir_span = re.search(r'\+\+\+ ', file_git).span()
    ori_dir = file_git[ori_dir_span[1]:new_dir_span[0]][:-1]

    new_dir = file_git[new_dir_span[1]:]
    new_dir = new_dir[0:new_dir.find("@@")][:-1]
    file_body = file_git[file_git.find("@@")+3:]
    modi_gits = file_body.split("\n@@ ")
    # print((modi_gits[0]))
    modifs = []
    for modi in modi_gits:
        # print("_________________________________")
        # print(modi)
        modifs.append(make_modi(modi))
    return {"ori_dir":ori_dir, "new_dir":new_dir, "modifs":modifs}
    
        




class PatchMgr(object):
    def __init__(self, git_body):
        self.git_body = git_body
        self.file_changes = []

    def parse(self):
        file_git_array = re.split(r'\ndiff --git ', self.git_body)
        for file_git in file_git_array:
            self.file_changes.append(make_file(file_git))

if __name__ == "__main__":
    file_git = '''a/src/util/virhostdev.c b/src/util/virhostdev.c
index 6be395cdda..19ae001971 100644
--- a/src/util/virhostdev.c
+++ b/src/util/virhostdev.c
@@ -333,8 +333,7 @@ virHostdevIsPCINetDevice(virDomainHostdevDefPtr hostdev)
 {
     return hostdev->mode == VIR_DOMAIN_HOSTDEV_MODE_SUBSYS &&
         hostdev->source.subsys.type == VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_PCI &&
-        hostdev->parent.type == VIR_DOMAIN_DEVICE_NET &&
-        hostdev->parent.data.net;
+        hostdev->parentnet != NULL;
 }
 
 
@@ -427,7 +426,7 @@ virHostdevSaveNetConfig(virDomainHostdevDefPtr hostdev,
     int vf = -1;
 
     if (!virHostdevIsPCINetDevice(hostdev) ||
-        virDomainNetGetActualVirtPortProfile(hostdev->parent.data.net))
+        virDomainNetGetActualVirtPortProfile(hostdev->parentnet))
        return 0;
 
     if (virHostdevIsVirtualFunction(hostdev) != 1) {
@@ -474,8 +473,8 @@ virHostdevSetNetConfig(virDomainHostdevDefPtr hostdev,
     if (virHostdevNetDevice(hostdev, -1, &linkdev, &vf) < 0)
         return -1;
 
-    vlan = virDomainNetGetActualVlan(hostdev->parent.data.net);
-    virtPort = virDomainNetGetActualVirtPortProfile(hostdev->parent.data.net);
+    vlan = virDomainNetGetActualVlan(hostdev->parentnet);
+    virtPort = virDomainNetGetActualVirtPortProfile(hostdev->parentnet);
     if (virtPort) {
         if (vlan) {
             virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
@@ -485,11 +484,11 @@ virHostdevSetNetConfig(virDomainHostdevDefPtr hostdev,
             return -1;
         }
         if (virHostdevNetConfigVirtPortProfile(linkdev, vf, virtPort,
-                                               &hostdev->parent.data.net->mac,
+                                               &hostdev->parentnet->mac,
                                                uuid, port_profile_associate) < 0)
             return -1;
     } else {
-        if (virNetDevSetNetConfig(linkdev, vf, &hostdev->parent.data.net->mac,
+        if (virNetDevSetNetConfig(linkdev, vf, &hostdev->parentnet->mac,
                                   vlan, NULL, true) < 0)
             return -1;
     }
@@ -535,10 +534,10 @@ virHostdevRestoreNetConfig(virDomainHostdevDefPtr hostdev,
     if (virHostdevNetDevice(hostdev, 0, &linkdev, &vf) < 0)
         return -1;
 
-    virtPort = virDomainNetGetActualVirtPortProfile(hostdev->parent.data.net);
+    virtPort = virDomainNetGetActualVirtPortProfile(hostdev->parentnet);
     if (virtPort) {
         return virHostdevNetConfigVirtPortProfile(linkdev, vf, virtPort,
-                                                  &hostdev->parent.data.net->mac,
+                                                  &hostdev->parentnet->mac,
                                                   NULL,
                                                   port_profile_associate);
     } else {
'''
    (make_file(file_git))
        