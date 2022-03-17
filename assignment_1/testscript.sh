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

 echo "Testing pgma2b..."
 ./pgma2b slice0a.pgm temp2.pgm

 echo "Testing pgmb2a..."
 ./pgmb2a temp2.pgm temp3.pgm

 echo "Comparing Converted files"
 ./pgmComp slice0a.pgm temp3.pgm

 echo "Testing pgmReduce"
 ./pgmReduce toReduce.pgm 5 temp4.pgm

 echo "Showing reduced file"
 more temp4.pgm

 echo "removing executables"
 make clean

 echo "removing output files"
 rm temp*.pgm
