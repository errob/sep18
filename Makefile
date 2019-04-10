SUBMISSION = sepcity
BUILDDIR   = build
EXECUTABLE = $(SUBMISSION)
SOURCES    = $(wildcard *.cpp)
ZIP_SOURCES = $(filter-out Interface.cpp Interface.h, $(wildcard *.cpp *.h))
D1_SOURCES = Field.cpp Field.h Game.cpp Game.h
OBJECTS    = $(patsubst %,$(BUILDDIR)/%,${SOURCES:.cpp=.o})
CXX        = g++
CCFLAGS    = -Wall -g -c -std=c++14 -o
LDFLAGS    =
DEFINE     = -DUSE_COLOR

ifeq ($(OS),Windows_NT)
else
	LDLIBS += -ldl
endif

#-------------------------------------------------------------------------------
#make executable
all: builddir $(EXECUTABLE)
ifeq ($(OS),Windows_NT)
	if exist Interface.cpp copy /b Interface.cpp +,,
else
	touch Interface.cpp
endif

#create build directory
builddir:
ifeq ($(OS),Windows_NT)
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
else
	mkdir -p $(BUILDDIR)
endif

#compile objects
$(BUILDDIR)/%.o: %.cpp
	$(CXX) $(CCFLAGS) $@ $< -MMD -MF ./$@.d $(DEFINE)

#link Objects
$(EXECUTABLE) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

#make readline
readline:	LDLIBS += -lreadline
readline: DEFINE += -DUSE_READLINE
readline: all

#make clean
clean:
ifeq ($(OS),Windows_NT)
	del /Q .\$(BUILDDIR)\*.o
	del /Q .\$(BUILDDIR)\*.o.d
	del /Q $(EXECUTABLE).exe
	del /Q $(EXECUTABLE).zip
else
	rm -rf ./$(BUILDDIR)
	rm -f $(EXECUTABLE)
	rm -f $(EXECUTABLE).zip
endif

#make valgrind
valgrind:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=lib/lib.supp ./$(EXECUTABLE) test.city

#make webinterface
webinterface: all
ifeq ($(OS),Windows_NT)
	cmd /c start sep.city
else
	-xdg-open sep.city
endif
	./sepcity test.city use_web

#make submission zip archive for PALME
submission:
ifeq ($(OS),Windows_NT)
	del /Q $(SUBMISSION).zip
else
	rm -f $(SUBMISSION).zip
endif
	zip $(SUBMISSION).zip $(ZIP_SOURCES)

submission_d1:
ifeq ($(OS),Windows_NT)
	del /Q $(SUBMISSION).zip
else
	rm -f $(SUBMISSION).zip
endif
	zip $(SUBMISSION).zip $(D1_SOURCES)

#make release
release: DEFINE += -DRELEASE
release: all

gitinspector:
	gitinspector -F html --grading -l -w -m -r -T -x file:lib -x file:gui > git.html
	-xdg-open git.html

.PHONY: clean submission submission_d1

#The dependencies:
-include $(wildcard $(BUILDDIR)/*.d)
