#  -------------------------------------------------------------------------
#  Copyright (C) 2018 BMW Car IT GmbH
#  All rights reserved.
#  -------------------------------------------------------------------------
#  This document contains proprietary information belonging to BMW Car IT.
#  Passing on and copying of this document, use and communication of its
#  contents is not permitted without prior written authorization.
#  -------------------------------------------------------------------------

file(GLOB
    RAMSES_ANDROIDINTERFACE_FILES_SOURCE
    src/*.cpp)

ACME_MODULE(
    #==========================================================================
    # general module information
    #==========================================================================
    NAME                    AndroidInterface
    TYPE                    STATIC_LIBRARY
    ENABLE_INSTALL          ON

    #==========================================================================
    # files of this module
    #==========================================================================
    FILES_PRIVATE_HEADER    include/*.h
    FILES_SOURCE            ${RAMSES_ANDROIDINTERFACE_FILES_SOURCE}
    FILES_RESOURCE          res/*

    #==========================================================================
    # dependencies
    #==========================================================================
    DEPENDENCIES            ramses-client
                            ramses-framework
                            ramses-renderer-lib
                            Window_Android
                            DisplayManager
)

if (TARGET AndroidInterface)
    set(ramses-shared-lib-MIXIN
        ${ramses-shared-lib-MIXIN}
        FILES_SOURCE ${RAMSES_ANDROIDINTERFACE_FILES_SOURCE}
        DEPENDENCIES AndroidInterface
        CACHE INTERNAL "")
endif()
