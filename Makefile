GCC = gcc
CFLAGS = -lssl -lcrypto -lm
OBJ = ./obj
BIN = ./bin


PART1 = ./source/partie1-2
PART3 = ./source/partie3
PART4 = ./source/partie4
PART5 = ./source/partie5


all :  $(PART1)/main1 $(PART3)/main2 $(PART4)/main3 $(PART5)/main4_1 $(PART5)/main4_2

 $(PART1)/main1 : $(OBJ)/main1.o $(OBJ)/partie1.o $(OBJ)/partie2.o 
	$(CC) -o  $(PART1)/main1 $(OBJ)/main1.o $(OBJ)/partie1.o $(OBJ)/partie2.o -lm

 $(PART3)/main2 : $(OBJ)/main2.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o 
	$(CC) -o  $(PART3)/main2 $(OBJ)/main2.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o -lm

 $(PART4)/main3 : $(OBJ)/main3.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o $(OBJ)/partie4.o
	$(CC) -o  $(PART4)/main3 $(OBJ)/main3.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o $(OBJ)/partie4.o -lm

 $(PART5)/main4_1 : $(OBJ)/main4_1.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o $(OBJ)/partie4.o  $(OBJ)/ex7.o $(OBJ)/ex8.o $(OBJ)/ex9.o
	$(CC) -o  $(PART5)/main4_1 $(OBJ)/main4_1.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o $(OBJ)/partie4.o  $(OBJ)/ex7.o $(OBJ)/ex8.o $(OBJ)/ex9.o $(CFLAGS)

 $(PART5)/main4_2 : $(OBJ)/main4_2.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o $(OBJ)/partie4.o  $(OBJ)/ex7.o $(OBJ)/ex8.o $(OBJ)/ex9.o
	$(CC) -o  $(PART5)/main4_2 $(OBJ)/main4_2.o $(OBJ)/partie1.o $(OBJ)/partie2.o $(OBJ)/partie3.o $(OBJ)/partie4.o  $(OBJ)/ex7.o $(OBJ)/ex8.o $(OBJ)/ex9.o $(CFLAGS)




 $(OBJ)/main1.o : ./headers/partie1.h ./headers/partie2.h $(PART1)/main1.c
	$(CC) -c $(PART1)/main1.c -o $(OBJ)/main1.o

 $(OBJ)/main2.o : ./headers/partie1.h ./headers/partie2.h ./headers/partie3.h $(PART3)/main2.c
	$(CC) -c $(PART3)/main2.c -o $(OBJ)/main2.o

 $(OBJ)/main3.o : ./headers/partie1.h ./headers/partie2.h ./headers/partie3.h ./headers/partie4.h $(PART4)/main3.c
	$(CC) -c $(PART4)/main3.c -o $(OBJ)/main3.o

 $(OBJ)/main4_1.o : ./headers/partie1.h ./headers/partie2.h ./headers/partie3.h ./headers/partie4.h ./headers/partie5.h $(PART5)/main4_1.c
	$(CC) -c $(PART5)/main4_1.c -o $(OBJ)/main4_1.o

 $(OBJ)/main4_2.o : ./headers/partie1.h ./headers/partie2.h ./headers/partie3.h ./headers/partie4.h ./headers/partie5.h $(PART5)/main4_2.c
	$(CC) -c $(PART5)/main4_2.c -o $(OBJ)/main4_2.o



 $(OBJ)/partie1.o: $(PART1)/partie1.c
	$(CC) -c $(PART1)/partie1.c -o $(OBJ)/partie1.o

 $(OBJ)/partie2.o: $(PART1)/partie2.c
	$(CC) -c $(PART1)/partie2.c -o $(OBJ)/partie2.o

 $(OBJ)/partie3.o: $(PART3)/partie3.c
	$(CC) -c $(PART3)/partie3.c -o $(OBJ)/partie3.o

 $(OBJ)/partie4.o: $(PART4)/partie4.c
	$(CC) -c $(PART4)/partie4.c -o $(OBJ)/partie4.o

 $(OBJ)/ex7.o: $(PART5)/ex7.c
	$(CC) -c $(PART5)/ex7.c -o $(OBJ)/ex7.o

 $(OBJ)/ex8.o: $(PART5)/ex8.c
	$(CC) -c $(PART5)/ex8.c -o $(OBJ)/ex8.o

 $(OBJ)/ex9.o: $(PART5)/ex9.c
	$(CC) -c $(PART5)/ex9.c -o $(OBJ)/ex9.o


clean:
	rm -f ./fichiers/*.txt
	rm -f ./Blockchain/*.txt

mrproper:
	rm -f ./obj/*.o
	
