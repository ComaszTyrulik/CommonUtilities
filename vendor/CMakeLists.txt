if (NOT DEFINED CT_VENDOR_XXHASH)
    add_subdirectory(XxHash)
    set(CT_VENDOR_XXHASH CT::vendor_xxhash PARENT_SCOPE)
endif()
