 gcc pgmEcho.c readFile.c outputFile.c -std=c99 -o pgmEchoTest
 ./pgmEchoTest slice0a.pgm temp1.pgm
 echo "Openining test output..."
 more temp1.pgm
 rm pgmEchoTest
 rm temp1.pgm
