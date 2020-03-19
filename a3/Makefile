# uncomment the -lpng12 and -DHAVEPNG if you have the png12 libraries
# installed on Linux.
#
# uncomment the -lfreetype and -DUSE_FREETYPE is you have the
# freetype2 libraries installed on Linux

PROG = rt

OBJS =	main.o arcballWindow.o font.o scene.o sphere.o triangle.o light.o eye.o object.o \
	material.o texture.o vertex.o wavefrontobj.o wavefront.o bvh.o linalg.o \
	gpuProgram.o axes.o arrow.o bbox.o glverts.o glad/src/glad.o

LDFLAGS  = -Llib32 -lglfw -lGL -ldl # -lfreetype -lpng12
CXXFLAGS = -g -I/usr/include/freetype2 -Wall -Wno-write-strings -Wno-parentheses -Wno-unused-variable -Wno-unused-result -DLINUX # -DUSE_FREETYPE -DHAVEPNG
CXX      = g++

$(PROG):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS) $(LDFLAGS)

.C.o:
	$(CXX) $(CXXFLAGS) -c $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(PROG) $(OBJS) *~ core Makefile.bak

depend:	
	makedepend -Y *.h *.cpp

# DO NOT DELETE

arcballWindow.o: headers.h glad/include/glad/glad.h
arcballWindow.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
arrow.o: object.h linalg.h material.h texture.h headers.h
arrow.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
arrow.o: include/GLFW/glfw3.h seq.h gpuProgram.h
axes.o: linalg.h gpuProgram.h headers.h glad/include/glad/glad.h
axes.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h seq.h
bbox.o: linalg.h
bvh.o: linalg.h seq.h material.h texture.h headers.h glad/include/glad/glad.h
bvh.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h gpuProgram.h
bvh.o: bbox.h main.h scene.h object.h light.h sphere.h eye.h axes.h glverts.h
bvh.o: arrow.h rtWindow.h arcballWindow.h wavefront.h shadeMode.h
eye.o: linalg.h
glverts.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
glverts.o: include/GLFW/glfw3.h linalg.h seq.h gpuProgram.h
gpuProgram.o: headers.h glad/include/glad/glad.h
gpuProgram.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
gpuProgram.o: seq.h
headers.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
headers.o: include/GLFW/glfw3.h linalg.h
light.o: linalg.h sphere.h object.h material.h texture.h headers.h
light.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
light.o: include/GLFW/glfw3.h seq.h gpuProgram.h
main.o: seq.h scene.h linalg.h object.h material.h texture.h headers.h
main.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
main.o: include/GLFW/glfw3.h gpuProgram.h light.h sphere.h eye.h axes.h
main.o: glverts.h arrow.h rtWindow.h main.h arcballWindow.h
material.o: linalg.h texture.h headers.h glad/include/glad/glad.h
material.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h seq.h
material.o: gpuProgram.h
object.o: linalg.h material.h texture.h headers.h glad/include/glad/glad.h
object.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h seq.h
object.o: gpuProgram.h
rtWindow.o: main.h seq.h scene.h linalg.h object.h material.h texture.h
rtWindow.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
rtWindow.o: include/GLFW/glfw3.h gpuProgram.h light.h sphere.h eye.h axes.h
rtWindow.o: glverts.h arrow.h rtWindow.h arcballWindow.h
scene.o: seq.h linalg.h object.h material.h texture.h headers.h
scene.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
scene.o: include/GLFW/glfw3.h gpuProgram.h light.h sphere.h eye.h axes.h
scene.o: glverts.h arrow.h
sphere.o: object.h linalg.h material.h texture.h headers.h
sphere.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
sphere.o: include/GLFW/glfw3.h seq.h gpuProgram.h sphere.h
texture.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
texture.o: include/GLFW/glfw3.h linalg.h seq.h
triangle.o: object.h linalg.h material.h texture.h headers.h
triangle.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
triangle.o: include/GLFW/glfw3.h seq.h gpuProgram.h vertex.h
vertex.o: linalg.h
wavefront.o: headers.h glad/include/glad/glad.h
wavefront.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
wavefront.o: seq.h shadeMode.h gpuProgram.h
wavefrontobj.o: object.h linalg.h material.h texture.h headers.h
wavefrontobj.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
wavefrontobj.o: include/GLFW/glfw3.h seq.h gpuProgram.h wavefront.h
wavefrontobj.o: shadeMode.h bvh.h bbox.h main.h scene.h light.h sphere.h
wavefrontobj.o: eye.h axes.h glverts.h arrow.h rtWindow.h arcballWindow.h
arcballWindow.o: arcballWindow.h headers.h glad/include/glad/glad.h
arcballWindow.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
arrow.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
arrow.o: include/GLFW/glfw3.h linalg.h arrow.h object.h material.h texture.h
arrow.o: seq.h gpuProgram.h
axes.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
axes.o: include/GLFW/glfw3.h linalg.h axes.h gpuProgram.h seq.h
bbox.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
bbox.o: include/GLFW/glfw3.h linalg.h bbox.h glverts.h seq.h gpuProgram.h
bbox.o: main.h scene.h object.h material.h texture.h light.h sphere.h eye.h
bbox.o: axes.h arrow.h rtWindow.h arcballWindow.h
bvh.o: bvh.h linalg.h seq.h material.h texture.h headers.h
bvh.o: glad/include/glad/glad.h glad/include/KHR/khrplatform.h
bvh.o: include/GLFW/glfw3.h gpuProgram.h bbox.h main.h scene.h object.h
bvh.o: light.h sphere.h eye.h axes.h glverts.h arrow.h rtWindow.h
bvh.o: arcballWindow.h wavefront.h shadeMode.h triangle.h vertex.h
eye.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
eye.o: include/GLFW/glfw3.h linalg.h eye.h main.h seq.h scene.h object.h
eye.o: material.h texture.h gpuProgram.h light.h sphere.h axes.h glverts.h
eye.o: arrow.h rtWindow.h arcballWindow.h
font.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
font.o: include/GLFW/glfw3.h linalg.h gpuProgram.h seq.h
glverts.o: glverts.h headers.h glad/include/glad/glad.h
glverts.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h seq.h
glverts.o: gpuProgram.h
gpuProgram.o: gpuProgram.h headers.h glad/include/glad/glad.h
gpuProgram.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
gpuProgram.o: seq.h
light.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
light.o: include/GLFW/glfw3.h linalg.h light.h sphere.h object.h material.h
light.o: texture.h seq.h gpuProgram.h main.h scene.h eye.h axes.h glverts.h
light.o: arrow.h rtWindow.h arcballWindow.h
linalg.o: linalg.h
main.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
main.o: include/GLFW/glfw3.h linalg.h rtWindow.h main.h seq.h scene.h
main.o: object.h material.h texture.h gpuProgram.h light.h sphere.h eye.h
main.o: axes.h glverts.h arrow.h arcballWindow.h font.h
material.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
material.o: include/GLFW/glfw3.h linalg.h material.h texture.h seq.h
material.o: gpuProgram.h main.h scene.h object.h light.h sphere.h eye.h
material.o: axes.h glverts.h arrow.h rtWindow.h arcballWindow.h
object.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
object.o: include/GLFW/glfw3.h linalg.h object.h material.h texture.h seq.h
object.o: gpuProgram.h main.h scene.h light.h sphere.h eye.h axes.h glverts.h
object.o: arrow.h rtWindow.h arcballWindow.h
scene.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
scene.o: include/GLFW/glfw3.h linalg.h scene.h seq.h object.h material.h
scene.o: texture.h gpuProgram.h light.h sphere.h eye.h axes.h glverts.h
scene.o: arrow.h rtWindow.h main.h arcballWindow.h triangle.h vertex.h
scene.o: wavefrontobj.h wavefront.h shadeMode.h bvh.h bbox.h font.h
sphere.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
sphere.o: include/GLFW/glfw3.h linalg.h sphere.h object.h material.h
sphere.o: texture.h seq.h gpuProgram.h main.h scene.h light.h eye.h axes.h
sphere.o: glverts.h arrow.h rtWindow.h arcballWindow.h
texture.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
texture.o: include/GLFW/glfw3.h linalg.h texture.h seq.h
triangle.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
triangle.o: include/GLFW/glfw3.h linalg.h triangle.h object.h material.h
triangle.o: texture.h seq.h gpuProgram.h vertex.h main.h scene.h light.h
triangle.o: sphere.h eye.h axes.h glverts.h arrow.h rtWindow.h
triangle.o: arcballWindow.h
vertex.o: headers.h glad/include/glad/glad.h glad/include/KHR/khrplatform.h
vertex.o: include/GLFW/glfw3.h linalg.h vertex.h main.h seq.h scene.h
vertex.o: object.h material.h texture.h gpuProgram.h light.h sphere.h eye.h
vertex.o: axes.h glverts.h arrow.h rtWindow.h arcballWindow.h
wavefront.o: headers.h glad/include/glad/glad.h
wavefront.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
wavefront.o: gpuProgram.h seq.h wavefront.h shadeMode.h
wavefrontobj.o: headers.h glad/include/glad/glad.h
wavefrontobj.o: glad/include/KHR/khrplatform.h include/GLFW/glfw3.h linalg.h
wavefrontobj.o: wavefrontobj.h object.h material.h texture.h seq.h
wavefrontobj.o: gpuProgram.h wavefront.h shadeMode.h bvh.h bbox.h main.h
wavefrontobj.o: scene.h light.h sphere.h eye.h axes.h glverts.h arrow.h
wavefrontobj.o: rtWindow.h arcballWindow.h
