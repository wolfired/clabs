# clabs

编译Quickjs

```bash
SOURCE_TAR_NAME=quickjs-2019-07-09
cd ~/workspace_labs
wget https://bellard.org/quickjs/${SOURCE_TAR_NAME}.tar.xz
tar -xf ${SOURCE_TAR_NAME}.tar.xz

cd ${SOURCE_TAR_NAME}
make
```

编译CLabs

```bash
rm -rf out && mkdir out && cd out && cmake .. && make && cd ..
```
