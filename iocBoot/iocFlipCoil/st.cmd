#!../../bin/linux-x86_64/FlipCoil

#- You may have to change FlipCoil to something else
#- everywhere it appears in this file

< envPaths

epicsEnvSet("ENGINEER", "Dean Andrew Hidas is not an engineer. <dhidas@bnl.gov>")
epicsEnvSet("PMACUTIL", "/usr/share/epics-pmacutil-dev")
epicsEnvSet("PMAC1_IP", "192.6.94.121:1025") # Lab
#epicsEnvSet("PMAC1_IP", "10.0.161.26:1025") # Ring
epicsEnvSet("sys", "MMF")
epicsEnvSet("dev", "FC:2")
epicsEnvSet("STREAM_PROTOCOL_PATH", "/usr/lib/epics/protocol:$(TOP)/proto")
epicsEnvSet("LOCATION",$(HOSTNAME))

#epicsEnvSet('EPICS_CA_AUTO_ADDR_LIST', 'NO')
#epicsEnvSet('EPICS_CA_ADDR_LIST', '192.168.122.255')


## Register all support components
dbLoadDatabase("../../dbd/FlipCoil.dbd",0,0)
FlipCoil_registerRecordDeviceDriver(pdbbase) 

# Configure keithley
drvAsynIPPortConfigure ("KEITHLEY1", "192.6.94.120:4001")


pmacAsynIPConfigure("P0", $(PMAC1_IP))
pmacCreateController("PMAC1", "P0", 0, 8, 50, 500)
pmacCreateAxis("PMAC1", 1)
pmacCreateAxis("PMAC1", 2)
pmacCreateAxis("PMAC1", 3)
pmacCreateAxis("PMAC1", 4)
#pmacCreateAxis("PMAC1", 5)
#pmacCreateAxis("PMAC1", 6)
pmacCreateAxis("PMAC1", 7)
pmacCreateAxis("PMAC1", 8)

# pmacDisableLimitsCheck(int card, int axis, int allAxes)
pmacDisableLimitsCheck(0, 1, 1)


# Create CS (ControllerPort, Addr, CSNumber, CSRef, Prog)
# Rotary: Coordinate System 5 | PROG 5
pmacAsynCoordCreate("P0", 0, 3, 0, 3) # X
pmacAsynCoordCreate("P0", 0, 4, 1, 4) # Y
pmacAsynCoordCreate("P0", 0, 5, 2, 5) # R

# Configure CS (PortName, DriverName, CSRef, NAxes)
drvAsynMotorConfigure("PMAC1CS3", "pmacAsynCoord", 0, 2)
drvAsynMotorConfigure("PMAC1CS4", "pmacAsynCoord", 1, 2)
drvAsynMotorConfigure("PMAC1CS5", "pmacAsynCoord", 2, 2)

# Set scale factor (CSRef, axis, stepsPerUnit)
pmacSetCoordStepsPerUnit(0, 0, 1000)
pmacSetCoordStepsPerUnit(0, 1, 1000)
pmacSetCoordStepsPerUnit(1, 0, 1000)
pmacSetCoordStepsPerUnit(1, 1, 1000)
pmacSetCoordStepsPerUnit(2, 0, 1)
pmacSetCoordStepsPerUnit(2, 1, 1)

# Set Idle and Moving poll periods (CSRef, PeriodsMilliSeconds)
pmacSetCoordIdlePollPeriod(0, 500)
pmacSetCoordMovingPollPeriod(0, 100)
pmacSetCoordIdlePollPeriod(1, 500)
pmacSetCoordMovingPollPeriod(1, 100)
pmacSetCoordIdlePollPeriod(2, 500)
pmacSetCoordMovingPollPeriod(2, 100)

## Load record instances
dbLoadRecords("../../db/FlipCoil.db","SYS=$(sys),DEV=$(dev),,PORT=P0")

dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:X+}-Mtr,MOTOR=PMAC1,ADDR=1,DESC=X Mtr at +z, MRES=0.001, PREC=3")
dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:X-}-Mtr,MOTOR=PMAC1,ADDR=2,DESC=X Mtr at -z, MRES=0.001, PREC=3")
dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:Y+}-Mtr,MOTOR=PMAC1,ADDR=3,DESC=Y Mtr at +z, MRES=0.001, PREC=3")
dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:Y-}-Mtr,MOTOR=PMAC1,ADDR=4,DESC=Y Mtr at -z, MRES=0.001, PREC=3")
dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:R+}-Mtr,MOTOR=PMAC1,ADDR=7,DESC=Rotary Mtr at +z, MRES=0.002, PREC=3")
dbLoadRecords("../../db/motor.db","P=$(sys),M={$(dev)-Ax:R-}-Mtr,MOTOR=PMAC1,ADDR=8,DESC=Rotary Mtr at -z, MRES=0.002, PREC=3")
dbLoadRecords("../../db/asynRecord.db","P=$(sys),R={$(dev)}Asyn,ADDR=1,PORT=P0,IMAX=128,OMAX=128")
dbLoadRecords("../../db/Keithley2182A.db","SYS=$(sys),DEV=$(dev),PORT=KEITHLEY1")
dbLoadRecords("../../db/asynRecord.db","P=$(sys),R={$(dev)-Keithley}Asyn,ADDR=1,PORT=KEITHLEY1,IMAX=128,OMAX=128")

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
