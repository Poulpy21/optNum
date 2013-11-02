
CC=g++
CFLAGS= -W -Wall -Wextra -pedantic -std=c99

CXX=g++
CXXFLAGS= -W -Wall -Wextra -pedantic -std=c++11

AS = nasm
ASFLAGS= -f elf64

#LDFLAGS= -lGL -lGLU -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi
LDFLAGS = -lblitz -lplplotcxxd -lgsl -lgslcblas
LDPOSTFLAGS= 

DEBUGFLAGS= -g -O0
PROFILINGFLAGS= -O3 -pg
RELEASEFLAGS= -O3

SRCDIR = src/
OBJDIR = obj/

TARGET = main

EXT = c C cc cpp s S asm
SRC = $(notdir $(wildcard $(addprefix $(SRCDIR)*., $(EXT))))
OBJ = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(SRC))))


all: $(TARGET)

debug: CFLAGS += $(DEBUGFLAGS)
debug: CXXFLAGS += $(DEBUGFLAGS) 
debug: $(TARGET)

profile: CFLAGS += $(PROFILINGFLAGS)
profile: CXXFLAGS += $(PROFILINGFLAGS)
profile: $(TARGET)

release: CFLAGS += $(RELEASEFLAGS)
release: CXXFLAGS += $(RELEASEFLAGS)
release: $(TARGET)

$(TARGET): $(OBJ)
	@echo
	@echo
	$(CXX) $^ $(LDFLAGS) -o $@ $(LDPOSTFLAGS) $(CXXFLAGS) 
	@echo


$(OBJDIR)%.o : $(SRCDIR)%.c
	@echo
	$(CC) -o $@ -c $^ $(CFLAGS)

$(OBJDIR)%.o : $(SRCDIR)%.C 
	@echo
	$(CXX) $(INCLUDE) -o $@ -c $^ $(CXXFLAGS)
$(OBJDIR)%.o : $(SRCDIR)%.cc 
	@echo
	$(CXX) $(INCLUDE) -o $@ -c $^ $(CXXFLAGS)
$(OBJDIR)%.o : $(SRCDIR)%.cpp 
	@echo
	$(CXX) $(INCLUDE) -o $@ -c $^ $(CXXFLAGS) 

$(OBJDIR)%.o : $(SRCDIR)%.s
	@echo
	$(AS) $(INCLUDE) -o $@ $^ $(ASFLAGS)
$(OBJDIR)%.o : $(SRCDIR)%.S
	@echo
	$(AS) $(INCLUDE) -o $@ $^ $(ASFLAGS)
$(OBJDIR)%.o : $(SRCDIR)%.asm
	@echo
	$(AS) $(INCLUDE) -o $@ $^ $(ASFLAGS)



# "-" pour enlever les messages d'erreurs
# "@" pour silent

.PHONY: clean cleanall

clean:
	-@rm -rf $(OBJDIR)*.o

cleanall: clean
	-@rm -f $(TARGET) $(TARGET).out 

