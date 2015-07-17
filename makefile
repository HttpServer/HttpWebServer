

main : main.o httpRequest.o httpResponse.o
	gcc  build/obj/main.o build/obj/httpRequest.o build/obj/httpResponse.o -lpthread -Wall -Wextra -Werror -o build/release/httpd 


main.o : src/main.c 
	gcc -c  src/main.c -o  build/obj/main.o

httpRequest.o : lib/httpRequest.c include/httpRequest.h
	gcc -c lib/httpRequest.c -o build/obj/httpRequest.o 

httpResponse.o : lib/httpResponse.c include/httpResponse.h include/httpRequest.h
	gcc -c lib/httpResponse.c -o ./build/obj/httpResponse.o


clean : 
	rm -rf ./build/obj/*.o ;
