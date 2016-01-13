PyHtdSeed.o:
	g++ -fPIC  -I../../include/ -I/usr/include/python2.7 -I. -std=gnu++11 -c PyHtdSeed.cpp -o PyHtdSeed.o 

PyMutableHypergraphImpl.o:
	g++ -fPIC  -I../../include/ -I/usr/include/python2.7 -I. -std=gnu++11 -c PyMutableHypergraphImpl.cpp -o PyMutableHypergraphImpl.o 

PyMinFillOrderingAlgorithmImpl.o:
	g++ -fPIC  -I../../include/ -I/usr/include/python2.7 -I. -std=gnu++11 -c PyMinFillOrderingAlgorithmImpl.cpp -o PyMinFillOrderingAlgorithmImpl.o 

PyBucketEliminationTreeDecompositionAlgorithm.o:
	g++ -fPIC  -I../../include/ -I/usr/include/python2.7 -I. -std=gnu++11 -c PyBucketEliminationTreeDecompositionAlgorithm.cpp -o PyBucketEliminationTreeDecompositionAlgorithm.o 

PyITreeDecomposition.o:
	g++ -fPIC  -I../../include/ -I/usr/include/python2.7 -I. -std=gnu++11 -c PyITreeDecomposition.cpp -o PyITreeDecomposition.o 

htd.o:
	g++ -fPIC -I../../include/ -I/usr/include/python2.7 -I. -L./libs/ -std=gnu++11  -l:libhtd.so -c htd.cpp -o htd.o

htd: PyHtdSeed.o PyITreeDecomposition.o PyBucketEliminationTreeDecompositionAlgorithm.o PyBucketEliminationTreeDecompositionAlgorithm.o PyMinFillOrderingAlgorithmImpl.o PyMutableHypergraphImpl.o htd.o
	g++ -shared -Wl,-soname,htd.so -L./libs/ -o htd.so htd.o PyHtdSeed.o PyMutableHypergraphImpl.o PyMinFillOrderingAlgorithmImpl.o PyBucketEliminationTreeDecompositionAlgorithm.o PyITreeDecomposition.o -lpython2.7 -lboost_python -std=gnu++11  -l:libhtd.so

py_test:
	./test.py

test:
	g++ -fPIC  -I../../include/ -L./libs/ -I. -std=gnu++11 -l:libhtd.so test.cpp -o test


clean:
	rm *.o htd.so || true
