## Get Isolated Python Runtime (If Needed)
```sh
wget -qO - https://ghproxy.com/https://raw.githubusercontent.com/innerNULL/pypack/main/pypack.sh | bash /dev/stdin pypack.json
cd _pypack_out && mkdir _pyenv && cd _pyenv && tar -xvzf ../pyenv.tar.gz && cd ../../
ln -s ./_pypack_out/_pyenv/bin/python ./python
```
