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
    # pat_dir = "./patch-list1"
    # git_repo = "/home/xwan/debug/libvirt-rhel"
    old_patch_str = ""
    with open(str(pat_dir), "r") as f:
        old_patch_str = f.read()
    # print("Start parsing each commit......")
    patches_array = re.split(r"-- \n[0-9,\.]*\n*", old_patch_str)

    # for raw_patch in patches_array:
    file_count = 0
    # raw_patch = patches_array[0]
    for raw_patch in patches_array:
        # print(len(raw_patch))
        # print("Working on file %d"%file_count)
        if len(raw_patch) == 0:
            break 
        file_count += 1
        patch_head_ind = re.search(" [0-9]* file(s)? changed, [0-9]"
                                    + r"* (insertions\(\+\)|deletions\(\-\))"
                                    + r"(, [0-9]* deletions\(\-\))?"
                                    , raw_patch).span()[1]
        patch_head = raw_patch[:patch_head_ind]
        patch_body = raw_patch[patch_head_ind+2:]
        patch_hash = patch_head[5:20]
        # print("Got the commit hash......")
        git_info_now = os.popen("cd %s && git diff %s"%
                                (git_repo, patch_hash)).read()
        # print("Got git-diff info from the commit to now version......")
        # print(git_info_now[0:100])
        mgr_bug = PatchMgr.PatchMgr(patch_body)
        # print("Generated bug patch mgr")
        mgr_now = PatchMgr.PatchMgr(git_info_now)
        # print("Generated now patch mgr")
        out_str = patch_head + Fake.getFakeInfo(mgr_bug, mgr_now)
        
        print(out_str)

