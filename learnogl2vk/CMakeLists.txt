# Function for building single example
function(buildExample EXAMPLE_PATH)
    SET(EXAMPLE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_PATH})
    message(STATUS "Generating project file for example in ${EXAMPLE_FOLDER}")

    get_filename_component(EXAMPLE_NAME ${EXAMPLE_PATH} NAME)

    # Main
    file(GLOB SOURCE *.cpp ${BASE_HEADERS} ${EXAMPLE_FOLDER}/*.cpp)
    SET(MAIN_CPP ${EXAMPLE_FOLDER}/${EXAMPLE_NAME}.cpp)
    if(EXISTS ${EXAMPLE_FOLDER}/main.cpp)
        SET(MAIN_CPP ${EXAMPLE_FOLDER}/main.cpp)
    ENDIF()
    if(EXISTS ${EXAMPLE_FOLDER}/${EXAMPLE_NAME}.h)
        SET(MAIN_HEADER ${EXAMPLE_FOLDER}/${EXAMPLE_NAME}.h)
    ENDIF()

    # Add shaders
    set(SHADER_DIR_GLSL "../data/shaders/glsl/${EXAMPLE_PATH}")
    file(GLOB SHADERS_GLSL "${SHADER_DIR_GLSL}/*.vert" "${SHADER_DIR_GLSL}/*.frag" "${SHADER_DIR_GLSL}/*.comp" "${SHADER_DIR_GLSL}/*.geom" "${SHADER_DIR_GLSL}/*.tesc" "${SHADER_DIR_GLSL}/*.tese" "${SHADER_DIR_GLSL}/*.mesh" "${SHADER_DIR_GLSL}/*.task" "${SHADER_DIR_GLSL}/*.rgen" "${SHADER_DIR_GLSL}/*.rchit" "${SHADER_DIR_GLSL}/*.rmiss" "${SHADER_DIR_GLSL}/*.rcall")

    add_executable(${EXAMPLE_NAME} ${MAIN_CPP} ${SOURCE} ${MAIN_HEADER} ${SHADERS_GLSL} ${SHADERS_HLSL} ${README_FILES})
    target_link_libraries(${EXAMPLE_NAME} base)
    set_target_properties(${EXAMPLE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endfunction(buildExample)

# Build all examples
function(buildExamples)
    foreach(EXAMPLE ${EXAMPLES})
        buildExample(${EXAMPLE})
    endforeach(EXAMPLE)
endfunction(buildExamples)

set(EXAMPLES
  getting_started/first_triangle
  getting_started/textures
  getting_started/transformations
  lighting/basic_lighting
  lighting/materials
  lighting/lighting_maps
  lighting/light_casters
  # model_loading/mesh
  # model_loading/model
  advance/depth_testing
  advance/stencil_testing
  advance/blending
  advance/face_culling
  advance/framebuffers
  extra/scene_manager
  extra/imgui_example
)

buildExamples()
