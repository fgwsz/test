#!/bin/bash
echo "You Can Input q For Abort."
read -p "Input Git Commit Info: " commit_info
if [ "$commit_info" != "q" ]; then
    git add -f bin/.gitkeep
    git add -f build/.gitkeep
    git add -f vendor/.gitkeep
    git add -f releases/.gitkeep
    git add include/*
    git add src/*
    git add tests/*
    git add res/*
    git add docs/*
    git add CMakeLists.txt
    git add LICENSE
    git add README.md
    git add .gitignore
    git add git-push.ps1
    git add git-push.sh
    git add git-keep.ps1
    git add build*.ps1
    git add build*.sh
    git add clean.ps1
    git add clean.sh
    git commit -m "$commit_info"
    git push
fi
