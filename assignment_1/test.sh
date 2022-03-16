 echo "Making executables.."
 make all

 echo "testing successful pgmEcho..."
 ./pgmEcho slice0a.pgm temp1.pgm
 echo "Openining test output..."
 more temp1.pgm

 echo "testing successful pgmComp..."
 ./pgmComp slice0a.pgm identical.pgm

 echo "removing executables"
 make clean
