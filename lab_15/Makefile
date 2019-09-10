TOOLS = tools

.PHONY: default clean

default: runme_to_test_asm.asm runme.asm

main.asm: main.c
# What do you do when you're a super good and competent TA and you can't
# figure out how to silence an error? Filter it out, of course!
	LD_PRELOAD= $(TOOLS)/lcc -L $< -o $@ 2>&1 | grep -v 'main.c:6: .* overflow in converting' | cat

runme.asm: main.asm nice.asm
	cat $^ >$@

runme_to_test_asm.asm: nice.asm
	{ printf '.orig x7FFD\nhalt\nSTACK .fill xf000\n.end\n\n'; cat $<; } >$@

clean:
	rm -f main.asm runme*.asm
