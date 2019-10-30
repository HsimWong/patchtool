import PatchMgr

def testify(git_repo, out_str, commit_hash):
    status = True
    file_mgr = PatchMgr.PatchMgr(out_str).file_changes[0]
    
    with open(git_repo + '/' + file_mgr['new_dir']) as f:
        file_text = f.readlines()
    verify_str = ""
    for modif in file_mgr['modifs']:
        check_line = modif['lines'][0]
        check_num = modif['new_start']
        fake_cont = modif['lines'][0]['content'].strip()
        real_cont = file_text[check_num - 1].strip()
        if not fake_cont == real_cont:
            status = False
            verify_str += "Commit %s: Line %d at file %s might be incorrect.\n" \
                % (commit_hash, check_num, file_mgr['new_dir'])
    return verify_str, status
    
