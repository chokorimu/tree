ifeq ($(OS),Windows_NT)
    COMPILE = main.exe
    RUN = .\main.exe
else
    COMPILE = main
    RUN = ./main
endif

main: main.c tree.c
	gcc main.c tree.c -o $(COMPILE)
	$(RUN)
    