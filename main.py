import patchtool
import display_patch as dp
import argparse
import os
import re

# parser = argparse.ArgumentParser()
# parser.add_argument('-d', type=str, required=True,
#                     help='The directory where this patch tool is hoped to be used')
# parser.add_argument('-p', type=str, required=True,
#                     help="Directory of the patch file")

# args = parser.parse_args()
# pat_dir = str(args.p)
pat_dir = "./patch-list1"
git_repo = "/home/xwan/debug/libvirt-rhel"
old_patch_str = ""
with open(str(pat_dir), "r") as f:
    old_patch_str = f.read()

patches_array = re.split(r"-- \n[0-9,\.]*\n*", old_patch_str)

# for raw_patch in patches_array:
raw_patch = patches_array[0]

patch_head_ind = re.search(" [0-9]* file(s)? changed, [0-9]"
                            + r"* (insertions\(\+\)|deletions\(\-\))"
                            + r"(, [0-9]* deletions\(\-\))?"
                            , raw_patch).span()[1]
patch_head = raw_patch[:patch_head_ind]
patch_body = raw_patch[patch_head_ind+2:]
patch_hash = patch_head[5:15]

git_info_now = os.popen("cd %s && git diff %s"%
                        (git_repo, patch_hash)).read()
# old_parser = patchtool.Parser(patch_body)
now_parser = dp.OriParser(patch_body, git_info_now)
print(patch_head)
(now_parser.out_str)

    


# body = body[body.find('\n'):]
# print(body)

# args = parser.parse_args()
# bug_commit_hash = str(args.n)
# ori_commit_hash = str(args.b)
# style = str(args.s)
# # print(ori_commit_hash)
# # print(bug_commit_hash)
# repo_dir = str(args.d)
# git_info_old = os.popen("cd %s && git diff %s %s" % \
#                         (repo_dir, ori_commit_hash, bug_commit_hash)).read()
# git_info_now = os.popen("cd %s && git diff %s" % \
#                         (repo_dir, bug_commit_hash)).read()
# # old_parser = patchtool.Parser(git_info_old)
# now_parser = dp.OriParser(git_info_old, git_info_now)
# if style == 'patch':
#     print(now_parser.out_str)
# elif style == 'comp':
#     patchtool.display(git_info_old, git_info_now)
