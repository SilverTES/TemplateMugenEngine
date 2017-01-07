@echo ######################################################################
@echo #
@echo # Allegro CHM Reference Manual Generator
@echo #
@echo # ===================================================================
@echo # This will generate a CHM Help file.
@echo # Be sure that HTML Help Workshop is installed.
@echo # This Batch script will look for HTML Help Compiler in 
@echo #
@echo # %ProgramFiles(x86)%\HTML Help Workshop\hhc.exe
@echo #
@echo # If you installed it somewhere else then please change this script.
@echo #
@echo ######################################################################
@echo #
@pause
@xcopy /Q /S refman\*.* refman_work\*.*
@ruby generate.rb
@"%ProgramFiles(x86)%\HTML Help Workshop\hhc.exe" chmproject.hhp
@del allegro-index
@del chmproject.hhp
@del allegro_toc.hhc
@rd /S /Q refman_work
@pause