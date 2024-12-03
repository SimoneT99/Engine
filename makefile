CC = g++
OBJS = SimpleSceneStub.o \
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
	OpenGLErrorHandling.o \
	ThreadSafeCamera.o \
	Lense.o \
	LenseThreadSafetyProxy.o \
	CameraObject.o \
	CameraObjectThreadSafetyProxy.o

HEADERS = ./headers/
CLASSES = ./implementations/

CORE = core/
PIPELINE = pipeline/

OBJECT = object/
CAMERA = ${CORE}camera/

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

SimpleSceneStub.o : ${CLASSES}${CORE}blackboard/concreteScene/SimpleSceneStub.cpp \
					${HEADERS}${CORE}blackboard/concreteScene/SimpleSceneStub.hpp \
					${HEADERS}${CORE}blackboard/AbstractScene.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CORE}blackboard/concreteScene/SimpleSceneStub.cpp

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

#Camera system

ThreadSafeCamera.o : ${CLASSES}${CAMERA}concreteCamera/ThreadSafeCamera.cpp \
					 ${HEADERS}${CAMERA}concreteCamera/ThreadSafeCamera.hpp \
					 ${HEADERS}${CAMERA}AbstractCamera.hpp
	${CC} ${CFLAGS} -c ${CLASSES}${CAMERA}concreteCamera/ThreadSafeCamera.cpp



Lense.o : ${CLASSES}${CAMERA}cameraLense/concreteLense/Lense.cpp \
		  ${HEADERS}${CAMERA}cameraLense/concreteLense/Lense.hpp \
		  ${HEADERS}${CAMERA}cameraLense/AbstractLense.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CAMERA}cameraLense/concreteLense/Lense.cpp

LenseThreadSafetyProxy.o : ${CLASSES}${CAMERA}cameraLense/concreteProxy/LenseThreadSafetyProxy.cpp \
		  ${HEADERS}${CAMERA}cameraLense/concreteProxy/LenseThreadSafetyProxy.hpp \
		  ${HEADERS}${CAMERA}cameraLense/AbstractLenseProxy.hpp \
		  ${HEADERS}${CAMERA}cameraLense/AbstractLense.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CAMERA}cameraLense/concreteProxy/LenseThreadSafetyProxy.cpp



CameraObject.o : ${CLASSES}${CAMERA}cameraObject/concreteCameraObject/CameraObject.cpp \
		  ${HEADERS}${CAMERA}cameraObject/concreteCameraObject/CameraObject.hpp \
		  ${HEADERS}${CAMERA}cameraObject/AbstractCameraObject.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CAMERA}cameraObject/concreteCameraObject/CameraObject.cpp

CameraObjectThreadSafetyProxy.o : ${CLASSES}${CAMERA}cameraObject/concreteProxy/CameraObjectThreadSafetyProxy.cpp \
		  ${HEADERS}${CAMERA}cameraObject/concreteProxy/CameraObjectThreadSafetyProxy.hpp \
		  ${HEADERS}${CAMERA}cameraObject/AbstractCameraObjectProxy.hpp \
		  ${HEADERS}${CAMERA}cameraObject/AbstractCameraObject.hpp
		${CC} ${CFLAGS} -c ${CLASSES}${CAMERA}cameraObject/concreteProxy/CameraObjectThreadSafetyProxy.cpp