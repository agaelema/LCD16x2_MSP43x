################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lcd16x2_msp43x.obj: ../lcd16x2_msp43x.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/LCD 16x2 - FR2433 - driverlib v2.91" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/LCD 16x2 - FR2433 - driverlib v2.91/driverlib/MSP430FR2xx_4xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/include" --advice:power="none" --advice:hw_config=all --define=DEPRECATED --define=__MSP430FR2433__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="lcd16x2_msp43x.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/LCD 16x2 - FR2433 - driverlib v2.91" --include_path="C:/Users/Embedded/Dropbox/- uC/MSP430/Workspace CCS 7.2/LCD 16x2 - FR2433 - driverlib v2.91/driverlib/MSP430FR2xx_4xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/include" --advice:power="none" --advice:hw_config=all --define=DEPRECATED --define=__MSP430FR2433__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


