PythonFlags := $(shell python-config --cflags --ldflags)
PythonFlags := $(subst -Wstrict-prototypes,,$(PythonFlags)) 

libiteadcpp.so: *.cpp ../../include/*.h
	$(SDK_CPP_COMPILE) $(SDK_LIB_OPTION) $(PythonFlags) -fpic -shared -o $@ *.cpp -I../../include
