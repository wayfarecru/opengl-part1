#!/bin/make

END =
SRCS = \
	$(wildcard *.c) \
	$(wildcard *.cpp) \
	$(END)
SRCS := $(filter-out common.c, $(SRCS))
OBJS1 = $(SRCS:.cpp=.obj)
OBJS = $(OBJS1:.c=.obj)
EXES1 = $(SRCS:.cpp=.exe)
EXES = $(EXES1:.c=.exe)

VS_VER = 14.41.34120
# visual studio compiler version
WK_VER = 10.0.22621.0
# Windows Kits version

FLAG_ARCH := x64
#FLAG_ARCH := x86

FLAG_MODE := release
#FLAG_MODE := debug

#CC = "/cygdrive/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/$(VS_VER)/bin/Hostx64/x64/cl.exe"
#LINK = "/cygdrive/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/$(VS_VER)/bin/Hostx64/x64/link.exe"

CC=cl.exe
CFLAGS =
CFLAGS += /permissive- /GS /W4 /Zc:wchar_t /Gm- /Zc:inline /fp:precise
CFLAGS += /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope
CFLAGS += /Gd /FC /EHsc /nologo /diagnostics:caret
CFLAGS += /std:c++17
ifeq ($(FLAG_MODE),release)
CFLAGS += /GL /Gy /Zi /O2 /sdl /D "NDEBUG" /Oi /MD 
else
CFLAGS += /JMC /ZI /Od /sdl /D "_DEBUG" /RTC1 /MDd
endif
CFLAGS += /D WIN32 /D PRINT_REPORT /D _CRT_SECURE_NO_WARNINGS

#CFLAGS += /I "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\$(VS_VER)\\include"
CFLAGS += /I "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\$(VS_VER)\\include"
CFLAGS += /I "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\$(WK_VER)\\um"
CFLAGS += /I "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\$(WK_VER)\\shared"
CFLAGS += /I "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\$(WK_VER)\\ucrt"

LINK=link.exe
LDFLAGS =
LDFLAGS += /MACHINE:X64
#LDLIBS += /LIBPATH:"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\$(VS_VER)\\lib/x64"
LDLIBS += /LIBPATH:"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\$(VS_VER)\\lib\\x64"
LDLIBS += /LIBPATH:"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\$(WK_VER)\\um\\x64"
LDLIBS += /LIBPATH:"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\$(WK_VER)\\ucrt\\x64"

LDFLAGS += /NXCOMPAT /SUBSYSTEM:CONSOLE
LDFLAGS += /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"
LDFLAGS += /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1 
ifeq ($(FLAG_MODE),release)
LDFLAGS += /LTCG /OPT:REF /INCREMENTAL:NO /OPT:ICF
else
LDFLAGS += /INCREMENTAL /DEBUG
endif
LINK.obj = $(LINK) $(LDFLAGS)

.TARGETS:	.cpp .c .obj .exe

%.obj:	%.cpp
	$(COMPILE.c) /c /Fo$@ $<
%.obj:	%.c
	$(COMPILE.c) /c /TC /Fo$@ $<
%.exe:	%.obj
	$(LINK.obj) $^ $(LOADLIBES) $(LDLIBS) /OUT:$@

default:	$(EXES)

clean:
	/bin/rm -f *.obj
	/bin/rm -f *.exp *.ilk *.pdb *.idb *.iobj *.ipdb

clobber: clean
	/bin/rm -f *.exe *.exe.manifest
