         _     ____     _____                   _    ____   
        | |   / ___|   |___ /    __ _ _ __   __| |  / ___|_ 
        | |  | |   _____ |_ \   / _` | '_ \ / _` | | |   (_)
        | |__| |__|_____|__) | | (_| | | | | (_| | | |___ _ 
        |_____\____|   |____/   \__,_|_| |_|\__,_|  \____(_)
                                                     _             _     
 __ _   __ _ _ ___ ______ _____ _____ _ _   ___ _ __(_)___ ___  __| |___ 
/ _` | / _| '_/ _ (_-<_-</ _ \ V / -_) '_| / -_) '_ \ (_-</ _ \/ _` / -_)
\__,_| \__|_| \___/__/__/\___/\_/\___|_|   \___| .__/_/__/\___/\__,_\___|
                                               |_|                       

                       a lab brought to you by
                    austin adams feat. cem gokmen
=========================================================================

In this lab, you will implement the following pseudocode TWICE, once in
assembly, and once in C:

    function nice():
        sum = 0

        for i = 0 to 69 inclusive:
            sum += i

        return sum

Exercise 1. Implement the pseudocode above in LC-3 assembly in
            `nice.asm'. We have provided the setup and teardown code
            (including callee saving registers), so don't worry about
            that. Just make sure to put your return value in R0.

            Each time before you test it in complx, run the following
            command, which will run the Makefile:

                $ make runme_to_test_asm.asm

            This will create a new file, `runme_to_test_asm.asm', which
            you can load in Complx. Before proceeding, use ``Simulate
            Subroutine Call'' to call nice().

            After pressing ``Run'' and making sure it terminates, to
            view the result your puts on the stack, you can press
            Control-G and enter `xF000'. That will take you to the
            bottom of the stack, where you should see:

             addr | value
            -------------
                 ...
            xEFFE | 2415    <-- return value of nice(), should be 2415 decimal
            xF000 | ???
                 ...

            Make sure this works right before continuing, since
            debugging will be more painful later on.


Exercise 2. Now implement nice() again in C in the nice_c() function
            in `main.c'. Much less tedious and more readable, right?

            Now run:

                $ make

            This runs the Makefile, which generates `main.asm' from
            `main.c'. (If you're on a VM and this fails with an error
            like ``file not found'', run `sudo apt install libc6-i386'.
            If you're on Docker and you get something like ``file not
            found'', restart the Docker container by re-running
            cs2110docker.sh.)

            Write down some short answers to these questions below:

            1. What is inside `main.asm'?

            2. Quickly compare the length of the generated code for
               nice_c() in `main.asm' (it's at around line 20 for me)
               with the length of your hand-written implementation in
               `nice.asm'. Eyeballing it, how much of a difference in
               length is there?

            3. What is this .c -> .asm generation process called?

            4. If you look in the Makefile, you'll see that it runs a
               program called lcc to generate the .asm file from the .c
               file. What is lcc, then?

            5. Is `main.asm' a binary yet? If so, why? If not, what step
               remains? (Multiple possible answers here)


Exercise 3. Finally, let's test our code.

            We've provided a hack that allows you to invoke your
            hand-written assembly nice() solution from C by calling
            nice_asm(). Do NOT write `nice()' in your C code or weird
            things will happen and it will be your fault sorry buddy.

            Let's use this hack. Write some code in main() in `main.c'
            that calls both nice_asm() and nice_c(), and prints the
            results. The output needs to look exactly like this (hint:
            Google printf):

                nice_asm() = 2415 = 0x96F
                nice_c()   = 2415 = 0x96F

            To build the final assembly file, run

                $ make

            And open `runme.asm' in Complx using ``File'' > ``Clean
            Load'' (since the compiler is crappy and expects memory to
            be zeroed). Do NOT load with ``File'' > ``Load'' since that
            randomizes memory and this compiler we randomly found on
            github chokes on that.

            When you click ``Run'', you should get the following output
            in the I/O window:

                nice_asm() = 2415 = 0x96F
                nice_c()   = 2415 = 0x96F

            Show this output and your answers from Exercise 2 to a TA.
            If they're cool with it, you're done! Good work bud
