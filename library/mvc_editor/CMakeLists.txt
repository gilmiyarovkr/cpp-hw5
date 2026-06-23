add_library(mvc_editor_lib STATIC
   include/IPrimitive.h
   include/Primitive.h
   Primitive.cpp
   include/SceneModel.h

   include/IDocIO.h
   include/JsonDoc.h
   JsonDoc.cpp

   include/Controller.h
   Controller.cpp
)

target_link_libraries(mvc_editor_lib INTERFACE compiler_flags)

target_include_directories(mvc_editor_lib INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>
)
