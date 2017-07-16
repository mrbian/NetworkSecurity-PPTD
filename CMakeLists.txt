cmake_minimum_required(VERSION 3.7)
project(PPTD)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        Queue/queue.h Queue/queue.c Tree/tree.h Tree/tree.c Database/database.h Database/database.c SAGTD/common/common.h SAGTD/common/common.c SAGTD/STR/str.h SAGTD/STR/str.c SAGTD/SAGTD.h SAGTD/SAGTD.c SAGTD/SAG/sag.h SAGTD/SAG/sag.c MPSTD/MPSTD.h MPSTD/MPSTD.c MPSTD/MCST.h MPSTD/MCST.c Print/sagtd_print.h Print/mpstd_print.h Print/sagtd_print.c Print/mpstd_print.c config/config.h TrackSet/track.h TrackSet/track.c Analysis/analysis.h Analysis/analysis.c Print/main_print.h Print/main_print.c)

add_executable(PPTD ${SOURCE_FILES})