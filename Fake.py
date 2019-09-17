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


def getFakeInfo(PatchMgrOri, PatchMgrNow):
    fake_body = ""
    # print()
    for bug_file in PatchMgrOri.file_changes:
        fake_body += bug_file['head_str'] + '\n'
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
                    # print(displ_modif['func_name'])
                    # print(displ_modif['new_offset'])
                    fake_body += "@@ -%d"%(displ_modif['ori_start'])\
                                + "," + str(displ_modif['ori_offset'])\
                                + " +" + str(displ_modif['new_start'])\
                                + "," + str(displ_modif['new_offset'])\
                                + " @@ " + str(displ_modif['func_name'])
                    # fake_body = fake_body + (
                    #         "@@ -{%d},{%d} +{%d},{%d} @@ \n".format(
                    #         displ_modif['ori_start'],
                    #         displ_modif['ori_offset'],
                    #         displ_modif['new_start'],
                    #         displ_modif['new_offset'],
                        
                    #     )
                    # )
                    for line in displ_modif['lines']:
                        fake_body += line['content'] + '\n'
    return fake_body
# import os
# import PatchMgr
# def getFakeInfo(patchMgrOri, bug_commit_hash, repo_dir):
#     for bug_file in patchMgrOri.file_changes:
#         git_info_now = os.popen("cd %s && git diff %s %s" % \
#             (repo_dir, bug_commit_hash, bug_file['new_dir'])).read()
#         now_file_patch = PatchMgr.PatchMgr()

