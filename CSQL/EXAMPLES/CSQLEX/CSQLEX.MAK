# Microsoft Visual C++ generated build script - Do not modify

PROJ = CSQLEX
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\CSQL\EXAMPLES\CSQLEX\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /GA /Fd"CSQLEX.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AL /O1 /D "NDEBUG" /FR /GA /GEe 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO /MAP  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /MAP  
LIBS_D_WEXE = lafxcwd oldnames libw llibcew sqlapiw \csql\lib\debug\csqld commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = lafxcw oldnames libw llibcew sqlapiw \csql\lib\release\csql commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = CSQLEX.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		CSQLEX.SBR \
		MAINFRM.SBR \
		CSQLEDOC.SBR \
		CSQLEVW.SBR


CSQLEX_RCDEP = c:\csql\examples\csqlex\res\csqlbase.ico \
	c:\csql\examples\csqlex\res\uk.ico \
	c:\csql\examples\csqlex\res\csqlex.rc2


STDAFX_DEP = c:\csql\examples\csqlex\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlsrvr.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlsel.h \
	c:\csql\include\csqlwapp.h \
	c:\csql\include\csqldll.h


CSQLEX_DEP = c:\csql\examples\csqlex\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlsrvr.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlsel.h \
	c:\csql\include\csqlwapp.h \
	c:\csql\include\csqldll.h \
	c:\csql\examples\csqlex\csqlex.h \
	c:\csql\examples\csqlex\mainfrm.h \
	c:\csql\examples\csqlex\csqledoc.h \
	c:\csql\examples\csqlex\csqlevw.h


MAINFRM_DEP = c:\csql\examples\csqlex\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlsrvr.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlsel.h \
	c:\csql\include\csqlwapp.h \
	c:\csql\include\csqldll.h \
	c:\csql\examples\csqlex\csqlex.h \
	c:\csql\examples\csqlex\mainfrm.h


CSQLEDOC_DEP = c:\csql\examples\csqlex\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlsrvr.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlsel.h \
	c:\csql\include\csqlwapp.h \
	c:\csql\include\csqldll.h \
	c:\csql\examples\csqlex\csqlex.h \
	c:\csql\examples\csqlex\csqledoc.h


CSQLEVW_DEP = c:\csql\examples\csqlex\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlsrvr.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlsel.h \
	c:\csql\include\csqlwapp.h \
	c:\csql\include\csqldll.h \
	c:\csql\examples\csqlex\csqlex.h \
	c:\csql\examples\csqlex\csqledoc.h \
	c:\csql\examples\csqlex\csqlevw.h \
	c:\csql\examples\ex1.cpp \
	c:\csql\examples\ex2.cpp \
	c:\csql\examples\ex3.cpp \
	c:\csql\examples\ex4.cpp \
	c:\csql\examples\ex5.cpp \
	c:\csql\examples\ex6.cpp


all:	$(PROJ).EXE

CSQLEX.RES:	CSQLEX.RC $(CSQLEX_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r CSQLEX.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

CSQLEX.OBJ:	CSQLEX.CPP $(CSQLEX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CSQLEX.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

CSQLEDOC.OBJ:	CSQLEDOC.CPP $(CSQLEDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CSQLEDOC.CPP

CSQLEVW.OBJ:	CSQLEVW.CPP $(CSQLEVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CSQLEVW.CPP


$(PROJ).EXE::	CSQLEX.RES

$(PROJ).EXE::	STDAFX.OBJ CSQLEX.OBJ MAINFRM.OBJ CSQLEDOC.OBJ CSQLEVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
CSQLEX.OBJ +
MAINFRM.OBJ +
CSQLEDOC.OBJ +
CSQLEVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
C:\MSVC\LIB\+
C:\MSVC\MFC\LIB\+
C:\GUPTA\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) CSQLEX.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	CSQLEX.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) CSQLEX.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
