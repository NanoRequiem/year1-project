 echo "Making executables.."
 make all

 echo "Testing usage messages"
 ./pgmEcho
 ./pgmComp
 ./pgma2b
 ./pgmb2a
 ./pgmReduce

 echo "testing successful pgmEcho..."
 ./pgmEcho slice0a.pgm temp1.pgm
 echo "diff Echoed file with original file"
 diff slice0a.pgm temp1.pgm

 echo "Comparing Echo to original..."
 ./pgmComp slice0a.pgm temp1.pgm

 echo "removing executables"
 make clean
