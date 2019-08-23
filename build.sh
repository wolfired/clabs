if [ '-h' == "$1" ] || [ '--help' == "$1" ]; then
    echo "Usage:"
    echo "  [options] ./build.sh"
    echo ""
    echo "Options:"
    echo "  clean=?"
    echo "      Clean and Build"
    echo "      ? = true | false, skip is false"
    echo "  run=?"
    echo "      Build an Run"
    echo "      ? = test_trace | test_file | test_qjs"
    echo "  type=?"
    echo "      ? = Debug | Release, skip is Debug"
    echo "  qjs_version=?"
    echo "      ? default is \"quickjs-2019-08-18\""
    echo "  qjs_make_target=?"
    echo "      ? default is \"libquickjs.a\""
    echo "  x264_git_url=?"
    echo "      ? default is \"git@code.videolan.org:wolfired/x264.git\""
    echo "  x264_config=?"
    echo "      ? default is \"--disable-asm\""
    echo "  x264_reconfig=?"
    echo "      ? = true | false, skip is false"
    echo "  x264_make_target=?"
    echo "      ? default is \"libx264.a cli\""
    exit 0
fi

CWD=`pwd`

CLABS_CLEAN=${clean:-"false"}
CLABS_RUN=${run:-""}
CLABS_BUILD_TYPE=${type:-"Debug"}

WORKSPACE_GIT=~/workspace_git
WORKSPACE_LABS=~/workspace_labs

GOLABS_PATH=$WORKSPACE_GIT/golabs

QJS_VERSION=${qjs_version:-"quickjs-2019-08-18"}
QJS_MAKE_TARGET=${qjs_make_target:-"libquickjs.a"}
QJS_PATH=$WORKSPACE_LABS/$QJS_VERSION

X264_GIT_URL=${x264_git_url:-"git@code.videolan.org:wolfired/x264.git"}
X264_CONFIG=${x264_config:-"--disable-asm"}
X264_RECONFIG=${x264_reconfig:-"false"}
X264_MAKE_TARGET=${x264_make_target:-"libx264.a cli"}
X264_PATH=$WORKSPACE_GIT/x264

# Build Quickjs
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
    make $QJS_MAKE_TARGET
}
build_qjs

# Build x264
function build_x264() {
    cd $WORKSPACE_GIT
    if [ ! -d "$X264_PATH" ]; then
        git clone $X264_GIT_URL
        X264_RECONFIG=true
    fi
    cd $X264_PATH
    if [ "true" = "$X264_RECONFIG" ]; then ./configure $X264_CONFIG; fi
    make $X264_MAKE_TARGET
}
build_x264

# Build clabs
function build_clabs() {
    cd $CWD
    if [ "true" = "$CLABS_CLEAN" ]; then rm -rf out; fi
    mkdir -p out
    cd out
    cmake -DQJS_PATH=$QJS_PATH -DX264_PATH=$X264_PATH -DCMAKE_BUILD_TYPE=$CLABS_BUILD_TYPE ..
    make
    if [ -n "$CLABS_RUN" ]; then $CWD/bin/$CLABS_RUN; fi
}
build_clabs
