# Microsoft Visual C++ generated build script - Do not modify

PROJ = CSQLMI
DEBUG = 0
PROGTYPE = 4
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\CSQL\EXAMPLES\LIB.MI\RELEASE\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = CSQLSSEL.CPP
RC = rc
CFLAGS_D_LIB = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /D "CSQLCMD_VBASE" /I "c:\gupta" /FR /GA /Fd"CSQL.PDB"
CFLAGS_R_LIB = /nologo /Gs /G2 /W3 /AL /Ox /D "NDEBUG" /D "CSQLCMD_VBASE" /I "c:\gupta" /FR /GA 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_LIB)
LFLAGS = 
LIBS = 
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_LIB)
LFLAGS = 
LIBS = 
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = CSQLSCMD.SBR \
		CSQLSSEL.SBR \
		CSQLCMD.SBR \
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
		CSQLWAPP.SBR


CSQLSCMD_DEP = c:\csql\include\csql.h \
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
	c:\csql\examples\csqlscmd.h


CSQLSSEL_DEP = c:\csql\include\csql.h \
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
	c:\csql\examples\csqlscmd.h \
	c:\csql\examples\csqlssel.h


CSQLCMD_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlcmd.h


CSQLCUR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h


CSQLDTM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqldtm.h


CSQLEXEP_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h


CSQLIDAT_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqlidat.h


CSQLINUM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
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
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
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
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlsrvr.h


CSQLSTR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqlstr.h


CSQLWAPP_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlwapp.h


all:	$(PROJ).LIB $(PROJ).BSC

CSQLSCMD.OBJ:	..\..\CSQLSCMD.CPP $(CSQLSCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\CSQLSCMD.CPP

CSQLSSEL.OBJ:	..\..\CSQLSSEL.CPP $(CSQLSSEL_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ..\..\CSQLSSEL.CPP

CSQLCMD.OBJ:	..\..\..\SRC\CSQLCMD.CPP $(CSQLCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLCMD.CPP

CSQLCUR.OBJ:	..\..\..\SRC\CSQLCUR.CPP $(CSQLCUR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLCUR.CPP

CSQLDTM.OBJ:	..\..\..\SRC\CSQLDTM.CPP $(CSQLDTM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLDTM.CPP

CSQLEXEP.OBJ:	..\..\..\SRC\CSQLEXEP.CPP $(CSQLEXEP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLEXEP.CPP

CSQLIDAT.OBJ:	..\..\..\SRC\CSQLIDAT.CPP $(CSQLIDAT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLIDAT.CPP

CSQLINUM.OBJ:	..\..\..\SRC\CSQLINUM.CPP $(CSQLINUM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLINUM.CPP

CSQLLVC.OBJ:	..\..\..\SRC\CSQLLVC.CPP $(CSQLLVC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLLVC.CPP

CSQLNUM.OBJ:	..\..\..\SRC\CSQLNUM.CPP $(CSQLNUM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLNUM.CPP

CSQLROW.OBJ:	..\..\..\SRC\CSQLROW.CPP $(CSQLROW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLROW.CPP

CSQLSEL.OBJ:	..\..\..\SRC\CSQLSEL.CPP $(CSQLSEL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLSEL.CPP

CSQLSRVR.OBJ:	..\..\..\SRC\CSQLSRVR.CPP $(CSQLSRVR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLSRVR.CPP

CSQLSTR.OBJ:	..\..\..\SRC\CSQLSTR.CPP $(CSQLSTR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLSTR.CPP

CSQLWAPP.OBJ:	..\..\..\SRC\CSQLWAPP.CPP $(CSQLWAPP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\..\SRC\CSQLWAPP.CPP

$(PROJ).LIB::	CSQLSCMD.OBJ CSQLSSEL.OBJ CSQLCMD.OBJ CSQLCUR.OBJ CSQLDTM.OBJ CSQLEXEP.OBJ \
	CSQLIDAT.OBJ CSQLINUM.OBJ CSQLLVC.OBJ CSQLNUM.OBJ CSQLROW.OBJ CSQLSEL.OBJ CSQLSRVR.OBJ \
	CSQLSTR.OBJ CSQLWAPP.OBJ $(OBJS_EXT)
	echo >NUL @<<$(PROJ).CRF
$@ /PAGESIZE:64
y
+CSQLSCMD.OBJ &
+CSQLSSEL.OBJ &
+CSQLCMD.OBJ &
+CSQLCUR.OBJ &
+CSQLDTM.OBJ &
+CSQLEXEP.OBJ &
+CSQLIDAT.OBJ &
+CSQLINUM.OBJ &
+CSQLLVC.OBJ &
+CSQLNUM.OBJ &
+CSQLROW.OBJ &
+CSQLSEL.OBJ &
+CSQLSRVR.OBJ &
+CSQLSTR.OBJ &
+CSQLWAPP.OBJ &
;
<<
	if exist $@ del $@
	lib @$(PROJ).CRF

$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
