.PHONY : build
build :
	dune build

.PHONY : test
test :
	dune exec test/test.exe
