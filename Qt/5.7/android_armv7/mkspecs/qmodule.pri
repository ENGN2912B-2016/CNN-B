CONFIG +=  cross_compile android-style-assets compile_examples qpa precompile_header pcre
QT_BUILD_PARTS += libs
QT_NO_DEFINES =  ALSA CUPS DBUS EGL_X11 FONTCONFIG GETIFADDRS GLIB ICONV IMAGEFORMAT_JPEG LIBPROXY NIS OPENVG POSIX_FALLOCATE PULSEAUDIO TSLIB XRENDER ZLIB
QT_QCONFIG_PATH = 
host_build {
    QT_CPU_FEATURES.x86_64 =  mmx sse sse2
} else {
    QT_CPU_FEATURES.arm = 
}
QT_COORD_TYPE = double
QT_LFLAGS_ODBC   = -lodbc
styles += mac fusion windows
styles += android
DEFINES += QT_NO_MTDEV
DEFINES += QT_NO_LIBUDEV
DEFINES += QT_NO_TSLIB
DEFINES += QT_NO_LIBINPUT
QMAKE_X11_PREFIX = /usr
EXTRA_INCLUDEPATH +=  "/home/qt/openssl-1.0.2/include"
sql-drivers = 
sql-plugins =  sqlite
