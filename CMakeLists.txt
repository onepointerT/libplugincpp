#
# Copyright 2025 The OnePointer Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required( VERSION 3.22 )

project( libplugin CXX )

set( PROJECT_NAME "libplugin" )
set( PROJECT_DESCRIPTION "A dynamic library for secure plugins for your code with C++ from OnePointer UG." )
set( PROJECT_VERSION "0.0.1" )

set( CMAKE_CXX_STANDARD 26 )

include_directories( ${PROJECT_SOURCE_DIR} )

# add_subdirectory( ${PROJECT_SOURCE_DIR}/plugin/api )

file( GLOB ONEPTR_PLUGIN_SRC ${PROJECT_SOURCE_DIR}/plugin/*.cpp )
add_library( oneptr_plugin ${ONEPTR_PLUGIN_SRC} )
# target_link_libraries( oneptr_plugin absl_plugin )
