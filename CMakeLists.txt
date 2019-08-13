cmake_minimum_required(VERSION 3.12.4)
project(otus-3-master VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})


set(CMAKE_CXX_STANDARD 17)

add_executable(otus-3-master main.cpp worstallocator.h worstvector.h)

install(TARGETS otus-3-master RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
