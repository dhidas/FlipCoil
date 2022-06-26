TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += FlipCoil.db

DB += motor.db
DB_INSTALLS += $(EPICS_BASE)/db/pmacStatus.db
DB_INSTALLS += $(EPICS_BASE)/db/pmacStatusAxis.db
DB_INSTALLS += $(EPICS_BASE)/db/pmac_asyn_motor.db
DB_INSTALLS += $(EPICS_BASE)/db/motorstatus.db
DB_INSTALLS += $(EPICS_BASE)/db/asynRecord.db
DB_INSTALLS += $(EPICS_BASE)/db/iocAdminSoft.db
DB_INSTALLS += $(EPICS_BASE)/db/asynRecord.db
DB_INSTALLS += $(AUTOSAVE)/db/save_restoreStatus.db
DB_INSTALLS += $(RECCASTER)/db/reccaster.db
#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

