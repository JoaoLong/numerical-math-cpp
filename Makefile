#definitions

CXX := g++ 
CXXFLAGS := $(shell root-config --cflags) -fPIC

UNAME := $(shell uname)


BINDIR := bin
LIBDIR := lib

C_EXT := C
CPP_EXT := cpp


SRCS_CPP := $(wildcard src/*.cpp) 
SRCS_C := $(wildcard src/*.C)
OBJS := $(patsubst %.cpp, bin/%.o, $(notdir $(SRCS_CPP)) ) $(patsubst %.C, bin/%.o, $(notdir $(SRCS_C)) )
EXES := $(patsubst %.cpp, bin/%.exe, $(notdir $(wildcard main/*.cpp)) ) $(patsubst %.C, bin/%.exe, $(notdir $(wildcard main/*.C)) )

ifeq ($(UNAME),Linux)
  EIGEN_INC := $(shell pkg-config --cflags eigen3)
else
  EIGEN_INC := -I /usr/local/Cellar/eigen/3.4.0_1/include/eigen3
endif	

ROOT_LIB := $(shell root-config --libs)

.PRECIOUS: $(OBJS)

#rules

VPATH = main:src

main: $(EXES)

lib: $(LIBDIR)/libFC.a

lib/%.a: $(OBJS)
	@echo making lib...[$^]
	ar ruv $@ $^
	ranlib $@

$(BINDIR)/%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a
	@echo executable... [$@]
	$(CXX) $(CXXFLAGS) -o $@ $< -I src $(EIGEN_INC) -L $(LIBDIR) -l FC $(ROOT_LIB)

$(BINDIR)/%.o: %.$(C_EXT)
	@echo compiling $< [$@]
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I src $(EIGEN_INC)
	
$(BINDIR)/%.o: %.$(CPP_EXT)
	@echo compiling $< [$@]
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I src $(EIGEN_INC)

clean:
	@echo cleaning...
	rm -f $(wildcard $(BINDIR)/*) $(wildcard $(LIBDIR)/*)
dump:
	@echo dump... $(CXX) 
	@echo dump... $(SRCS_CPP) 
	@echo dump... $(SRCS_C)
	@echo dump... $(OBJS) 
	@echo dump... $(EXES) 

