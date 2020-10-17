/*
 * GccApplication1.c
 *
 * Created: 10/6/2020 8:41:58 PM
 * Author : User
 */ 

#include <avr/io.h>
int calculatebonus(int yearsWorked);

int main()
{
  
  
	int Kamil = calculatebonus(15);
	printf("You get ", Kamil)  ;
   return 0;
   
  
}

int calculatebonus(int yearsWorked){
	int bonus = yearsWorked *250;
	
	if(yearsWorked> 10){
		
		bonus = bonus + 10000;
		
	}
		return(bonus);
}
