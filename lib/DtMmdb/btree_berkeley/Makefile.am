MAINTAINERCLEANFILES = Makefile.in

noinst_LTLIBRARIES = libbtree_berkeley.la

libbtree_berkeley_la_CFLAGS = -DMEMMOVE -I..

libbtree_berkeley_la_SOURCES =  bt_close.c bt_conv.c bt_debug.c bt_delete.c \
				bt_get.c bt_open.c bt_overflow.c bt_page.c \
				bt_put.c bt_search.c bt_seq.c bt_split.c \
				bt_stack.c bt_utils.c mktemp.c \
				realloc.c snprintf.c mpool.c db.c

if AIX
else
libbtree_berkeley_la_SOURCES += memmove.c
endif
