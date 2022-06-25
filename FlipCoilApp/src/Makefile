TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = FlipCoil
# FlipCoil.dbd will be created and installed
DBD += FlipCoil.dbd

# FlipCoil.dbd will be made up from these files:
FlipCoil_DBD += base.dbd

# Include dbd files from all support applications:
#FlipCoil_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#FlipCoil_LIBS += xxx

# FlipCoil_registerRecordDeviceDriver.cpp derives from FlipCoil.dbd
FlipCoil_SRCS += FlipCoil_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
FlipCoil_SRCS_DEFAULT += FlipCoilMain.cpp
FlipCoil_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#FlipCoil_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
FlipCoil_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

