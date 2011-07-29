# Microsoft Visual C++ generated build script - Do not modify

PROJ = CSQLAFX
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\CSQL\EXAMPLES\CSQLAFX\
USEMFC = 0
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
CFLAGS_D_WEXE = /G2 /W3 /Zi /AL /Gx- /Od /D "_DEBUG" /D "_AFXDLL" /GA /GEf /Fd"CSQLAFX.PDB" /GEs 
CFLAGS_R_WEXE = /Gs /G2 /W3 /AL /Gx- /Od /D "NDEBUG" /D "_AFXDLL" /GA /GEf 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mfc200d \csql\dll\debug\csqldlld llibcew libw oldnames sqlapiw commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = \csql\dll\release\csqldll mfc200 llibcew libw oldnames sqlapiw commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = CSQLAFX.DEF
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
		CSQLAFX.SBR \
		MAINFRM.SBR \
		CSQLADOC.SBR \
		CSQLAVW.SBR


CSQLAFX_RCDEP = c:\csql\examples\csqlafx\res\csqlbase.ico \
	c:\csql\examples\csqlafx\res\uk.ico \
	c:\csql\examples\csqlafx\res\csqlafx.rc2


STDAFX_DEP = c:\csql\examples\csqlafx\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
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


CSQLAFX_DEP = c:\csql\examples\csqlafx\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
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
	c:\csql\examples\csqlafx\csqlafx.h \
	c:\csql\examples\csqlafx\mainfrm.h \
	c:\csql\examples\csqlafx\csqladoc.h \
	c:\csql\examples\csqlafx\csqlavw.h


MAINFRM_DEP = c:\csql\examples\csqlafx\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
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
	c:\csql\examples\csqlafx\csqlafx.h \
	c:\csql\examples\csqlafx\mainfrm.h


CSQLADOC_DEP = c:\csql\examples\csqlafx\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
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
	c:\csql\examples\csqlafx\csqlafx.h \
	c:\csql\examples\csqlafx\csqladoc.h


CSQLAVW_DEP = c:\csql\examples\csqlafx\stdafx.h \
	c:\csql\include\csql.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
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
	c:\csql\examples\csqlafx\csqlafx.h \
	c:\csql\examples\csqlafx\csqladoc.h \
	c:\csql\examples\csqlafx\csqlavw.h \
	c:\csql\examples\ex1.cpp \
	c:\csql\examples\ex2.cpp \
	c:\csql\examples\ex3.cpp \
	c:\csql\examples\ex4.cpp \
	c:\csql\examples\ex5.cpp \
	c:\csql\examples\ex6.cpp


all:	$(PROJ).EXE

CSQLAFX.RES:	CSQLAFX.RC $(CSQLAFX_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r CSQLAFX.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

CSQLAFX.OBJ:	CSQLAFX.CPP $(CSQLAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CSQLAFX.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

CSQLADOC.OBJ:	CSQLADOC.CPP $(CSQLADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CSQLADOC.CPP

CSQLAVW.OBJ:	CSQLAVW.CPP $(CSQLAVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CSQLAVW.CPP


$(PROJ).EXE::	CSQLAFX.RES

$(PROJ).EXE::	STDAFX.OBJ CSQLAFX.OBJ MAINFRM.OBJ CSQLADOC.OBJ CSQLAVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
CSQLAFX.OBJ +
MAINFRM.OBJ +
CSQLADOC.OBJ +
CSQLAVW.OBJ +
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
	$(RC) $(RESFLAGS) CSQLAFX.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	CSQLAFX.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) CSQLAFX.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
