import re
import Fake

'''
fc = {
    "ori_dir":str, "new_dir":str,
    "modifs":{modif}, "head_str":str
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


class PatchMgr(object):
    def __init__(self, git_body):
        self.git_body = git_body
        self.file_changes = []
        self.parse()

    def parse(self):
        file_git_array = re.split(r'diff --git ', self.git_body)
        # print(len(file_git_array))
        for file_git in file_git_array:
            if len(file_git) < 10:
                continue
            self.file_changes.append(self.make_file(file_git))
        # print(self.file_changes)

    def make_modi(self, modi_git):
        # print(modi_git)
        raw_lines = modi_git.split('\n')
        # print(raw_lines[0])
        # print(lines[1])
        # print(lines[2])

        int_raw = re.findall('[0-9]*', raw_lines[0])
        # print(raw_lines[0])
        # print(int_raw)
        # print(sum([int(x) for x in int_raw]))
        # if int_raw[1] == "":
        #     ori_start = int(int_raw[1])
        #     ori_offst = int(int_raw[3])
        #     new_start = int(int_raw[6])
        #     new_offst = int(int_raw[8])
        # else:  
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
            typ = ""
            if len(raw_line) == 0:
                continue
            if raw_line[0] == '+':
                cur_off_new += 1
                typ = "addition"
            elif raw_line[0] == '-':
                cur_off_old += 1
                typ = "deletion"
            elif raw_line[0] == ' ':
                cur_off_new += 1
                cur_off_old += 1
                typ = "unmodified"
            else:
                continue
            apd = {"ori_line_num": ori_start + cur_off_old,
                   "new_line_num": new_start + cur_off_new,
                   "type": typ, "content": raw_line}
            lines.append(apd)
            # print(apd)
        # print("yes")

        return {
            "ori_start": ori_start, "ori_offset": ori_offst,
            "new_start": new_start, "new_offset": new_offst,
            "func_name": raw_lines[0][raw_lines[0].find("@@") + 3:],
            "lines": lines
        }

    def make_file(self, file_git):
        file_head = ""
        split_lines = file_git.split('\n')
        for line in file_git.split('\n')[0:4]:
            file_head += line + '\n'
        # print(split_lines[0])

        ori_dir = split_lines[0][2:split_lines[0].find(" b/")]
        # print(ori_dir)
        new_dir = split_lines[0][split_lines[0].find(" b/") + 3:]

        file_body = file_git[file_git.find("@@") + 3:]

        modi_gits = file_body.split("\n@@ ")
        # print(len(modi_gits))
        # print((modi_gits[0]))
        modifs = []
        if not (len(split_lines) < 5):
            # print(split_lines[5])
            # print(modi_gits)
            try:
                for modi in modi_gits:
                    # print(modi)
                    # print("_________________________________")
                    # print(modi)
                    # if len(modi.split('\n')) <= 4:
                    #     break
                    modifs.append(self.make_modi(modi))
            except ValueError:
                pass

        return {"ori_dir": ori_dir, "new_dir": new_dir,
                "modifs": modifs, "head_str": file_head}


if __name__ == "__main__":
    file_git = ""
    add_git = ""
    with open("./sample_new.txt") as f:
        add_git = f.read()
    with open("./sample_bug.txt") as f:
        file_git = f.read()

    a = PatchMgr(file_git)
    b = PatchMgr(add_git)
    out_str = (Fake.getFakeInfo(a, b))
    print(out_str)
