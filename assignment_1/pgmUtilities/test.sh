 gcc pgmEcho.c readFile.c outputFile.c -std=c99 -o pgmEchoTest
 ./pgmEchoTest identical.pgm temp1.pgm
 echo "Openining test output..."
 more temp1.pgm
 rm pgmEchoTest
 rm temp1.pgm

 echo "testing pgmComp..."
 gcc pgmComp.c readFile.c -std=c99 -o pgmCompTest
 ./pgmCompTest slice0a.pgm identical.pgm
 rm pgmCompTest
