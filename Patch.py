import pygit2 as git

# class Modification:
#     file_dir = ""
#     line_num = None
#     next_line = None 

# # One line of modification: 
class Patch:
    def __init__(self, repo_dir, commit_hash):
        self.repo_dir = repo_dir
        self.repo = git.Repository(repo_dir)
        # self.patch_info = self.repo.get(commit_hash)
        print(self.repo.blame("sample.txt").for_line(3))




if __name__ == "__main__":
    patch = Patch(repo_dir = "/home/xwan/patch_working_dir/test", 
                  commit_hash = "cda6611ca63d117075b1816de7bae4bdd64b1050")
    
    
# import pygit2 as git 
# repo = git.Repository("/home/xwan/patch_working_dir/test")

