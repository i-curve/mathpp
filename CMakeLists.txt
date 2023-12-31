cmake_minimum_required(VERSION 3.15)

project(
  mathpp
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(MATHPP_MASTER_PROJECT OFF)
option(MATHPP_TEST "build mathpp tests" OFF) # 是否开启 test 开关

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MATHPP_MASTER_PROJECT ON)
  option(MATHPP_TEST "build mathpp tests" on)
  message(STATUS "CMake version: ${CMAKE_VERSION}")
endif()

include(GNUInstallDirs)

add_library(mathpp src/mathpp.cpp)
add_library(mathpp::mathpp ALIAS mathpp)

set_target_properties(
  mathpp PROPERTIES VERSION ${${PROJECT_NAME}_VERSION}
                    SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})

# 处理头文件
target_include_directories(
  mathpp PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# 进行库安装
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
install(
  TARGETS mathpp
  EXPORT ${TARGETS_EXPORT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION include
  FRAMEWORK DESTINATION ".")

# 添加后续使用 cmake 导入的相关配置
include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME})

install(EXPORT ${TARGETS_EXPORT_NAME}
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

# 开启测试
if(MATHPP_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
