#
# **************************************************************
# *                                                            *
# * Author: sunbin (2025)                                      *
# * URL: https://ftp.gnu.org/pub/gnu/global/				   *
# *                                                            *
# * Copyright notice:                                          *
# * Free use of this C++ Makefile template is permitted under  *
# * the guidelines and in accordance with the the MIT License  *
# * http://www.opensource.org/licenses/MIT                     *
# *                                                            *
# **************************************************************
#

TOPDIR := $(shell /bin/pwd)
resource_agents_src_dir = $(TOPDIR)

build_dir = $(TOPDIR)/build
resource_agents_dir_name = resource-agents-4.15.1


all: build_resource_agents

build_resource_agents:
	@(if [ -d $(build_dir) ]; then rm -rf $(build_dir); fi)
	@(mkdir -p $(build_dir))
	@(mkdir -p $(build_dir)/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS})
	@echo "---------- copy resource_agents files ----------"
	@(cd $(build_dir)/SOURCES; \
		cp -a $(resource_agents_src_dir)/resource-agents-4.15.1 $(resource_agents_dir_name); \
		tar -zcvf $(resource_agents_dir_name).tar.gz $(resource_agents_dir_name); rm -rf $(resource_agents_dir_name); )

	@echo "---------- copy spec ----------"
	@(cp -af $(resource_agents_src_dir)/resource-agents.spec $(build_dir)/SPECS)
	@echo "---------- build resource_agents ----------"
	@(rpmbuild -ba --define="_topdir $(build_dir)" $(build_dir)/SPECS/resource-agents.spec)

install:
	@(rpm -ivh $(build_dir)/RPMS/x86_64/resource-agents-4.15.1-1.x86_64.rpm --force)

clean:
	-rm -rf $(build_dir)
