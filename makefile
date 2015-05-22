


main : main.o httpRequest.o httpResponse.o
	gcc  main.o httpRequest.o httpResponse.o -lpthread -o  main 

main.o : src/main.c 
	gcc -c  src/main.c -o  main.o

httpRequest.o : lib/httpRequest.c include/httpRequest.h
	gcc -c lib/httpRequest.c -o httpRequest.o 

httpResponse.o : lib/httpResponse.c include/httpResponse.h include/httpRequest.h
	gcc -c lib/httpResponse.c -o httpResponse.o


clean : 
	rm -rf ./*.o ;
