#///////////////////////////////////////////////////////////////////////////////
#//
#//  Copyright (c) 2009, Michael A. Jackson. BlueQuartz Software
#//  All rights reserved.
#//  BSD License: http://www.opensource.org/licenses/bsd-license.html
#//
#///////////////////////////////////////////////////////////////////////////////


# ------------------------------------------------------------------------------ 
# This CMake code sets up for CPack to be used to generate native installers
# ------------------------------------------------------------------------------
if (MSVC)
    # Skip the install rules, we only want to gather a list of the system libraries
    SET(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP 1)
    #SET(CMAKE_INSTALL_DEBUG_LIBRARIES OFF)
    
    # Gather the list of system level runtime libraries
    INCLUDE (InstallRequiredSystemLibraries)
    
    # Our own Install rule for Release builds of the MSVC runtime libs
    IF (CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
      INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION ./
        PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ
        COMPONENT Applications
        CONFIGURATIONS Release)
    ENDIF (CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
endif()

# Add a short ReadMe file for OS X that warns of moving the applications
if (APPLE)
install(FILES ${PROJECT_RESOURCES_DIR}/CPack/OS_X_ReadMe.txt DESTINATION .)
endif()

# Get a shorter version number:
set(TomoEngine_VERSION_SHORT "${TomoEngine_VER_MAJOR}.${TomoEngine_VER_MINOR}")


SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "EIM Tomography Tools")
SET(CPACK_PACKAGE_VENDOR "BlueQuartz Software, Michael A. Jackson")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_BINARY_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_BINARY_DIR}/License.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${TomoEngine_VER_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${TomoEngine_VER_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${TomoEngine_VER_PATCH})
SET(CPACK_PACKAGE_VERSION ${TomoEngine_VERSION})
#SET(CPACK_COMPONENTS_ALL Applications Headers)
#set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Applications")
#set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION  "The DREAM3D Software Tools Suite")
#set(CPACK_COMPONENT_APPLICATIONS_REQUIRED 1)
#set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Headers")
#set(CPACK_COMPONENT_HEADERS_DESCRIPTION  "Development Header Files")
#set(CPACK_COMPONENT_HEADERS_REQUIRED 0)
#set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
#set(CPACK_COMPONENT_RUNTIME_DESCRIPTION  "Runtime Libraries")
#set(CPACK_COMPONENT_RUNTIME_REQUIRED 1)

set(CPACK_PACKAGE_EXECUTABLES
    TomoGui TomoGui)
set(UPLOAD_FILE_NAME "")

IF (APPLE)
    set(CPACK_PACKAGE_FILE_NAME "TomoEngine-${TomoEngine_VERSION_SHORT}-OSX")
    # This ASSUMES we are creating a tar.gz package. If you change that below to
    # anything else then you need to update this.
    set (UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.tar.gz)
elseif(WIN32)
	if ( "${CMAKE_SIZEOF_VOID_P}" EQUAL "8" )
		set(CPACK_PACKAGE_FILE_NAME "TomoGui-${TomoEngine_VERSION_SHORT}-Win64")
		set (UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.zip)
	elseif( "${CMAKE_SIZEOF_VOID_P}" EQUAL "4" )
		set(CPACK_PACKAGE_FILE_NAME "TomoGui-${TomoEngine_VERSION_SHORT}-Win32")
		set (UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.zip)
	else()
	    set(CPACK_PACKAGE_FILE_NAME "TomoGui-${TomoEngine_VERSION_SHORT}-Unknown")
	    set (UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.zip)
    endif()
else()
  set(CPACK_PACKAGE_FILE_NAME "TomoGui-${TomoEngine_VERSION_SHORT}-${CMAKE_SYSTEM_NAME}")
  set (UPLOAD_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}.tar.gz)
endif()


set (TomoEngine_WEBSITE_SERVER "www.bluequartz.net")
set (TomoEngine_WEBSITE_SERVER_PATH "/var/www/www.bluequartz.net/binaries/to81/.")
set (TomoEngine_WEBSITE_SCP_USERNAME "mjackson") 
#-- Create a bash script file that will upload the latest version to the web server
configure_file(${PROJECT_RESOURCES_DIR}/upload.sh.in 
               ${PROJECT_BINARY_DIR}/upload.sh)  

# Create an NSIS based installer for Windows Systems
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSIS that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET(CPACK_NSIS_DISPLAY_NAME "EIM Tomography Software Tools")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.bluequartz.net")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.bluequartz.net")
  SET(CPACK_NSIS_CONTACT "mike.jackson@bluequartz.net")
  SET(CPACK_NSIS_MODIFY_PATH ON)
  SET(CPACK_GENERATOR "ZIP")
  SET(CPACK_BINARY_ZIP "ON")
  SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "EIM Tomography Software Tools")
ELSE(WIN32 AND NOT UNIX)
    SET(CPACK_BINARY_BUNDLE "OFF")
    SET(CPACK_BINARY_CYGWIN "OFF")
    SET(CPACK_BINARY_DEB "OFF")
    SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
    SET(CPACK_BINARY_DRAGNDROP "OFF")
    SET(CPACK_BINARY_NSIS "OFF")
    SET(CPACK_BINARY_OSXX11 "OFF")
    SET(CPACK_BINARY_PACKAGEMAKER "OFF")
    SET(CPACK_BINARY_RPM "OFF")
    SET(CPACK_BINARY_STGZ "OFF")
    SET(CPACK_BINARY_TBZ2 "OFF")
    SET(CPACK_BINARY_TGZ "ON")
    SET(CPACK_BINARY_TZ "OFF")
    SET(CPACK_BINARY_ZIP "OFF")
ENDIF(WIN32 AND NOT UNIX)

SET(CPACK_SOURCE_GENERATOR "ZIP")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "TomoGui-${TomoEngine_VERSION_SHORT}-Source")
SET(CPACK_SOURCE_TOPLEVEL_TAG "Source")
SET(CPACK_IGNORE_FILES "/i386/;/x64/;/VS2008/;/zRel/;/Build/;/\\\\.git/;\\\\.*project")
SET(CPACK_SOURCE_IGNORE_FILES "/i386/;/x64/;/VS2008/;/zRel/;/Build/;/\\\\.git/;\\\\.*project")



# THIS MUST BE THE LAST LINE OF THIS FILE BECAUSE ALL THE CPACK VARIABLES MUST BE
# DEFINED BEFORE CPack IS INCLUDED
INCLUDE(CPack)
