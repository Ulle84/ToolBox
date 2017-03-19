################################################################################
# Call of CodeCleaner as Post-Build Step
# Created by Ulrich Belitz on 2017-03-09
################################################################################

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND CodeCleaner.exe ARGS
  -d ${CMAKE_CURRENT_SOURCE_DIR}
  -isd
  -csf ${CMAKE_CURRENT_BINARY_DIR}/CodeCleanerChecksum.txt
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../bin
)