TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

LIBRARY_IOC += regexasub

USR_CXXFLAGS += -std=c++11

# xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
# install regexasub.dbd into <top>/dbd
DBD += regexasub.dbd

# specify all source files to be compiled and added to the library
regexasub_SRCS += regexasub.cpp

regexasub_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

