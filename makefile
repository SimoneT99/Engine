CC = g++
OBJS = Camera.o \
	SimpleSceneStub.o \
	Transform.o \
	AbstractTransform.o \
	GlobalObject.o \
	AbstractGlobalObject.o \
	AbstractLocalObject.o \
	ObjLoader.o \
	OptimizedObjectBuilder.o \
	OptimizedObject.o \
	BaseOpenGLRenderer.o \
	OpenGLObjectInformations.o \
	OpenGLErrorHandling.o

HEADERS = ./headers/
CORE = core/
PIPELINE = pipeline/
OBJECT = object/
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

Main : ${OBJS} main.o
	   @echo "Linking main..."
	   ${CC} ${CFLAGS} ${OBJS} main.o -L${LIBS}/ -lglew32 -l:libglfw3dll.a -lopengl32 -o ${COUT}

main.o : main.cpp
		${CC} ${CFLAGS} -c main.cpp

Camera.o : ${CLASSES}${CORE}concreteCamera/Camera.cpp \
		   ${HEADERS}${CORE}concreteCamera/Camera.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}concreteCamera/Camera.cpp

SimpleSceneStub.o : ${CLASSES}${CORE}concreteScene/SimpleSceneStub.cpp \
					${HEADERS}${CORE}concreteScene/SimpleSceneStub.hpp \
					${HEADERS}${CORE}AbstractScene.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}concreteScene/SimpleSceneStub.cpp

Transform.o : ${CLASSES}${CORE}${OBJECT}transform/concreteTransform/Transform.cpp \
			  ${HEADERS}${CORE}${OBJECT}transform/concreteTransform/Transform.hpp \
			  ${HEADERS}${CORE}${OBJECT}transform/AbstractTransform.hpp \
			  AbstractTransform.o
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}transform/concreteTransform/Transform.cpp

AbstractTransform.o : ${CLASSES}${CORE}${OBJECT}transform/AbstractTransform.cpp \
				   	  ${HEADERS}${CORE}${OBJECT}transform/AbstractTransform.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}transform/AbstractTransform.cpp


GlobalObject.o : ${CLASSES}${CORE}${OBJECT}concreteGlobalObject/GlobalObject.cpp \
			  	 ${HEADERS}${CORE}${OBJECT}concreteGlobalObject/GlobalObject.hpp \
				 AbstractTransform.o \
				 AbstractLocalObject.o \
				 AbstractGlobalObject.o
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}concreteGlobalObject/GlobalObject.cpp

AbstractGlobalObject.o : ${CLASSES}${CORE}${OBJECT}AbstractGlobalObject.cpp \
			  	 		 ${HEADERS}${CORE}${OBJECT}AbstractGlobalObject.hpp \
				 		 AbstractTransform.o \
				 		 AbstractLocalObject.o
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}AbstractGlobalObject.cpp

AbstractLocalObject.o :  ${CLASSES}${CORE}${OBJECT}localObject/AbstractLocalObject.cpp \
			  	 		 ${HEADERS}${CORE}${OBJECT}localObject/AbstractLocalObject.hpp 
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}localObject/AbstractLocalObject.cpp

ObjLoader.o : ${CLASSES}${CORE}${OBJECT}localObject/loader/concreteLoader/ObjLoader.cpp \
			  ${HEADERS}${CORE}${OBJECT}localObject/loader/concreteLoader/ObjLoader.hpp \
			  ${HEADERS}${CORE}${OBJECT}localObject/loader/AbstractLocalObjectLoader.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}localObject/loader/concreteLoader/ObjLoader.cpp

#Optimized object stuff
OptimizedObjectBuilder.o : ${CLASSES}${CORE}${OBJECT}localObject/OptimizedObject/OptimizedObjectBuilder.cpp \
						   ${HEADERS}${CORE}${OBJECT}localObject/OptimizedObject/OptimizedObjectBuilder.hpp \
						   ${HEADERS}${CORE}${OBJECT}localObject/AbstractLocalObjectBuilder.hpp \
						   OptimizedObject.o
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}localObject/OptimizedObject/OptimizedObjectBuilder.cpp

OptimizedObject.o : ${CLASSES}${CORE}${OBJECT}localObject/OptimizedObject/OptimizedObject.cpp \
					${HEADERS}${CORE}${OBJECT}localObject/OptimizedObject/OptimizedObject.hpp \
					${HEADERS}${CORE}${OBJECT}localObject/AbstractLocalObject.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}${OBJECT}localObject/OptimizedObject/OptimizedObject.cpp

#Pipeline

BaseOpenGLRenderer.o : ${CLASSES}${PIPELINE}concreteRenderer/baseOpenGLRenderer/BaseOpenGLRenderer.cpp \
					   ${HEADERS}${PIPELINE}concreteRenderer/baseOpenGLRenderer/BaseOpenGLRenderer.hpp \
					   ${HEADERS}${PIPELINE}AbstractRenderer.hpp \
					   ${HEADERS}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLObjectInformations.hpp \
					   ${HEADERS}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLErrorHandling.hpp \
					   OpenGLObjectInformations.o \
					   OpenGLErrorHandling.o
		${CC} ${CFLAGS} -c ${CLASSES}${PIPELINE}concreteRenderer/baseOpenGLRenderer/BaseOpenGLRenderer.cpp

OpenGLObjectInformations.o : ${CLASSES}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLObjectInformations.cpp \
							 ${HEADERS}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLObjectInformations.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLObjectInformations.cpp 

OpenGLErrorHandling.o :  ${CLASSES}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLErrorHandling.cpp \
						 ${HEADERS}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLErrorHandling.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${PIPELINE}concreteRenderer/baseOpenGLRenderer/OpenGLErrorHandling.cpp 