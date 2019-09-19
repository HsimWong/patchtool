import PatchMgr
import Fake
import argparse
import os
import re

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', type=str, required=True,
                        help='The directory where this patch tool is hoped to be used')
    parser.add_argument('-p', type=str, required=True,
                        help="Directory of the patch file")
    args = parser.parse_args()
    pat_dir = str(args.p)
    git_repo = str(args.d)
    old_patch_str = ""
    with open(str(pat_dir), "r") as f:
        old_patch_str = f.read()
    patches_array = re.split(r"-- \n[0-9,\.]*\n*", old_patch_str)
    file_count = 0
    for raw_patch in patches_array:
        if len(raw_patch) == 0:
            break 
        file_count += 1
        patch_head_ind = re.search(" [0-9]* file(s)? changed, [0-9]* (insertions\(\+\)|deletions\(\-\))"+\
                "(, [0-9]* deletions\(\-\))?\n?( [a-z]{1,} mode [0-9]* [0-9,A-Z,a-z,\/,\.,\-]*\n)*", raw_patch).span()[1]
        patch_head = raw_patch[:patch_head_ind]
        patch_body = raw_patch[patch_head_ind+2:]
        patch_hash = patch_head[5:20]
        git_info_now = os.popen("cd %s && git diff %s"%
                                (git_repo, patch_hash)).read()
        mgr_bug = PatchMgr.PatchMgr(patch_body)
        mgr_now = PatchMgr.PatchMgr(git_info_now)
        out_str = patch_head + '\nd' + Fake.getFakeInfo(mgr_bug, mgr_now)[12:]
        print(out_str)

