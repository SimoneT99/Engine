CC = g++
OBJS = ObjLoader.o OptimizedObjectBuilder.o OptimizedObject.o AbstractObject.o GlobalObject.o Transform.o AbstractTransform.o Camera.o Renderer.o error.o
HEADERS = ./headers/
CLASSES = ./implementations/
OUT = Program.exe
OUT_DEBUG = Program_DB.exe
INCLUDE = ./include
FLAGS = -I${HEADERS} -I${INCLUDE}
DEBUG_FLAGS = -g -O0
LIBS = ./lib

#SUBPATHS
OPTIMIZED_OBJECT = object/OptimizedObject/
CONCRETE_LOADER = object/loader/concreteLoaders/


all : release_setup
debug : debug_setup

debug_setup : CFLAGS = -g -Og $(FLAGS)
debug_setup : COUT = $(OUT_DEBUG)
debug_setup : Main

release_setup : CFLAGS = $(FLAGS)
release_setup : COUT = $(OUT)
release_setup : Main

clean : 
	del $(OBJS) main.o

Main : ${OBJS} main.o ${HEADERS}${OPTIMIZED_OBJECT}OptimizedObjectBuilder.hpp \
	   ${HEADERS}${CONCRETE_LOADER}ObjLoader.hpp"
	   @echo "Linking main..."
	   ${CC} ${CFLAGS} ${OBJS} main.o -L${LIBS}/ -lglew32 -l:libglfw3dll.a -lopengl32 -o ${COUT}

main.o : main.cpp Camera.o Renderer.o
		${CC} ${CFLAGS} -c main.cpp

Renderer.o : ${CLASSES}pipeline/Renderer.cpp \
			 ${HEADERS}pipeline/Renderer.hpp \
			 Camera.o \
			 error.o
		${CC} ${CFLAGS} -c ${CLASSES}pipeline/Renderer.cpp

error.o : ${CLASSES}pipeline/error.cpp \
		  ${HEADERS}pipeline/error.hpp 
		${CC} ${CFLAGS} -c ${CLASSES}pipeline/error.cpp

Camera.o : ${CLASSES}pipeline/Camera.cpp \
		   ${HEADERS}pipeline/Camera.hpp 
		${CC} ${CFLAGS} -c ${CLASSES}pipeline/Camera.cpp


ObjLoader.o : ${CLASSES}${CONCRETE_LOADER}ObjLoader.cpp \
			  ${HEADERS}${CONCRETE_LOADER}ObjLoader.hpp \
			  ${HEADERS}object/loader/AbstractLoader.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CONCRETE_LOADER}ObjLoader.cpp

OptimizedObjectBuilder.o : ${CLASSES}${OPTIMIZED_OBJECT}OptimizedObjectBuilder.cpp \
						   ${HEADERS}${OPTIMIZED_OBJECT}OptimizedObjectBuilder.hpp \
						   ${HEADERS}object/AbstractObjectBuilder.hpp \
						   OptimizedObject.o

		${CC} ${CFLAGS} -c ${CLASSES}${OPTIMIZED_OBJECT}OptimizedObjectbuilder.cpp

OptimizedObject.o : ${CLASSES}${OPTIMIZED_OBJECT}/OptimizedObject.cpp \
					${HEADERS}${OPTIMIZED_OBJECT}/OptimizedObject.hpp \
					${HEADERS}object/AbstractObject.hpp \
					AbstractObject.o
		${CC} ${CFLAGS} -c ${CLASSES}${OPTIMIZED_OBJECT}OptimizedObject.cpp

AbstractObject.o : ${CLASSES}object/AbstractObject.cpp \
				   ${HEADERS}object/AbstractObject.hpp
		${CC} ${CFLAGS} -c ${CLASSES}object/AbstractObject.cpp


Transform.o : ${CLASSES}transform/concreteTransforms/Transform.cpp \
			  ${HEADERS}transform/concreteTransforms/Transform.hpp \
			  ${HEADERS}transform/AbstractTransform.hpp \
			  AbstractTransform.o
		${CC} ${CFLAGS} -c ${CLASSES}transform/concreteTransforms/Transform.cpp

AbstractTransform.o : ${CLASSES}transform/AbstractTransform.cpp \
				   ${HEADERS}transform/AbstractTransform.hpp
		${CC} ${CFLAGS} -c ${CLASSES}transform/AbstractTransform.cpp

GlobalObject.o : ${CLASSES}GlobalObject.cpp \
			  	 ${HEADERS}GlobalObject.hpp \
				 AbstractTransform.o \
				 AbstractObject.o
		${CC} ${CFLAGS} -c ${CLASSES}GlobalObject.cpp
