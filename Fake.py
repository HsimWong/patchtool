def getFakeNum(num, now_file):
    off_set = 0
    for modif in now_file['modifs']:
        for line in modif['lines']:
            if line['ori_line_num'] <= num:
                if line['type'] == 'addition':
                    off_set += 1
                elif line['type'] == 'deletion':
                    off_set -= 1
                else:
                    continue
    return (num + off_set)

"""fc = {"ori_dir":str, "new_dir":str, "modifs":{modif}, "head_str":str}"""


def getFakeInfo(PatchMgrOri, PatchMgrNow):
    fake_body = ""
    for bug_file in PatchMgrOri.file_changes:
        fake_body += "diff --git " + bug_file['head_str'] + '\n'
        if len(PatchMgrNow.file_changes) == 0:
            print("YES")
            PatchMgrNow.file_changes.append({"ori_dir":bug_file['ori_dir'], \
                    "modifs":[],"new_dir":bug_file['new_dir']})
        for now_file in PatchMgrNow.file_changes:
            if not bug_file['new_dir'][1:] == now_file['new_dir'][1:]:
                continue
            else:
                for modif in bug_file['modifs']:
                    
                    displ_modif = {"ori_start": None, "ori_offset": modif['ori_offset'], 
                                   "new_start": None, "new_offset": modif['new_offset'], 
                                   "func_name": modif['func_name'],"lines": modif['lines']}
                    displ_modif['ori_start'] = getFakeNum(modif['ori_start'], now_file),
                    displ_modif['new_start'] = getFakeNum(modif['new_start'], now_file)
                    fake_body += "@@ -%d"%(displ_modif['ori_start'])\
                                + "," + str(displ_modif['ori_offset'])\
                                + " +" + str(displ_modif['new_start'])\
                                + "," + str(displ_modif['new_offset'])\
                                + " @@ " + str(displ_modif['func_name']) + '\n'
                    for line in displ_modif['lines']:
                        fake_body += line['content'] + '\n'
    return '\n' + fake_body




