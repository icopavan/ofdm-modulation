cmake_minimum_required (VERSION 2.6)
project (ofdm-modulation)

#if (FFTW_FOUND)
#  include_directories(${FFTW_INCLUDE_DIRS})
#  set(LIBS ${LIBS} ${FFTW_LIBRARIES})
#endif (FFTW_FOUND)

# Add efence link
# find_library(EFENCE_LIBRARY NAMES efence PATHS /opt/local/lib/)
# set(LIBS ${LIBS} ${EFENCE_LIBRARY})

# MAC plus OFDM frame generator
add_executable(mac_ofdm_framer mac_ofdm_framer.c)

target_link_libraries(mac_ofdm_framer ofdm_lib ${LIBS})
