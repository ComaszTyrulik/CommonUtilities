if (NOT DEFINED CT_XXHASH_VENDOR)
    add_subdirectory(XxHash)
    set(CT_XXHASH_VENDOR CT::vendor_xxhash PARENT_SCOPE)
endif()
