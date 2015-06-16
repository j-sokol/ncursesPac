# PACMAN MAKEFILE
# make all        Builds the package + documentation
# make run        Builds and runs the program
# make clean      Cleans results of building process
# make doc        Generates the documentation with doxygen
# make docclean   Removes the documentation



# General Info
PACKAGE = npac
VERSION = 1
DATE    = $(shell date "+%b%Y")


# Misc stuff
PNGDIR     = $(DATAROOTDIR)/icons/hicolor
XPMDIR     = $(DATAROOTDIR)/pixmaps
DESKTOPDIR = $(DATAROOTDIR)/applications
LEVELDIR   = $(DATAROOTDIR)/games/nsnake/levels

# Things for the man page

# Build info
EXE         = $(PACKAGE)
CDEBUG      = -O0
CXXFLAGS    = $(CDEBUG) -c -g -Wno-reorder -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb $(CFLAGS_PLATFORM) # -Wall -Wextra
LDFLAGS     = -lmenu -lncurses $(LDFLAGS_PLATFORM)
INCLUDESDIR = -I"src/"
LIBSDIR     =

# Project source files
CXXFILES = $(shell find src -type f -name '*.cpp')
OBJECTS  = $(CXXFILES:.cpp=.o)


DEFINES = -DVERSION=\""$(VERSION)"\"                  \
          -DPACKAGE=\""$(PACKAGE)"\"                  \
          -DDATE=\""$(DATE)"\"                        \
          -DSYSTEM_LEVEL_DIR=\""$(LEVELDIR)"\"


# Verbose mode check:
#V = 1;
ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

# Make targets
all:compile doc
	# Build successful!

compile: $(EXE) 
	# Build successful!

$(EXE): $(OBJECTS) $(ENGINE_OBJECTS) $(COMMANDER_OBJECTS)
	# Linking...
	$(MUTE)$(CXX) $(OBJECTS) $(ENGINE_OBJECTS) $(COMMANDER_OBJECTS) -o $(EXE) $(LIBSDIR) $(LDFLAGS)

src/%.o: src/%.cpp
	# Compiling $<...
	$(MUTE)$(CXX) $(CXXFLAGS) $(CDEBUG) $< -c -o $@ $(DEFINES) $(INCLUDESDIR)


run: compile 
	# Running...
	$(MUTE)./$(EXE)

doc:
	# Generating documentation...
	$(MUTE)doxygen Doxyfile

docclean:
	# Cleaning documentation...
	-$(MUTE)rm $(VTAG) -rf doc

clean: docclean
	# Cleaning object files...
	$(MUTE)rm $(VTAG) -f $(OBJECTS)
	$(MUTE)rm $(VTAG) -f $(EXE)

clean-all: clean
	# Cleaning object files...
	$(MUTE)rm $(VTAG) -f $(ENGINE_OBJECTS) $(COMMANDER_OBJECTS)

