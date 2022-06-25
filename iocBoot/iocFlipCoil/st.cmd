#!../../bin/linux-x86_64/FlipCoil

#- You may have to change FlipCoil to something else
#- everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase("../../dbd/FlipCoil.dbd",0,0)
FlipCoil_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/FlipCoil.db","user=dhidas")

iocInit()

## Start any sequence programs
#seq sncFlipCoil,"user=dhidas"
