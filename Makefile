SRCDIR = src
SRCS := $(wildcard $(SRCDIR)/*.c)

OBJDIR = obj
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

DEPDIR = dep
DEPS := $(SRCS:$(SRCDIR)/%.c=$(DEPDIR)/%.d)

EXDIR = bin
EXE  := $(EXDIR)/genearbre

CFLAGS = -g -O2 -Wall -Wextra -Wconversion -Wsign-conversion -pthread
LDFLAGS = -pthread



.PHONY: all
all: $(EXE)


include $(DEPS)


$(EXE): $(OBJS)
	mkdir -p $(EXDIR)
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPDIR)/%.d: $(SRCDIR)/%.c
	@set -e; mkdir -p $(DEPDIR); \
		rm -f $@; \
		echo $<; \
		$(CC) -MM -MP $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		sed -i '1s/^/$(OBJDIR)\//' $@; \
		rm -f $@.$$$$



$(EXDIR):
	mkdir $@

$(DEPDIR):
	mkdir $@

$(OBJDIR):
	mkdir $@



.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)

.PHONY: mrproper
mrproper: clean
	$(RM) $(EXE)
