del ..\belt_control_link.bin
fsutil  file createnew ..\belt_control_link.bin 16384
..\binHEBING\cat ..\belt_control_app.bin >>..\belt_control_link.bin
..\binHEBING\hbin ..\binHEBING\STM32F4xx_IAP.bin ..\belt_control_link.bin