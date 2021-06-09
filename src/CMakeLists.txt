set(PUB_HEADERS ../vendor/Skeleton/include)

file(GLOB TET_SRC
    "*.h"
    "*.cpp"
    "Game/*.cpp"
    "Game/*.h"
    "States/*.h"
    "States/*.cpp"
)

add_executable(Tetris ${TET_SRC})
target_include_directories(Tetris PUBLIC ${PUB_HEADERS})

target_link_libraries(Tetris SkeletonLib)
