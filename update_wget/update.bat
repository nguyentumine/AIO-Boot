@echo off
mode 100,4
curl -sL https://api.github.com/repos/nguyentumine/AIO-Boot/releases/latest > curl.json
curl -sL https://api.github.com/repos/nguyentumine/AIO-Boot/releases/latest | jq -r ".name" > name.txt
curl -sL https://api.github.com/repos/nguyentumine/AIO-Boot/releases/latest | jq -r ".tag_name" > version.txt
curl -sL https://api.github.com/repos/nguyentumine/AIO-Boot/releases/latest | jq -r ".assets[].browser_download_url" > url.txt
wget -q -O AIOBoot.7z --show-progress -i url.txt
7zG.exe  x -y -o"..\" -paioboot AIOBoot*.7z
