generate_grpc_lib(
    RpcProto
    ${CMAKE_SOURCE_DIR}/include/MaaRpc/proto
    ${CMAKE_CURRENT_BINARY_DIR}/generated
    maa_rpc_proto_src)

file(GLOB_RECURSE maa_rpc_src implement/* implement/* API/*)
file(GLOB_RECURSE maa_rpc_header ../../include/MaaRpc/*)

add_library(MaaRpc SHARED ${maa_rpc_src} ${maa_rpc_header})
target_compile_definitions(MaaRpc PRIVATE MAA_RPC_EXPORTS)
target_include_directories(
    MaaRpc
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include> $<INSTALL_INTERFACE:include>
    PRIVATE . ../include ../../include 
    ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(MaaRpc PUBLIC MaaToolkit PRIVATE RpcProto MaaUtils HeaderOnlyLibraries protobuf::libprotobuf gRPC::grpc++)

install(
    TARGETS MaaRpc
    EXPORT MaaFrameworkTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../include/MaaRpc" DESTINATION "include")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${maa_rpc_src})

if(BUILD_GRPC_CLI)
    add_subdirectory(cli)
endif()
