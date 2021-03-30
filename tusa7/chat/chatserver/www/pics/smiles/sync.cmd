@echo Forum FULL SYNC
rsync -rvltz -e "ssh -l parf" . ded:/www/forum/phpBB/images/smiles