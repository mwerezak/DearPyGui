brew install openssl xz gdbm
cd ../Dependencies/cpython
mkdir debug
cd debug
../configure --enable-shared --prefix=$(pwd) LDFLAGS=-Wl,-rpath,$(pwd) --with-openssl=$(brew --prefix openssl)
make
make install

cd ../../..
mkdir cmake-build-local
cd cmake-build-local
cmake .. -DMVDIST_ONLY=True -DMVPY_VERSION=0 -DMVDPG_VERSION=local_build
cd ..
cmake --build cmake-build-local --config Release

cd Distribution
"../Dependencies/cpython/debug/python.exe" BuildPythonWheel.py ../cmake-build-local/DearPyGui/core.so 0
"../Dependencies/cpython/debug/python.exe" -m ensurepip
"../Dependencies/cpython/debug/python.exe" -m pip install --upgrade pip
"../Dependencies/cpython/debug/python.exe" -m pip install twine --upgrade
"../Dependencies/cpython/debug/python.exe" -m pip install wheel
"../Dependencies/cpython/debug/python.exe" -m setup bdist_wheel --plat-name macosx-10.6-x86_64 --dist-dir ../dist
cd ..
cd Scripts
