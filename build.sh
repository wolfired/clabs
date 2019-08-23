if [ '-h' == "$1" ] || [ '--help' == "$1" ]; then
    echo "Usage:"
    echo "  [options] ./build.sh"
    echo ""
    echo "Options:"
    echo "  clean=1"
    echo "      Clean and Build"
    echo "  run=?"
    echo "      Build an Run"
    echo "      ? = test_trace | test_file | test_qjs"
    echo "  qjs_version=?"
    echo "      ? default is \"quickjs-2019-08-18\""
    exit 0
fi

CWD=`pwd`

WORKSPACE_GIT=~/workspace_git
WORKSPACE_LABS=~/workspace_labs

GOLABS_PATH=$WORKSPACE_GIT/golabs

QJS_VERSION=${qjs_version:-"quickjs-2019-08-18"}
QJS_PATH=$WORKSPACE_LABS/$QJS_VERSION

#编译Quickjs
function build_qjs() {
    cd $WORKSPACE_LABS
    if [ ! -d "$QJS_PATH" ]; then
        wget https://bellard.org/quickjs/$QJS_VERSION.tar.xz
        tar -xJvf $QJS_VERSION.tar.xz

        qjs_go="$GOLABS_PATH/go2clabs/qjs.go"
        if [ -f "$qjs_go" ]; then
            sed -i "s/quickjs-[0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}/$QJS_VERSION/g" $qjs_go
        fi
    fi
    cd `find . -maxdepth 1 -type d -name quickjs-\*`
    sed -i 's/CONFIG_M32=y/CONFIG_M32=/g' Makefile
    make libquickjs.a
    cd $CWD
}
build_qjs

if [ -n "$clean" ]; then rm -rf out; fi \
&& mkdir -p out \
&& cd out \
&& cmake -DQJS_PATH=$QJS_PATH -DCMAKE_BUILD_TYPE=Debug .. \
&& make \
&& if [ -n "$run" ]; then $CWD/bin/$run; fi
