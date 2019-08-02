if [ '-h' == "$1" ] || [ '--help' == "$1" ]; then
    echo "Usage:"
    echo "  clean=1 ./build.sh"
    echo "      Clean"
    echo "  run=1 ./build.sh"
    echo "      Run"
    exit 0
fi

if [ -n "$clean" ]; then rm -rf out; fi \
&& mkdir -p out \
&& cd out \
&& cmake -DCMAKE_BUILD_TYPE=Debug .. \
&& make \
&& if [ -n "$run" ]; then ./main; fi
