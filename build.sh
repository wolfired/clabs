if [ '-h' == "$1" ] || [ '--help' == "$1" ]; then
    echo "Usage:"
    echo "  [options] ./build.sh"
    echo ""
    #
    echo "Options:"
    echo "  enable_wasm=?"
    echo "      ? = true | false, skip is false"
    echo "  enable_wasm_html=?"
    echo "      ? = true | false, skip is false"
    echo "  clean=?"
    echo "      Clean and Build"
    echo "      ? = true | false, skip is false"
    echo "  run=?"
    echo "      Build an Run"
    echo "      ? = test_clabs | test_file | test_qjs"
    echo "  type=?"
    echo "      ? = Debug | Release, skip is Debug"
    #
    echo "  qjs_version=?"
    echo "      ? default is \"quickjs-2019-08-18\""
    echo "  qjs_reconfig=?"
    echo "      ? = true | false, skip is false"
    echo "  qjs_make_target=?"
    echo "      ? default is \"libquickjs.a\""
    #
    echo "  x264_git_url=?"
    echo "      ? default is \"https://code.videolan.org/videolan/x264.git\""
    echo "  x264_config=?"
    echo "      ? default is \"--disable-asm\""
    echo "  x264_reconfig=?"
    echo "      ? = true | false, skip is false, if you change \"x264_config\", you need to set it at least one times"
    echo "  x264_make_target=?"
    echo "      ? default is \"libx264.a cli\""
    #
    echo "  ffmpeg_git_url=?"
    echo "      ? default is \"https://github.com/FFmpeg/FFmpeg.git\""
    echo "  ffmpeg_config=?"
    echo "      ? default is \"--disable-all --disable-doc --disable-asm --disable-autodetect --disable-pthreads --disable-everything --disable-iconv --enable-avcodec --enable-decoder=h264\""
    echo "  ffmpeg_config_wasm=?"
    echo "      ? default is \"--cc=emcc --cxx=em++ --ar=emar\""
    echo "  ffmpeg_reconfig=?"
    echo "      ? = true | false, skip is false, if you change \"ffmpeg_config\" or \"ffmpeg_config_wasm\", you need to set it at least one times"
    echo "  ffmpeg_make_target=?"
    echo "      ? default is \"libavcodec/libavcodec.a\""
    echo "  ffmpeg_enable_wasm=?"
    echo "      ? = true | false, skip is false"
    #
    exit 0
fi

CWD=`pwd`

CLABS_ENABLE_WASM=${enable_wasm:-"false"}
CLABS_ENABLE_WASM_HTML=${enable_wasm_html:-"false"}
CLABS_CLEAN=${clean:-"false"}
CLABS_RUN=${run:-""}
CLABS_BUILD_TYPE=${type:-"Debug"}

WORKSPACE_GIT=${workspace_git:-"~/workspace_git"}
WORKSPACE_LABS=${workspace_labs:-"~/workspace_labs"}

GOLABS_PATH=$WORKSPACE_GIT/golabs

# Build quickjs
QJS_VERSION=${qjs_version:-"quickjs-2019-08-18"}
QJS_RECONFIG=${qjs_reconfig:-"false"}
QJS_MAKE_TARGET=${qjs_make_target:-"libquickjs.a"}
QJS_PATH=$WORKSPACE_LABS/$QJS_VERSION
function build_qjs() {
    cd $WORKSPACE_LABS
    if [ ! -d "$QJS_PATH" ]; then
        wget https://bellard.org/quickjs/$QJS_VERSION.tar.xz
        tar -xJvf $QJS_VERSION.tar.xz
        QJS_RECONFIG=true
    fi

    qjs_go="$GOLABS_PATH/go2clabs/qjs.go"
    if [ -f "$qjs_go" ] && [ "true" = "$QJS_RECONFIG" ]; then
        sed -i "s/quickjs-[0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}/$QJS_VERSION/g" $qjs_go
    fi
    
    cd "$QJS_PATH"
    sed -i 's/CONFIG_M32=y/CONFIG_M32=/g' Makefile
    make $QJS_MAKE_TARGET
}
build_qjs

# Build x264
X264_GIT_URL=${x264_git_url:-"https://code.videolan.org/videolan/x264.git"}
X264_CONFIG=${x264_config:-"--disable-asm"}
X264_RECONFIG=${x264_reconfig:-"false"}
X264_MAKE_TARGET=${x264_make_target:-"libx264.a cli"}
X264_PATH=$WORKSPACE_LABS/x264
function build_x264() {
    cd $WORKSPACE_LABS
    if [ ! -d "$X264_PATH" ]; then
        git clone $X264_GIT_URL
        X264_RECONFIG=true
    fi
    cd $X264_PATH
    if [ "true" = "$X264_RECONFIG" ]; then ./configure $X264_CONFIG; fi
    make $X264_MAKE_TARGET
}
build_x264

# Build ffmpeg
FFMPEG_GIT_URL=${ffmpeg_git_url:-"https://github.com/FFmpeg/FFmpeg.git"}
FFMPEG_ENABLE_WASM=${ffmpeg_enable_wasm:-"false"}
FFMPEG_CONFIG=${ffmpeg_config:-"--disable-all --disable-doc --disable-asm --disable-autodetect --disable-pthreads --disable-everything --disable-iconv --enable-avcodec --enable-decoder=h264"}
FFMPEG_CONFIG_WASM=${ffmpeg_config_wasm:-"--cc=emcc --cxx=em++ --ar=emar"}
FFMPEG_RECONFIG=${ffmpeg_reconfig:-"false"}
FFMPEG_MAKE_TARGET=${ffmpeg_make_target:-"libavcodec/libavcodec.a"}
FFMPEG_PATH=$WORKSPACE_LABS/ffmpeg
function build_ffmpeg() {
    cd $WORKSPACE_LABS
    if [ ! -d "$FFMPEG_PATH" ]; then
        git clone $FFMPEG_GIT_URL ffmpeg
        FFMPEG_RECONFIG=true
    fi
    cd $FFMPEG_PATH
    wasm_configure=
    wasm_make=
    if [ "true" = "$FFMPEG_ENABLE_WASM" ]; then wasm_configure=emconfigure; wasm_make=emmake; FFMPEG_CONFIG="$FFMPEG_CONFIG_WASM $FFMPEG_CONFIG"; fi
    if [ "true" = "$FFMPEG_RECONFIG" ]; then $wasm_configure ./configure $FFMPEG_CONFIG; fi
    $wasm_make make $FFMPEG_MAKE_TARGET
}
# build_ffmpeg

# Build clabs
function build_clabs() {
    cd $CWD
    if [ "true" = "$CLABS_CLEAN" ]; then rm -rf bin lib out; fi
    mkdir -p out
    cd out
    wasm_cmake=
    wams_make=
    Denable_wasm="-DENABLE_WASM=false"
    Denable_wasm_html=
    Dqjs_path="-DQJS_PATH=$QJS_PATH"
    Dx264_path="-DX264_PATH=$X264_PATH"
    if [ "true" = "$CLABS_ENABLE_WASM" ]; then
        wasm_cmake=emcmake
        wasm_make=emmake
        Denable_wasm="-DENABLE_WASM=true"
        Denable_wasm_html="-DENABLE_WASM_HTML=$CLABS_ENABLE_WASM_HTML"
        Dqjs_path=
        Dx264_path=
    fi
    $wasm_cmake cmake $Denable_wasm $Denable_wasm_html $Dqjs_path $Dx264_path -DCMAKE_BUILD_TYPE=$CLABS_BUILD_TYPE ..
    $wasm_make make
    if [ -n "$CLABS_RUN" ]; then $CWD/bin/$CLABS_RUN; fi
}
build_clabs
