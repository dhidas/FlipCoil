#!../../bin/linux-x86_64/FlipCoil

#- You may have to change FlipCoil to something else
#- everywhere it appears in this file

< envPaths

epicsEnvSet("ENGINEER", "Dean Andrew Hidas is not an engineer. <dhidas@bnl.gov>")
epicsEnvSet("PMACUTIL", "/usr/share/epics-pmacutil-dev")
epicsEnvSet("PMAC1_IP", "10.0.161.26:1025")
epicsEnvSet("sys", "MMF")
epicsEnvSet("dev", "FC:2")
epicsEnvSet("STREAM_PROTOCOL_PATH", "/usr/lib/epics/protocol:$(TOP)/proto")
epicsEnvSet("LOCATION",$(HOSTNAME))



## Register all support components
dbLoadDatabase("../../dbd/FlipCoil.dbd",0,0)
FlipCoil_registerRecordDeviceDriver(pdbbase) 

pmacAsynIPConfigure("P0", $(PMAC1_IP))
pmacCreateController("PMAC1", "P0", 0, 7, 50, 500)
pmacCreateAxis("PMAC1", 1)
pmacCreateAxis("PMAC1", 2)
pmacCreateAxis("PMAC1", 3)
pmacCreateAxis("PMAC1", 4)
pmacCreateAxis("PMAC1", 5)
pmacCreateAxis("PMAC1", 6)
pmacCreateAxis("PMAC1", 7)

# Create CS (ControllerPort, Addr, CSNumber, CSRef, Prog)
# Rotary: Coordinate System 5 | PROG 5
pmacAsynCoordCreate("P0", 0, 2, 0, 2) # X
pmacAsynCoordCreate("P0", 0, 3, 1, 3) # Y
pmacAsynCoordCreate("P0", 0, 5, 2, 5) # R

# Configure CS (PortName, DriverName, CSRef, NAxes)
drvAsynMotorConfigure("PMAC1CS2", "pmacAsynCoord", 0, 2)
drvAsynMotorConfigure("PMAC1CS3", "pmacAsynCoord", 1, 2)
drvAsynMotorConfigure("PMAC1CS5", "pmacAsynCoord", 2, 2)

# Set scale factor (CSRef, axis, stepsPerUnit)
pmacSetCoordStepsPerUnit(0, 0, 1)
pmacSetCoordStepsPerUnit(0, 1, 1)
pmacSetCoordStepsPerUnit(1, 2, 1)
pmacSetCoordStepsPerUnit(1, 3, 1)
pmacSetCoordStepsPerUnit(2, 4, 1)
pmacSetCoordStepsPerUnit(2, 5, 1)

# Set Idle and Moving poll periods (CSRef, PeriodsMilliSeconds)
pmacSetCoordIdlePollPeriod(0, 500)
pmacSetCoordMovingPollPeriod(0, 100)
pmacSetCoordIdlePollPeriod(1, 500)
pmacSetCoordMovingPollPeriod(1, 100)
pmacSetCoordIdlePollPeriod(2, 500)
pmacSetCoordMovingPollPeriod(2, 100)

## Load record instances
dbLoadRecords("../../db/FlipCoil.db","SYS=$(sys),DEV=$(dev),,PORT=P0")

dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:R+}-Mtr,MOTOR=PMAC1,ADDR=5,DESC=Rotary +z  Mtr, MRES=0.002, PREC=2")
dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:R-}-Mtr,MOTOR=PMAC1,ADDR=6,DESC=Rotary -z  Mtr, MRES=0.002, PREC=2")
dbLoadRecords("../../db/asynRecord.db","P=$(sys),R={$(dev)}Asyn,ADDR=1,PORT=P0,IMAX=128,OMAX=128")

cd ../../
set_savefile_path("as","/save")
set_requestfile_path("as","/req")
set_pass0_restoreFile("ioc_settings.sav")
set_pass1_restoreFile("ioc_waveforms.sav")

iocInit()


makeAutosaveFileFromDbInfo("as/req/ioc_settings.req", "autosaveFields_pass0")
makeAutosaveFileFromDbInfo("as/req/ioc_waveforms.req", "autosaveFields_pass1")
create_monitor_set("ioc_settings.req", 5, "")
create_monitor_set("ioc_waveforms.req", 60, "")
