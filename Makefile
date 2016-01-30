TOPLEVELWD := $(dir $(lastword $(MAKEFILE_LIST)))

makerules = $(TOPLEVELWD)../xtc/makerules

include $(makerules)/toplevel.mk

include $(TOPLEVELWD)/project.mk

CWD := $(TOPLEVELWD)
$(call enter,src)

include $(makerules)/postsrc.mk

#test: $(TEST_BINARY)
#	$(print_run) LD_LIBRARY_PATH=$(dir $(LIB_BINARY)) ./$(TEST_BINARY)

# Need to add the LIB_BINARY dependency here because CMD_BINARY
# has a dependency on it only at runtime.
#run: $($(MAIN_PROGRAM)_BINARY)
#	$(print_run) LD_LIBRARY_PATH=$(dir $(LIB_BINARY)) ./$(CMD_BINARY)

#install: $(LIB_BINARY) $(CMD_BINARY)
	#$(at)echo "Installing to $(INSTALL_PREFIX)"
	#$(at)mkdir -p $(INSTALL_PREFIX)/bin
	#$(at)mkdir -p $(INSTALL_PREFIX)/lib
	#$(at)mkdir -p $(INSTALL_PREFIX)/include
	#$(at)cp $(LIBRARIES) $(INSTALL_PREFIX)/lib
	#$(at)chmod u+x $(EXECUTABLES)
	#$(at)cp $(EXECUTABLES) $(INSTALL_PREFIX)/bin
	#$(at)cp -r $(LOCATION_LIB_INT)/* $(INSTALL_PREFIX)/include

#.PHONY: test runcmd install
