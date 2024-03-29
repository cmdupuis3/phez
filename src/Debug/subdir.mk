################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cpp/phez_attribute_t_api.cpp \
../cpp/phez_cnames.cpp \
../cpp/phez_context_t_api.cpp \
../cpp/phez_cwrappers.cpp \
../cpp/phez_dataset_t_api.cpp \
../cpp/phez_file_t_api.cpp \
../cpp/phez_group_t_api.cpp \
../cpp/phez_hdf5_t_api.cpp \
../cpp/phez_space_t_api.cpp \
../cpp/phez_tests.cpp

F90_WRAPPER_SRCS += \
../f90/phez_fwrappers.cpp

F90_SRCS += \
../f90/phez_f.f90 \
../f90/phez_tests_f.f90 

CPP_OBJS += \
./phez_attribute_t_api.o \
./phez_cnames.o \
./phez_context_t_api.o \
./phez_cwrappers.o \
./phez_dataset_t_api.o \
./phez_file_t_api.o \
./phez_group_t_api.o \
./phez_hdf5_t_api.o \
./phez_space_t_api.o \
./phez_tests.o

F90_OBJS += \
./phez_fwrappers.o \
./phez_f.o \
./phez_tests_f.o 

CPP_DEPS += \
./phez_attribute_t_api.d \
./phez_cnames.d \
./phez_context_t_api.d \
./phez_cwrappers.d \
./phez_dataset_t_api.d \
./phez_file_t_api.d \
./phez_group_t_api.d \
./phez_hdf5_t_api.d \
./phez_space_t_api.d \
./phez_tests.d 


# Each subdirectory must supply rules for building sources it contributes
phez_attribute_t_api.o: ../cpp/phez_attribute_t_api.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_cnames.o: ../cpp/phez_cnames.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_context_t_api.o: ../cpp/phez_context_t_api.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_cwrappers.o: ../cpp/phez_cwrappers.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_dataset_t_api.o: ../cpp/phez_dataset_t_api.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_file_t_api.o: ../cpp/phez_file_t_api.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_group_t_api.o: ../cpp/phez_group_t_api.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_hdf5_t_api.o: ../cpp/phez_hdf5_t_api.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_space_t_api.o: ../cpp/phez_space_t_api.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_tests.o: ../cpp/phez_tests.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_fwrappers.o: ../f90/phez_fwrappers.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I${HDF5_INC} -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_f.o: ../f90/phez_f.f90
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -funderscoring -O0 -g -Wall -c -fmessage-length=0 -fPIC -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_f.o: ../f90/phez_f.f90

phez_tests_f.o: ../f90/phez_tests_f.f90
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Fortran Compiler'
	gfortran -funderscoring -O0 -g -Wall -c -fmessage-length=0 -fPIC -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

phez_tests_f.o: ../f90/phez_tests_f.f90 phez_f.o





