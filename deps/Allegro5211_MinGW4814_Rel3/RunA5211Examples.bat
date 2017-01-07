
set SCRIPT_HOME=%~dp0

set path=%SCRIPT_HOME%\bin\dlls;%PATH%

cd /d %SCRIPT_HOME%\bin\examples

title Allegro 5.2.1.1 Examples Environment

color 0a

doskey showhelp=%SCRIPT_HOME%\ShowHelp.bat

doskey home=cd /d %SCRIPT_HOME%

doskey examples=cd /d %SCRIPT_HOME%\bin\examples

doskey htmldocs=start %SCRIPT_HOME%\docs\allegro5\html\refman\index.html

doskey chmdocs=start %SCRIPT_HOME%\docs\allegro5\chm\Allegro5_2_1_1_Manual.chm

cls

call %SCRIPT_HOME%\ShowHelp.bat

cmd.exe


