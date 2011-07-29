#	IMPORTANT: open as an external makefile from the Visual C++ Workbench
PROJ = CSQLDLL
DEBUG = 0
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\CSQL\DLL\RELEASE\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDINCS.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDINCS.H
FIRSTC =             
FIRSTCPP = STDINCS.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /FR /GD /GEf /Fd"CSQLDLLD.PDB" 
CFLAGS_R_WDLL = /nologo /W3 /ALw /Od /D "NDEBUG" /D "_AFXDLL" /FR /GD /GEf 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = mfc200d ldllcew libw sqlapiw oldnames commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = mfc200 ldllcew libw sqlapiw oldnames commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = CSQLDLL.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDINCS.SBR \
		CSQLCUR.SBR \
		CSQLDTM.SBR \
		CSQLEXEP.SBR \
		CSQLIDAT.SBR \
		CSQLINUM.SBR \
		CSQLLVC.SBR \
		CSQLNUM.SBR \
		CSQLROW.SBR \
		CSQLSEL.SBR \
		CSQLSRVR.SBR \
		CSQLSTR.SBR \
		CSQLDLL.SBR \
		CSQLCMD.SBR


STDINCS_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h


CSQLCUR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h


CSQLDTM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqldtm.h


CSQLEXEP_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h


CSQLIDAT_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h


CSQLINUM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqlinum.h


CSQLLVC_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqllvc.h


CSQLNUM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h


CSQLROW_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlrow.h


CSQLSEL_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlsel.h


CSQLSRVR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlsrvr.h


CSQLSTR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlstr.h


CSQLDLL_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqldll.h


CSQLCMD_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlcmd.h


all:	$(PROJ).DLL $(PROJ).BSC

STDINCS.OBJ:	..\..\SRC\STDINCS.CPP $(STDINCS_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ..\..\SRC\STDINCS.CPP

CSQLCUR.OBJ:	..\..\SRC\CSQLCUR.CPP $(CSQLCUR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLCUR.CPP

CSQLDTM.OBJ:	..\..\SRC\CSQLDTM.CPP $(CSQLDTM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLDTM.CPP

CSQLEXEP.OBJ:	..\..\SRC\CSQLEXEP.CPP $(CSQLEXEP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLEXEP.CPP

CSQLIDAT.OBJ:	..\..\SRC\CSQLIDAT.CPP $(CSQLIDAT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLIDAT.CPP

CSQLINUM.OBJ:	..\..\SRC\CSQLINUM.CPP $(CSQLINUM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLINUM.CPP

CSQLLVC.OBJ:	..\..\SRC\CSQLLVC.CPP $(CSQLLVC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLLVC.CPP

CSQLNUM.OBJ:	..\..\SRC\CSQLNUM.CPP $(CSQLNUM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLNUM.CPP

CSQLROW.OBJ:	..\..\SRC\CSQLROW.CPP $(CSQLROW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLROW.CPP

CSQLSEL.OBJ:	..\..\SRC\CSQLSEL.CPP $(CSQLSEL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLSEL.CPP

CSQLSRVR.OBJ:	..\..\SRC\CSQLSRVR.CPP $(CSQLSRVR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLSRVR.CPP

CSQLSTR.OBJ:	..\..\SRC\CSQLSTR.CPP $(CSQLSTR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLSTR.CPP

CSQLDLL.OBJ:	..\CSQLDLL.CPP $(CSQLDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\CSQLDLL.CPP

CSQLCMD.OBJ:	..\..\SRC\CSQLCMD.CPP $(CSQLCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLCMD.CPP


$(PROJ).DLL::	STDINCS.OBJ CSQLCUR.OBJ CSQLDTM.OBJ CSQLEXEP.OBJ CSQLIDAT.OBJ CSQLINUM.OBJ \
	CSQLLVC.OBJ CSQLNUM.OBJ CSQLROW.OBJ CSQLSEL.OBJ CSQLSRVR.OBJ CSQLSTR.OBJ \
	CSQLDLL.OBJ CSQLCMD.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDINCS.OBJ +
CSQLCUR.OBJ +
CSQLDTM.OBJ +
CSQLEXEP.OBJ +
CSQLIDAT.OBJ +
CSQLINUM.OBJ +
CSQLLVC.OBJ +
CSQLNUM.OBJ +
CSQLROW.OBJ +
CSQLSEL.OBJ +
CSQLSRVR.OBJ +
CSQLSTR.OBJ +
CSQLDLL.OBJ +
CSQLCMD.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
c:\gupta\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@
	implib $(PROJ).LIB $(PROJ).DLL $(PROJ).DEF


run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
