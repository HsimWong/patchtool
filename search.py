import PatchMgr
import re


def get_phrase_num(file_lines, phrase):
    ret = 0
    return ret 

def get_line_num(file_dir, phrases):
    line_nums = [-2 for i in range(len(phrases))]
    file_lines = []
    with open(file_dir, 'r') as f:
        file_lines = f.read().split('\n')

    for i in range(len(phrases)):
        line_nums[i] = get_phrase_num(file_lines, phrases[i])
    return line_nums

