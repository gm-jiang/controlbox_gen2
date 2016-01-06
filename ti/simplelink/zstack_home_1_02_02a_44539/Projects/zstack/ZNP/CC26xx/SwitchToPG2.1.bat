REM This file switches the IAR ARGVARS to point to PG2.1 TI RTOS/Driverlib for the ZStack Library Project
RMDIR configPkg /s /q
RMDIR settings /s /q
RMDIR src /s /q
RMDIR "Coordinator-Pro" /s /q
RMDIR "Coordinator-Pro_Secure" /s /q
RMDIR "Coordinator-Pro_Secure_Link_Key_Join" /s /q
RMDIR "EndDevice-Pro" /s /q
RMDIR "EndDevice-Pro_Secure" /s /q
RMDIR "EndDevice-Pro_Secure_Link_Key_Join" /s /q
RMDIR "Router-Pro" /s /q
RMDIR "Router-Pro_Secure" /s /q
RMDIR "Router-Pro_Secure_Link_Key_Join" /s /q
copy .\znp_pg2.1.custom_argvars  .\znp.custom_argvars