if [ '-h' == "$1" ] || [ '--help' == "$1" ]; then
    echo "Usage:"
    echo "  clean=1 ./build.sh"
    echo "      Clean"
    echo "  run=? ./build.sh"
    echo "      Run ? = test_trace | test_file | test_qjs"
    exit 0
fi

root=`pwd`

if [ -n "$clean" ]; then rm -rf out; fi \
&& mkdir -p out \
&& cd out \
&& cmake -DCMAKE_BUILD_TYPE=Debug .. \
&& make \
&& if [ -n "$run" ]; then $root/bin/$run; fi
