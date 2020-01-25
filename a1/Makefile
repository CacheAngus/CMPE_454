# This Makefile works only for Linux.

LDFLAGS  = -Llib -lglfw -lGL -ldl
CXXFLAGS = -g -Wall -Wno-write-strings -Wno-parentheses -DLINUX
CXX = g++

PROG = missile
OBJS = main.o state.o linalg.o gpuProgram.o glad/src/glad.o 

.C.o:
	$(CXX) $(CXXFLAGS) -c $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

all:	$(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS) $(LDFLAGS)

clean:
	rm -f *~ $(OBJS) $(PROG)

depend:	
	makedepend -Y *.h *.cpp

# DO NOT DELETE

buildings.o: headers.h glad/include/glad/glad.h
buildings.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
buildings.o: gpuProgram.h
circle.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
circle.o: include/GLFW/glfw3.h linalg.h gpuProgram.h
city.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
city.o: include/GLFW/glfw3.h linalg.h gpuProgram.h buildings.h
gpuProgram.o: headers.h glad/include/glad/glad.h
gpuProgram.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
headers.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
headers.o: include/GLFW/glfw3.h linalg.h
missile.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
missile.o: include/GLFW/glfw3.h linalg.h gpuProgram.h
seq.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
seq.o: include/GLFW/glfw3.h linalg.h
silo.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
silo.o: include/GLFW/glfw3.h linalg.h gpuProgram.h buildings.h
state.o: gpuProgram.h headers.h glad/include/glad/glad.h
state.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h seq.h
state.o: missile.h silo.h buildings.h city.h circle.h
gpuProgram.o: gpuProgram.h headers.h glad/include/glad/glad.h
gpuProgram.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
linalg.o: linalg.h
main.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
main.o: include/GLFW/glfw3.h linalg.h state.h gpuProgram.h seq.h missile.h
main.o: silo.h buildings.h city.h circle.h
state.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
state.o: include/GLFW/glfw3.h linalg.h state.h gpuProgram.h seq.h missile.h
state.o: silo.h buildings.h city.h circle.h
