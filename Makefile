# sets the target object file name
obj-m := driver.o
# sets the kernel source directory path
KDIR := /lib/modules/$(shell uname -r)/build
# builds the module
all:
	$(MAKE) -C $(KDIR) M=${PWD} modules
# installs the built module
install:
	$(MAKE) -C $(KDIR) M=${PWD} module_install
# cleans the built files
clean:
	$(MAKE) -C $(KDIR) M=${PWD} clean
