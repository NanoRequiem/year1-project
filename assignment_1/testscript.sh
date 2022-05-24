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
 
 echo "running pgmAssemble"
 ./pgmAssemble Assembled.pgm 512 512 0 0 test_0_0.pgm 0 1 test_0_1.pgm 0 2 test_0_2.pgm 1 0 test_1_0.pgm 1 1 test_1_1.pgm 1 2 test_1_2.pgm 2 0 test_2_0.pgm 2 1 test_2_1.pgm 2 2 test_2_2.pgm

 echo "removing executables"
 make clean

 echo "removing output files"
 rm temp*.pgm
