// AUTHOR: John ("Jack") Messerly


#include <stdio.h>



// Rone     Rtwo      Rthree        Rfour


#define Rdivider 978

#define Rone 352 

#define Rtwo 979

#define Rthree 1478

#define Rfour 1968

#define voltage 5.03

// CODE STARTS HERE
double parallelTwo (double r1, double r2);
double parallelThree (double r1, double r2, double r3);
double parallelFour (double r1, double r2, double r3, double r4);

double Rdiv = Rdivider;
double R1 = Rone;
double R2 = Rtwo;
double R3 = Rthree;
double R4 = Rfour; 
double Re = 0; // the efective resistance that will go into the equation 
// for finding the voltage. Found in functions by adding things in 
// parallel

double calculate (double resistance);


double vin = voltage;

int main(){

				double val = 0;
	
// Must check 16 combinations, 0 through 15
//
// My simulation needs to obey circuit divider laws. I can probably keep R2 as constant
//
//
//
// If two resistors are pressed at once, I need to find their results in parallel, and use that 
// as the series resistor
//
//

				printf("Rdivider = %d", Rdivider);
				printf("\n%d %d %d %d\n\n", Rone, Rtwo, Rthree, Rfour);
				printf("Combin\t\tVoltage\tButton\n");

				// 0000

					printf("0000\t\t%d\n", 0);

				// 0001
					Re = R4; 
					val = calculate (Re);					
					printf("0001\t\t\t%lf\n", val);

				// 0010
					val = calculate (R3);
					printf("0010\t\t\t%lf\n", val);

				// 0011
					Re = parallelTwo (R4, R3);
					val = calculate (Re);
					printf("0011\t\t%lf\n", val);
				//0100
					Re = R2;
					val = calculate (Re);
				 	printf("0100\t\t\t%lf\n",val);
				//0101
					Re = parallelTwo(R2, R4);
					val = calculate (Re);
					printf("0101\t\t%lf\n", val);
				//0110
					Re = parallelTwo (R2, R3);
					val = calculate (Re);
					printf("0110\t\t%lf\n", val);
				//0111
					Re = parallelThree (R2, R3, R4);
					val = calculate (Re);
					printf("0111\t\t%lf\n", val);
				//1000
					Re = R1;
					val = calculate (Re);
					printf("1000\t\t\t%lf\n", val);
				//1001
					Re = parallelTwo (R4, R1);
				//1010
					Re = parallelTwo (R1, R3);
					val = calculate (Re);
					printf("1010\t\t%lf\n", val);
				//1011
					Re = parallelThree (R1, R3, R4);
					val = calculate (Re);
					printf("1011\t\t%lf\n", val);
				//1100
					Re = parallelTwo (R1, R2);
					val = calculate (Re);
					printf("1100\t\t%lf\n", val);
				//1101
					Re = parallelThree(R1, R2, R4);
					val = calculate (Re);
					printf("1101\t\t%lf\n", val);
				//1110
					Re = parallelThree (R1, R2, R3);
					val = calculate (Re);
					printf("1110\t\t%lf\n", val);
				//1111
					Re = parallelFour (R1, R2, R3, R4);
					val = calculate (Re);
					printf("1111\t\t%lf\n", val);			


}

double calculate (double resistance){
	
		double sum = resistance + Rdiv; 
		double divide = Rdiv / sum; 
		double vout = vin * divide; 

		return vout; 
	

}


double parallelTwo (double r1, double r2) {
	double product = r1 * r2;
	double sum = r1 + r2; 
	double parallelVal = product / sum; 
	return parallelVal;  
}

double parallelThree (double r1, double r2, double r3){

double first = parallelTwo (r1, r2);

double second = parallelTwo (first, r3);

return second;
}


double parallelFour (double r1, double r2, double r3, double r4){

	double first = parallelTwo (r1, r2);
	double second = parallelTwo (r3, r4);
	double third = parallelTwo (first, second);

	return third;
}
