#define ELMIMINATED = -1
 * 1. Look-back methods are used in Parserr. This can be 

class Parser {
private:
    Patch patch;
    FileChange * cur_file;
    int cur_ori_num;
    int cur_fin_num;
    string commit_hash;
    void deal_with_one_line(int ident_id, char * st);
    bool hit_identifier(char * op_buffer, int & ident_id);
    string Parser_patch_git_info(string str);
public:
};

Parser::Parser(string commit_hash) {
    this -> cur_ori_num = 0;
    this -> cur_fin_num = 0;
    this -> commit_hash = commit_hash;
}

void Parser::deal_with_one_line(int ident_id, char * st){
        case 0:         // +
            LineChange l = {this->cur_file->orig_dir, this->cur_file->final_dir, 
                        cur_ori_num, cur_fin_num, (string)st, this->commit_hash};
            (*(patch.file_changes.end())).linechanges.push_back(l);
            break;
        case 1:         // -  
        case 3:         // +++
            break;
        case 4:         // ---
            break;
        case 6:         // normal lines
            break;
        case 7:         // @@

            break;
bool Parser::hit_identifier(char * op_buffer, int & ident_id) {
string Parser::Parser_patch_git_info(string str) {
    int ptr = 0;
