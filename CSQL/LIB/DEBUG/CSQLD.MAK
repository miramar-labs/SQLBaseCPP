# Microsoft Visual C++ generated build script - Do not modify

PROJ = CSQLD
DEBUG = 1
PROGTYPE = 4
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\CSQL\LIB\DEBUG\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = CSQLCUR.CPP 
RC = rc
CFLAGS_D_LIB = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /I "c:\gupta" /FR /GA /Fd"CSQLD.PDB"
CFLAGS_R_LIB = /nologo /Gs /G2 /W3 /AL /Ox /D "NDEBUG" /I "c:\gupta" /FR /GA 
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
SBRS = CSQLCMD.SBR \
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


CSQLCMD_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlexep.inl \
	c:\csql\include\csqlcur.inl \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqlnum.inl \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqllvc.inl \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqlstr.inl \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqldtm.inl \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlidat.inl \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlinum.inl \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlcmd.inl


CSQLCUR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlexep.inl \
	c:\csql\include\csqlcur.inl


CSQLDTM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqldtm.inl


CSQLEXEP_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlexep.inl \
	c:\csql\include\csqlcur.inl


CSQLIDAT_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqldtm.inl \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlidat.inl


CSQLINUM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlexep.inl \
	c:\csql\include\csqlcur.inl \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqlnum.inl \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlinum.inl


CSQLLVC_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqllvc.inl


CSQLNUM_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqlnum.inl


CSQLROW_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqlnum.inl \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqllvc.inl \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqlstr.inl \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqldtm.inl \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlidat.inl \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlinum.inl \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlrow.inl


CSQLSEL_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlexep.inl \
	c:\csql\include\csqlcur.inl \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqlnum.h \
	c:\csql\include\csqlnum.inl \
	c:\csql\include\csqllvc.h \
	c:\csql\include\csqllvc.inl \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqlstr.inl \
	c:\csql\include\csqldtm.h \
	c:\csql\include\csqldtm.inl \
	c:\csql\include\csqlidat.h \
	c:\csql\include\csqlidat.inl \
	c:\csql\include\csqlinum.h \
	c:\csql\include\csqlinum.inl \
	c:\csql\include\csqlcmd.h \
	c:\csql\include\csqlcmd.inl \
	c:\csql\include\csqlrow.h \
	c:\csql\include\csqlrow.inl \
	c:\csql\include\csqlsel.h


CSQLSRVR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlexep.inl \
	c:\csql\include\csqlcur.inl \
	c:\csql\include\csqlsrvr.h \
	c:\csql\include\csqlsrvr.inl


CSQLSTR_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqltype.h \
	c:\csql\include\csqltype.inl \
	c:\csql\include\csqlstr.h \
	c:\csql\include\csqlstr.inl


CSQLWAPP_DEP = c:\csql\include\stdincs.h \
	c:\gupta\sql.h \
	c:\gupta\sqlsrv.h \
	c:\csql\include\csqlcur.h \
	c:\csql\include\csqlexep.h \
	c:\csql\include\csqlexep.inl \
	c:\csql\include\csqlcur.inl \
	c:\csql\include\csqlwapp.h


all:	$(PROJ).LIB $(PROJ).BSC

CSQLCMD.OBJ:	..\..\SRC\CSQLCMD.CPP $(CSQLCMD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLCMD.CPP

CSQLCUR.OBJ:	..\..\SRC\CSQLCUR.CPP $(CSQLCUR_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ..\..\SRC\CSQLCUR.CPP

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

CSQLWAPP.OBJ:	..\..\SRC\CSQLWAPP.CPP $(CSQLWAPP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\SRC\CSQLWAPP.CPP

$(PROJ).LIB::	CSQLCMD.OBJ CSQLCUR.OBJ CSQLDTM.OBJ CSQLEXEP.OBJ CSQLIDAT.OBJ CSQLINUM.OBJ \
	CSQLLVC.OBJ CSQLNUM.OBJ CSQLROW.OBJ CSQLSEL.OBJ CSQLSRVR.OBJ CSQLSTR.OBJ CSQLWAPP.OBJ $(OBJS_EXT)
	echo >NUL @<<$(PROJ).CRF
$@ /PAGESIZE:64
y
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
