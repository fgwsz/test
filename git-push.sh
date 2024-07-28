#!/bin/bash
echo "You Can Input q For Abort."
read -p "Input Git Commit Info: " commit_info
if [ "$commit_info" != "q" ]; then
    git add ./include/*
    git add ./src/*
    git add ./tests/*
    git add ./CMakeLists.txt
    git add ./LICENSE
    git add ./README.md
    git add ./.gitignore
    git add ./*.ps1
    git add ./*.sh
    git commit -m "$commit_info"
    git push
fi
