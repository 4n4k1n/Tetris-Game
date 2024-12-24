#! /bin/bash

org_dir=$PWD

cd ~/

chmod 777 .bashrc
chmod 777 .zshrc

echo "alias tetris='cd "$org_dir" && make clean && make && ./tetris'" >> ~/.bash_aliases
echo "alias tetris='cd "$org_dir" && make clean && make && ./tetris'" >> ~/.zshrc

cd $org_dir