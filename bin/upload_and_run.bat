@set serial_port0=COM4


@set buad_rate=9600
@set serial_settings=N,8,1
@set srec_file=.\bin\..\000.s19
@set txt_start_address=2000

@echo off
echo ==========Start Compiling the Code==========
REM cd ..
REM make clean
REM make
REM cd bin
echo done.
echo =========Configure the Serial Port==========
REM mode %serial_port0% %buad_rate%,%serial_settings%
echo done.
echo =============Uploading the Code============= 
.\bin\HCS12SerialSend.exe %serial_port0% %buad_rate% %srec_file% %txt_start_address%
echo done.
echo ===============Finished======================
REM echo Press ENTER to continue ...
REM @pause>nul
