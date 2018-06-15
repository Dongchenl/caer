IF (NOT DSNN)
	SET(DSNN 0 CACHE BOOL "Enable the dsnn module")
ENDIF()

IF (DSNN)
    ADD_LIBRARY(dsnn SHARED dsnn.c)

    TARGET_LINK_LIBRARIES(dsnn ${CAER_C_LIBS})

ENDIF()

