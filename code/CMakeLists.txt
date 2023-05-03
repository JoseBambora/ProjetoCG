cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(projetoexec)

# set(OpenGL_GL_PREFERENCE LEGACY)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(engine src/Execs/Engine.cpp src/TinyXML/tinyxml2.cpp src/Classes/EngineClasses/Cpp/World.cpp src/Classes/EngineClasses/Header/World.h src/Classes/EngineClasses/Cpp/Camera.cpp src/Classes/EngineClasses/Header/Camera.h src/Classes/EngineClasses/Cpp/Group.cpp src/Classes/EngineClasses/Header/Group.h src/Classes/Figures/Cpp/Cone.cpp src/Classes/Figures/Header/Cone.h src/Classes/Figures/Cpp/Box.cpp src/Classes/Figures/Header/Box.h src/Classes/Figures/Cpp/Sphere.cpp src/Classes/Figures/Header/Sphere.h src/Classes/Figures/Cpp/Plane.cpp src/Classes/Figures/Header/Plane.h src/Classes/Figures/Cpp/Figure.cpp src/Classes/Figures/Header/Figure.h src/Classes/Figures/Cpp/Basics.cpp src/Classes/Figures/Header/Basics.h src/Classes/Figures/Cpp/Donut.cpp src/Classes/Figures/Header/Donut.h src/Classes/Figures/Cpp/Cylinder.cpp src/Classes/Figures/Header/Cylinder.h src/Classes/EngineClasses/Cpp/ListTree.cpp src/Classes/EngineClasses/Header/ListTree.h src/Classes/Transformations/Cpp/Rotate.cpp src/Classes/Transformations/Header/Rotate.h src/Classes/Transformations/Cpp/Translate.cpp src/Classes/Transformations/Header/Translate.h src/Classes/Transformations/Cpp/Scale.cpp src/Classes/Transformations/Header/Scale.h src/Classes/Transformations/Cpp/Transformation.cpp src/Classes/Transformations/Header/Transformation.h src/Classes/Transformations/Cpp/Transform.cpp src/Classes/Transformations/Header/Transform.h src/Classes/EngineClasses/Cpp/DefaultNode.cpp src/Classes/EngineClasses/Header/DefaultNode.h src/Classes/Transformations/Header/CatmullRom.h src/Classes/Transformations/Cpp/CatmullRom.cpp src/Classes/EngineClasses/Header/MatrixOperations.h src/Classes/EngineClasses/Cpp/MatrixOperations.cpp src/Classes/Transformations/Header/CatmullRom.h src/Classes/Figures/Header/Bezier.h src/Classes/Figures/Cpp/Bezier.cpp)
add_executable(generator src/Execs/Generator.cpp src/Classes/Figures/Cpp/Cone.cpp src/Classes/Figures/Header/Cone.h src/Classes/Figures/Cpp/Box.cpp src/Classes/Figures/Header/Box.h src/Classes/Figures/Cpp/Sphere.cpp src/Classes/Figures/Header/Sphere.h src/Classes/Figures/Cpp/Plane.cpp src/Classes/Figures/Header/Plane.h src/Classes/Figures/Cpp/Figure.cpp src/Classes/Figures/Header/Figure.h src/Classes/Figures/Cpp/Basics.cpp src/Classes/Figures/Header/Basics.h src/Classes/Figures/Cpp/Donut.cpp src/Classes/Figures/Header/Donut.h src/Classes/Figures/Cpp/Cylinder.cpp src/Classes/Figures/Header/Cylinder.h src/Classes/Figures/Header/Bezier.h src/Classes/Figures/Cpp/Bezier.cpp src/Classes/EngineClasses/Header/MatrixOperations.h src/Classes/EngineClasses/Cpp/MatrixOperations.cpp)
add_executable(teste src/TinyXML/tinyxml2.cpp src/Classes/EngineClasses/Cpp/World.cpp src/Classes/EngineClasses/Header/World.h src/Classes/EngineClasses/Cpp/Camera.cpp src/Classes/EngineClasses/Header/Camera.h src/Classes/EngineClasses/Cpp/Group.cpp src/Classes/EngineClasses/Header/Group.h src/Classes/Figures/Cpp/Cone.cpp src/Classes/Figures/Header/Cone.h src/Classes/Figures/Cpp/Box.cpp src/Classes/Figures/Header/Box.h src/Classes/Figures/Cpp/Sphere.cpp src/Classes/Figures/Header/Sphere.h src/Classes/Figures/Cpp/Plane.cpp src/Classes/Figures/Header/Plane.h src/Classes/Figures/Cpp/Figure.cpp src/Classes/Figures/Header/Figure.h src/Classes/Figures/Cpp/Basics.cpp src/Classes/Figures/Header/Basics.h src/Classes/Figures/Cpp/Donut.cpp src/Classes/Figures/Header/Donut.h src/Classes/Figures/Cpp/Cylinder.cpp src/Classes/Figures/Header/Cylinder.h src/Classes/EngineClasses/Cpp/ListTree.cpp src/Classes/EngineClasses/Header/ListTree.h src/Classes/Transformations/Cpp/Rotate.cpp src/Classes/Transformations/Header/Rotate.h src/Classes/Transformations/Cpp/Translate.cpp src/Classes/Transformations/Header/Translate.h src/Classes/Transformations/Cpp/Scale.cpp src/Classes/Transformations/Header/Scale.h src/Classes/Transformations/Cpp/Transformation.cpp src/Classes/Transformations/Header/Transformation.h src/Classes/Transformations/Cpp/Transform.cpp src/Classes/Transformations/Header/Transform.h src/Classes/EngineClasses/Cpp/DefaultNode.cpp src/Classes/EngineClasses/Header/DefaultNode.h src/Classes/Transformations/Header/CatmullRom.h src/Classes/Transformations/Cpp/CatmullRom.cpp src/Classes/EngineClasses/Header/MatrixOperations.h src/Classes/EngineClasses/Cpp/MatrixOperations.cpp src/Classes/Transformations/Header/CatmullRom.h src/Classes/Figures/Header/Bezier.h src/Classes/Figures/Cpp/Bezier.cpp src/Execs/main.cpp)
add_executable(generatexml src/Execs/CreateSolarSystem.cpp src/TinyXML/tinyxml2.cpp)


if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")

    if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
        message(ERROR ": GLEW not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")

    if (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")
        message(ERROR ": DevIL not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")

    include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
            ${TOOLKITS_FOLDER}/glut/glut32.lib
            ${TOOLKITS_FOLDER}/devil/devIL.lib
            ${TOOLKITS_FOLDER}/glew/glew32.lib )

    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
            AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/devil/devil.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
            AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else (WIN32) #Linux and Mac

    find_package(OpenGL REQUIRED)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})

    if(NOT OPENGL_FOUND)
        message(ERROR " OPENGL not found!")
    endif(NOT OPENGL_FOUND)
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
    set(OpenGL_GL_PREFERENCE "GLVND")
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})

    target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GLEW::GLEW)
    target_link_libraries(teste ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GLEW::GLEW)
    target_link_libraries(generator ${OPENGL_LIBRARIES}  ${GLUT_LIBRARIES} GLEW::GLEW)

    if(NOT GLUT_FOUND)
        message(ERROR ": GLUT not found!")
    endif(NOT GLUT_FOUND)

endif(WIN32)









