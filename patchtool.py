'''
LineChange = (
    string ori_file_dir;
    string final_dir;
    int inserted_line_num;      

   1 ori        +1 ist
   2 ori        +1 ist
                 1 ori
                +2 ist
                 2 ori


    int result_line_num;
    int if_inserted;            // INSERTED: 1, DELETED: -1, UNMODIFIED: 0
    string line_content;
)     (tuple)

struct FileChange{
    string orig_dir;
    string final_dir;
    LineChange (linechanges); (List of tuple)
};

struct Patch {
    string commit_hash;
    Listfile_changes;         (List of List)
};
'''
import os
now_commit_hash = ""
bug_commit_hash = ""

# from pygit2 import Repository as rp 
INFINITY = 65535

# repo = rp('./.git')
# patches = [p for p in repo.diff( bug_commit_hash, now_commit_hash)]

class Parser:
    def __init__(self, git_diff_string):
        print("Parser initializing")
        self.cur_ori_num = 1
        self.cur_fin_num = 1
        self.file_changes = []
        self.parse_patch_git_info(git_diff_string)

    def parse_patch_git_info(self, diff_str):
        str_lines = diff_str.split('\n')
        for line in str_lines:
            self.deal_with_one_line(line)

    def deal_with_one_line(self,line):
        # print(line)
        operator, content = self.parse_line(line)
        if operator == 1:   # ---
            file_change = [content, "", []]
            self.file_changes.append(file_change)
        elif operator == 0: # +++
            self.file_changes[-1][1] = content
        elif operator == 2: # +
            line_change = (self.file_changes[-1][0],self.file_changes[-1][1], self.cur_ori_num, self.cur_fin_num, 1, content)
            # line_change = (cur_ori_num, cur_fin_num, 1, content)
            self.file_changes[-1][2].append(line_change)
            self.cur_fin_num += 1
        elif operator == 3:  # -
            line_change = (self.file_changes[-1][0],self.file_changes[-1][1], self.cur_ori_num, self.cur_fin_num, -1, content)
            # line_change = (cur_ori_num, cur_fin_num, -1, content)
            self.file_changes[-1][2].append(line_change)
            self.cur_ori_num += 1
        elif operator == 4:  # ' '
            line_change = (self.file_changes[-1][0],self.file_changes[-1][1], self.cur_ori_num, self.cur_fin_num, 0, content)
            # line_change = (cur_ori_num, cur_fin_num, 0, content)
            self.file_changes[-1][2].append(line_change)
            self.cur_ori_num += 1
            self.cur_fin_num += 1
        elif operator == 5:  # @@
            ori_num, mod_num = self.parse_line_num(line)
            # ori_num = 1 if ori_num == 0 else ori_num
            self.cur_ori_num = ori_num
            self.cur_fin_num = mod_num
        else:
            return
        return
    
    def parse_line(self, line):
        # print(line)
        if len(line) == 0:
            return INFINITY, line
        if line[0:3] == '+++':
            return 0, line[4:]
        elif line[0] == '+':
            return 2, line[1:]
        elif line[0:3] == '---':
            return 1, line[4:]
        elif line[0] == '-':
            return 3, line[1:]
        elif line[0] == ' ':
            return 4, line[1:]
        elif line[0] == '@':
            return 5, line 
        else:
            return INFINITY, line 
    

    def absorb_int(self,string):
        num = ""
        for char in string:
            if char.isdigit():
                num += char 
            else:
                break
        return int(num)

    def parse_line_num(self, line):
        # print(line)
        ori_num = self.absorb_int(line[line.find('-')+1:])
        mod_num = self.absorb_int(line[line.find('+')+1:])
        # mod_num = int(line[plus_ind:comma_ind])
        return ori_num, mod_num


    
def if_dir_match(dir_1, dir_2):
    return (dir_1[1:] == dir_2[1:])




def get_new_line_num(line, parse_now):
    disp_num = line[3]
    for file in parse_now.file_changes:
        if if_dir_match(file[0], line[1]):
            for now_line in file[2]:
                if now_line[2] < line[3]:
                    disp_num += now_line[4]
    return disp_num

def display(pat_str_bug, pat_str_now):
    # print("enterd")
    patch_bug = Parser(pat_str_bug)
    patch_now = Parser(pat_str_now)
    for file in patch_bug.file_changes:
        print("File dir when un-debugged:\t%s\n"%(file[0]))
        print("File dir after debugged:\t%s\n"%(file[1]))
        if_modified = False
        for file_now in patch_now.file_changes:
            if if_dir_match(file_now[0], file[1]):
                if_modified = True
                print("File dir right now:\t\t%s"%file_now[1])
        if not if_modified:        
            print("File dir right now:\t\t%s"%file[1])
        for line in file[2]:
            print("%d\t%d\t%d\t%s"%(line[2], line[3], get_new_line_num(line, patch_now), line[5]))

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-b', type=str, required=True,help='Bug commit: The commit hash or version where the bug is solved.')
parser.add_argument('-n', type=str, required=True,help='Check commit: The commit hash or version where the bug commit is displayed.')
args = parser.parse_args()
bug_commit_hash = str(args.b)
now_commit_hash = str(args.n)


git_info_old = os.popen("git diff %s"%bug_commit_hash).read()
git_info_now = os.popen("git diff %s %s"%(bug_commit_hash, now_commit_hash)).read()
display(git_info_old,git_info_now)