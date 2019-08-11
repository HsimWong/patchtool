import patchtool
INFINITY = 65535
bug_string = ""
now_string = ""


now_patches = patchtool.Parser(now_string)

class OriParser(object):
    def __init__(self, diff_string, now_parse_git_info):
        self.patches = []
        self.parser_now = patchtool.Parser(now_parse_git_info)
        self.out_str = self.parse_git_diff(diff_string)


    def parse_git_diff(self, diff_string):
        # pat_lines = []
        # line_indicator = "" # @@ -， +， @@
        # headers = []
        # patch = [headers, ]
        output_str = ""
        curr_ori_dir = ""
        curr_mod_dir = ""
        for line in diff_string.split("\n"):
            operator, content = self.parse_line(line)
            if operator == 0: # +,-,' ',
                # pat_lines.append(operator + content)
                output_str += line
                #continue 
            elif operator == 1: # @@
                line_indicator = self.get_new_fake_line(line, \
                    self.parser_now, curr_ori_dir, curr_mod_dir)
                output_str += line_indicator
                #continue 
            elif operator == 2: # ---
                curr_ori_dir = content
                output_str += line
                #continue
            elif operator == 3:  # +++
                curr_mod_dir = content
                output_str += line 
                #continue
            else:
                output_str += line 
            output_str += '\n'
                
        return output_str

    def parse_line(self, line):
        if len(line) == 0:
            return INFINITY, line
        if line[0:3] == '---':
            return 2, line[4:]
        elif line[0:3] == '+++':
            return 3, line[4:]
        elif line[0] in ['+', '-', ' ']:
            return 0, line[1:]
        elif line[0:1] == '@@':
            return 1, line
        else:
             return INFINITY, line
    
    def get_new_fake_line(self, line, parser, curr_ori_dir, curr_mod_dir):
        ori_start, line_buf = self.absorb_int(line[3:])
        ori_end, line_buf = self.absorb_int(line_buf[1:])
        mod_start, line_buf = self.absorb_int(line[1:])
        mod_end, line_buf = self.absorb_int(line[1:])
        now_ori_start = self.get_now_num(ori_start, curr_mod_dir)
        now_ori_end = self.get_now_num(ori_end, curr_mod_dir)
        now_mod_start = self.get_now_num(mod_start, curr_mod_dir)
        now_mod_end = self.get_now_num(mod_end, curr_mod_dir)
        line_indicator = "@@ -%d,%d +%d,%d"%\
            (now_ori_start, now_ori_end, now_mod_start, now_mod_end) + \
                line_buf
        return line_indicator
        
    def get_now_num(self, line_num, curr_mod_dir):
        disp_num = line_num
        for file_struct in self.parser_now.file_changes:
            if curr_mod_dir[1:] == file_struct[1:]:
                for now_line in file_struct[2]:
                    if now_line[2] <= line[3]:
                        disp_num += now_line[4]
        return disp_num
            

    def absorb_int(self,string):
        num = ""
        for char in string:
            if char.isdigit():
                num += char
            else:
                break
        return int(num), string[len(num):]



