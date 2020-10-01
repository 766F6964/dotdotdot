
CFLAGS=-Wall -Werror -I../src
LIBS=-lncursesw -lm -lpbm

pbmtodots: ../src/constants.c ../src/grid.c ../src/unicode.c ../src/renderer.c pbmtodots.c
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

test: pbmtodots
	./$^ tag-text.pbm > text-test.out 2> text-test.err
	grep -q '^pbmtodots: input 16x16, output 16x16$$' text-test.err
	cmp text-test.out verify.txt
	./$^ < tag-raw.pbm > tag-raw.out 2> /dev/null
	cmp text-test.out tag-raw.out
	@echo ALL TESTS SUCCEEDED

clean:
	rm -f pbmtodots text-test.out text-test.err tag-raw.out
