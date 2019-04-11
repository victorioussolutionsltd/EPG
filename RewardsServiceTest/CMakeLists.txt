CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(RewardsServiceTest
        LANGUAGES CXX)


add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    SET(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    SET(GOOGLETEST_DIR "../googletest")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    SET(GTestSrc ${GOOGLETEST_DIR}/googletest)
    SET(GMockSrc ${GOOGLETEST_DIR}/googlemock)
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()


include_directories(${GTestSrc} ${GTestSrc}/include ${GMockSrc} ${GMockSrc}/include Interfaces Mocks UnitTests)

add_executable(${PROJECT_NAME} main.cpp
                               UnitTests/RewardsFactoryTest.h RewardsFactory.h RewardsFactory.cpp
                               UnitTests/AccountTest.h Account.h Account.cpp
                               UnitTests/RewardsServiceTest.h RewardsService.h RewardsService.cpp
                               UnitTests/EligibilityServiceTest.h EligibilityService.h EligibilityService.cpp

                               Interfaces/AbstractAccount.h
                               Interfaces/AbstractEligibilityService.h

                               Mocks/AccountMock.h
                               Mocks/EligibilityServiceMock.h

                               Exceptions/InvalidAccountNumberException.h
                               Exceptions/TechnicalFailureException.h


               ${GTestSrc}/src/gtest-all.cc
               ${GMockSrc}/src/gmock-all.cc)
add_test(${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

