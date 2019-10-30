import PatchMgr
import Fake
import argparse
import os
import re
import sys
import test

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', type=str, required=True,
                        help='The directory where this patch tool is hoped to be used')
    parser.add_argument('-p', type=str, required=True,
                        help="Directory of the patch file")
    parser.add_argument('-s', type=str, required=False,
                        help="The style you would like the updated file to be output" )           
    args = parser.parse_args()
    curr_dir = os.popen("pwd").read() + '/'
    '''
    Geting absolute directory of git repo and 
    pat_dir in order to avoid chaos.
    '''
    pat_dir = str(args.p)
    git_repo = str(args.d)
    style = str(args.s)

    if not style in ['verify', "None"]:
        print("The option should be \'verify\' or dropped")
        exit()
    log_dir = pat_dir + '.log'
    pat_dir = pat_dir if pat_dir[0] == '/' else curr_dir[:-2] + '/' + pat_dir
    git_repo = git_repo if git_repo[0] == '/' else curr_dir[:-2] + '/' + git_repo
    old_patch_str = ""
    with open(str(pat_dir), 'r') as f:
        old_patch_str = f.read()
    patches_array = re.split(r"-- \n[0-9,\.]*\n*", old_patch_str)
    file_count = 0
    fv = open("verification_info.log", 'w+')
    usable_patches = ""
    unveri_patches = ""
    all_patches = ""
    for raw_patch in patches_array:
        if len(raw_patch) == 0:
            break 
        file_count += 1
        patch_head_ind = re.search(" [0-9]* file(s)? changed, [0-9]* " + \
                                   "(insertion(s)?\(\+\)|deletion(s)?\(\-\))" + \
                                   "(, [0-9]* deletion(s)?\(\-\))?\n" + \
                                   "(( create\s[\s\S]*\n\n)*)?", raw_patch).span()[1]
        patch_head = raw_patch[:patch_head_ind]
        patch_body = raw_patch[patch_head_ind+2:]
        patch_hash = patch_head[5:20]
        mgr_bug = PatchMgr.PatchMgr(patch_body)
        file_name_list = [file_change['new_dir'] for file_change in mgr_bug.file_changes]
        cmd_get_git = "cd %s && git diff %s "%(git_repo, patch_hash)
        git_info_now = ""
        for fileName in file_name_list:
            cmd = "cd %s && git diff %s %s"%\
                (git_repo, patch_hash, fileName)
            git_info = os.popen(cmd).read()
            
            if git_info is None:
                sys.stderr.write(fileName)
                continue 
            else:
                git_info_now += '\n' + git_info 
        mgr_now = PatchMgr.PatchMgr(git_info_now)
        new_info = '\nd' + Fake.getFakeInfo(mgr_bug, mgr_now)[12:]
        out_str = patch_head + new_info
        test_info, test_status = test.testify(git_repo, new_info, patch_hash)
        if len(test_info) == 0:
            test_info = "The patch generated for commit %s is correct. \n" % patch_hash
        fv.write(test_info)
        if style == "verify":
            print(test_info, end = "")
        all_patches += out_str
        if test_status:
            usable_patches += out_str
        else:
            unveri_patches += out_str
    if style == "verify":
        with open(pat_dir + '.verified.patch', 'w+') as f:
            f.write(usable_patches)
        with open(pat_dir + '.unverified.patch', 'w+') as f:
            f.write(unveri_patches)
    else:
        print(all_patches)
    fv.close()
    

main()
