# gdb-for-windows-nonascii
[release](https://github.com/fjh1997/gdb-for-windows-nonascii/releases/download/1.0.0/release.zip)

tmp solution of adb.exe truncating non-ascii name in windows when pull and push.

see [issue ](https://issuetracker.google.com/issues/143232373)
place the patch in /prebuilts/gcc/linux-x86/host/x86_64-w64-mingw32-4.8/toolchain-patches/mingw-w64 
run build-mingw64-toolchain.sh to make toolchain.clean and build adb.exe as usual.
or much easier.In msys2
```
cd mingw-w64-master
git apply rewrite.patch
cd mingw-w64-crt
./configure
make lib32/libmingwex.a
```
replace the /prebuilts/gcc/linux-x86/host/x86_64-w64-mingw32-4.8/x86_64-w64-mingw32/lib32/libmingwex.a
clean and build adb.exe as usual.
```
rm -rf out
source build/envsetup.sh
cd packages/modules/adb
mm
```
use msys2 to strip adb.exe
```
strip -s adb.exe
```
