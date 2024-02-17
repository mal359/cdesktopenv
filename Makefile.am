docsdir = $(CDE_INSTALLATION_TOP)
docs_DATA = CONTRIBUTORS COPYING copyright HISTORY README.md

MAINTAINERCLEANFILES = Makefile.in \
		configure libtool \
		config.guess \
		config.sub \
		config.log \
		config.h.in \
		install-sh

SUBDIRS = util lib programs include

if BUILD_DOCS
SUBDIRS += doc
endif

