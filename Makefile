simulator.out : city.o citylist.o main.o plane.o  
	g++ -ansi -Wall -g -o simulator.out  city.o citylist.o main.o plane.o  

city.o : city.cpp city.h 
	g++ -ansi -Wall -g -c  city.cpp

citylist.o : citylist.cpp citylist.h 
	g++ -ansi -Wall -g -c  citylist.cpp

main.o : main.cpp citylist.h plane.h 
	g++ -ansi -Wall -g -c  main.cpp

plane.o : plane.cpp plane.h citylist.h 
	g++ -ansi -Wall -g -c  plane.cpp

clean :
	rm -f simulator.out city.o  citylist.o  main.o  plane.o   