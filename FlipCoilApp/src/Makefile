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
FlipCoil_DBD += base.dbd
FlipCoil_DBD += asyn.dbd
FlipCoil_DBD += motorSupport.dbd
FlipCoil_DBD += drvAsynIPPort.dbd
#FlipCoil_DBD += drvAsynSerialPort.dbd
FlipCoil_DBD += pmacAsynMotorPort.dbd
FlipCoil_DBD += pmacAsynMotor.dbd
FlipCoil_DBD += pmacAsynIPPort.dbd
FlipCoil_DBD += pmacAsynCoord.dbd
FlipCoil_DBD += asSupport.dbd
FlipCoil_DBD += busySupport.dbd
FlipCoil_DBD += calcSupport.dbd
FlipCoil_DBD += system.dbd
FlipCoil_DBD += stream.dbd
FlipCoil_DBD += devIocStats.dbd
FlipCoil_DBD += reccaster.dbd

# Add all the support libraries needed by this IOC
FlipCoil_LIBS += pmacAsynIPPort
FlipCoil_LIBS += pmacAsynCoord
FlipCoil_LIBS += motor
FlipCoil_LIBS += asyn
FlipCoil_LIBS += autosave
FlipCoil_LIBS += busy
FlipCoil_LIBS += calc
FlipCoil_LIBS += stream
FlipCoil_LIBS += devIocStats
FlipCoil_LIBS += pmacAsynMotor
FlipCoil_LIBS += pmacAsynMotorPort
FlipCoil_LIBS += reccaster

# FlipCoil_registerRecordDeviceDriver.cpp derives from FlipCoil.dbd
FlipCoil_SRCS += FlipCoil_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
FlipCoil_SRCS_DEFAULT += FlipCoilMain.cpp
FlipCoil_SRCS_vxWorks += -nil-

# Finally link to the EPICS Base libraries
FlipCoil_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

