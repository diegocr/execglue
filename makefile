
CC	=	ppc-amigaos-gcc
CPU	=	-mcpu=powerpc -mmultiple
OPTIM	=	-O2 #-fomit-frame-pointer -funroll-loops
DEFS	=	-D__NOLIBBASE__
WARNS	=	-W -Wall -Winline
CFLAGS	=	$(CPU) $(OPTIM) -I. -Iinclude/priv -Iinclude $(DEFS) $(WARNS)
LINK	=	$(CC) -nostdlib $(CPU) $(OPTIM)
LDFLAGS	=	-Wl,-Map,$@.map,--cref
LIBS	=	
SYS	=	
TARGET	=	execglue.library$(SYS)

OBJDIR	=	_objs$(SYS)
OBJS	=				\
	$(OBJDIR)/libinit.o		\
	$(OBJDIR)/execglue_68k.o	\
	$(OBJDIR)/getcpuinfo.o

all: $(OBJDIR) $(TARGET)

$(OBJDIR)/%.o: %.c
	@echo Making $@
	$(CC) $(CFLAGS) -o $@ -c $^

$(TARGET): $(OBJS)
	$(LINK) -o $@ $^ $(LDFLAGS) $(LIBS)

$(OBJDIR):
	@mkdir -p $@

clean:
	rm -f _objs*/*.o

test: test.c
	m68k-amigaos-gcc -noixemul -m68020-60 -O2 -W -Wall test.c -Iinclude -s -o test

#.SILENT:
