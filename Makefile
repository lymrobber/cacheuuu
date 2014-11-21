OBJS := Dev_Light.o
OBJS += Dev_Switch.o
OBJS += Dev_THSensor.o
OBJS += HW_SHT1x.o


itead_IoTgo.o: $(OBJS) IoTgo.o
	$(SDK_LINKER) -r -o $@ $^
	rm -rf $^

PythonFlags := $(shell python-config --cflags --ldflags)
PythonFlags := $(subst -Wstrict-prototypes,,$(PythonFlags)) 

.PHONY: IoTgo.o
IoTgo.o: IoTgo.cpp IoTgo.h
	$(SDK_CPP_COMPILE) $(PythonFlags) $(SDK_LIB_OPTIMIZE_OPTION) -fpic -c -o $@ $< -I../../include

%.o:%.cpp
	$(SDK_CPP_COMPILE) $(SDK_LIB_OPTIMIZE_OPTION) -fpic -c -o $@ $< -I../../include
