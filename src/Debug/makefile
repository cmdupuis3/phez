

WITH_FORTRAN="false"

HDF5_PATH = /opt/hdf5/1.10.1/GNU

HDF5_LIB = ${HDF5_PATH}/lib
HDF5_INC = ${HDF5_PATH}/include


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: cpp fortran

cpp: libphez.so
fortran: libphez_fortran.so

# Tool invocations
libphez.so: $(CPP_OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L${HDF5_LIB} -shared -o "libphez.so" $(CPP_OBJS) $(USER_OBJS) $(CPP_LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libphez_fortran.so: $(F90_OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Fortran Linker'
	gfortran -L${HDF5_LIB} -L. -shared -o "libphez_fortran.so" $(F90_OBJS) $(USER_OBJS) $(F90_LIBS)
	@echo 'Finished building target: $@'
	@echo ' '



# Other Targets
clean:
	-$(RM) $(LIBRARIES)$(CC_DEPS)$(C++_DEPS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_OBJS)$(F90_OBJS)$(CPP_DEPS)$(C_DEPS) libphez.so libphez_fortran.so
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
