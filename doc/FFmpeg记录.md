### configure

修改之前:
SLIBNAME_WITH_MAJOR=’$(SLIBNAME).$(LIBMAJOR)’

LIB_INSTALL_EXTRA_CMD=’$$(RANLIB) “$(LIBDIR)/$(LIBNAME)”‘

SLIB_INSTALL_NAME=’$(SLIBNAME_WITH_VERSION)’

SLIB_INSTALL_LINKS=’$(SLIBNAME_WITH_MAJOR) $(SLIBNAME)’
复制代码修改之后:
SLIBNAME_WITH_MAJOR=’$(SLIBPREF)$(FULLNAME)-$(LIBMAJOR)$(SLIBSUF)’

LIB_INSTALL_EXTRA_CMD=’$$(RANLIB) “$(LIBDIR)/$(LIBNAME)”‘

SLIB_INSTALL_NAME=’$(SLIBNAME_WITH_MAJOR)’

SLIB_INSTALL_LINKS=’$(SLIBNAME)’



### ffbuild/version.sh
#!/bin/bash
 
ADDI_CFLAGS="-marm"
API=19
PLATFORM=arm-linux-androideabi
CPU=armv7-a
#自己本地的ndk路径。
NDK=/Users/cainjiang/ProgramFiles/android-ndk-r17c
SYSROOT=$NDK/platforms/android-$API/arch-arm/
ISYSROOT=$NDK/sysroot
ASM=$ISYSROOT/usr/include/$PLATFORM
TOOLCHAIN=$NDK/toolchains/$PLATFORM-4.9/prebuilt/darwin-x86_64
#自己指定一个输出目录，用来放生成的文件的。
OUTPUT=/Users/cainjiang/ProgramFiles/ffmpeg-4.1.3/android_out 
function build
{
./configure \
--prefix=$OUTPUT \
--enable-shared \
--disable-static \
--disable-doc \
--disable-ffmpeg \
--disable-ffplay \
--disable-ffprobe \
--disable-avdevice \
--disable-doc \
--disable-symver \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--target-os=android \
--arch=arm \
--enable-cross-compile \
--sysroot=$SYSROOT \
--extra-cflags="-I$ASM -isysroot $ISYSROOT -Os -fpic -marm" \
--extra-ldflags="-marm" \
$ADDITIONAL_CONFIGURE_FLAG
  make clean
  make 
  make install
}
build
