#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/main_batch.o \
	${OBJECTDIR}/main_cluster.o \
	${OBJECTDIR}/main_mfcc.o \
	${OBJECTDIR}/main_query.o \
	${OBJECTDIR}/src/batch.o \
	${OBJECTDIR}/src/cluster.o \
	${OBJECTDIR}/src/fft.o \
	${OBJECTDIR}/src/filter.o \
	${OBJECTDIR}/src/kmeans.o \
	${OBJECTDIR}/src/mfcc.o \
	${OBJECTDIR}/src/query.o \
	${OBJECTDIR}/src/quicksort.o \
	${OBJECTDIR}/src/wave.o \
	${OBJECTDIR}/src/window.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/musicretrieval

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/musicretrieval: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/musicretrieval ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/main_batch.o: main_batch.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_batch.o main_batch.cpp

${OBJECTDIR}/main_cluster.o: main_cluster.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_cluster.o main_cluster.cpp

${OBJECTDIR}/main_mfcc.o: main_mfcc.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_mfcc.o main_mfcc.cpp

${OBJECTDIR}/main_query.o: main_query.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_query.o main_query.cpp

${OBJECTDIR}/src/batch.o: src/batch.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/batch.o src/batch.cpp

${OBJECTDIR}/src/cluster.o: src/cluster.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/cluster.o src/cluster.cpp

${OBJECTDIR}/src/fft.o: src/fft.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/fft.o src/fft.cpp

${OBJECTDIR}/src/filter.o: src/filter.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/filter.o src/filter.cpp

${OBJECTDIR}/src/kmeans.o: src/kmeans.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/kmeans.o src/kmeans.cpp

${OBJECTDIR}/src/mfcc.o: src/mfcc.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/mfcc.o src/mfcc.cpp

${OBJECTDIR}/src/query.o: src/query.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/query.o src/query.cpp

${OBJECTDIR}/src/quicksort.o: src/quicksort.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/quicksort.o src/quicksort.cpp

${OBJECTDIR}/src/wave.o: src/wave.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/wave.o src/wave.cpp

${OBJECTDIR}/src/window.o: src/window.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/window.o src/window.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
