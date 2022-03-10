 echo "Making executables.."
 make all

 echo "testing successful pgmEcho..."
 ./pgmEcho identical.pgm temp1.pgm
 echo "Openining test output..."
 more temp1.pgm
 rm temp1.pgm

 echo "testing successful pgmComp..."
 ./pgmComp slice0a.pgm identical.pgm

 echo "removing executables"
 make clean
