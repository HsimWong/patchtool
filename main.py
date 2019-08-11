import patchtool
import display_patch as dp
import argparse
import os




parser = argparse.ArgumentParser()                                              
parser.add_argument('-b', type=str, required=True, \
        help='commit before bug: The commit hash or version where the bug \
            is discovered')
parser.add_argument('-n', type=str, required=True, \
        help='Check commit: The commit hash or version where the bug is \
            fixed')
parser.add_argument('-d', type=str, required=True, \
        help='git repository directory')

args = parser.parse_args()                                                      
bug_commit_hash = str(args.n)                                                   
ori_commit_hash = str(args.b)                                                   
#print(ori_commit_hash)                                                         
#print(bug_commit_hash)                                                         
repo_dir = str(args.d)                                                          
git_info_old = os.popen("cd %s && git diff %s %s"%\
        (repo_dir, ori_commit_hash, bug_commit_hash)).read()
git_info_now = os.popen("cd %s && git diff %s"%\
        (repo_dir, bug_commit_hash)).read()
# old_parser = patchtool.Parser(git_info_old)
now_parser = dp.OriParser(git_info_old, git_info_now)
print(now_parser.out_str)
 
