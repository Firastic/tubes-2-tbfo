#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char str[105],arr[105];
int isValid,mathError;

int tipe(char X){
	switch(X){
		case '+': return 1; break;
		case '-': return 1; break;
		case '*': return 2; break;
		case '/': return 2; break;
		case '^': return 3; break;
		case '(': return 4; break;
		case ')': return 5; break;
		default: if(X <= '9' && X >= '0')return 0;
				 else return 6;
	}
}

void inc(int *idx){
	do{
		(*idx)++;
	} while(str[*idx] == ' ');
}

double parse_expression(int *idx);

double parse_item(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	char t = str[*idx];
<<<<<<< HEAD
	double result = 0;
=======
	float result = 0;
>>>>>>> c754c050a69b3fb88277f95530cd866cec75352b
	if (tipe(t) == 0){
		char strdouble[105];
		int idxdouble = 0;
		int countdot = 0;
		strdouble[idxdouble] = t;
	//	printf("value strdouble %c\n",strdouble[idxdouble]);
		while ((tipe(t) == 0) || (t == '.')) {
			/*result = result * 10;
			result = result + (t-'0');*/
			inc(idx);
			t = str[*idx];
			if ((tipe(t) == 0) || (t == '.')) {
				inc(&idxdouble);
				strdouble[idxdouble] = t;
				if (t == '.')
					countdot = countdot + 1;
				if (countdot > 1)
					isValid = 0;
			}
		}
		result = strtod(strdouble,NULL);
		printf("result = %f\n",result);
<<<<<<< HEAD
		memset(strdouble, 0, sizeof(strdouble));
=======
		memset(strfloat, 0, sizeof(strfloat));
>>>>>>> c754c050a69b3fb88277f95530cd866cec75352b
	} else if(t == '('){
		inc(idx);
		int prev = *idx;
		result = parse_expression(idx);

		if(prev == *idx){
			isValid = 0;
			return result;
		}
		if(str[*idx] == ')')
			inc(idx);
		else {
			isValid = 0;
			return result;
		}
	} else isValid = 0;
	return result;
}

double parse_factor(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	char t = str[*idx];
	double result;
	if(t == '-'){
		inc(idx);
		int prev = *idx;
		result = -parse_item(idx);
		if(prev == *idx){
			isValid = 0;
			return result;
		}
	} else if(tipe(t) == 0 || tipe(t) == 4){
		printf("Angka parse\n");
		int prev = *idx;
		result = parse_item(idx);
		if(prev == *idx){
			isValid = 0;
			return result;
		}
	} else isValid = 0;
	t = str[*idx];
	if(t == '^'){
		inc(idx);
		int prev = *idx;
		result = pow(result,parse_factor(idx));
		if(prev == *idx){
			isValid = 0;
			return result;
		}
	}
	return result;
}

double parse_term(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	double result = parse_factor(idx);
	char t = str[*idx];
	while(tipe(t) == 2){
		inc(idx);
		int prev = *idx;
		int rhs = parse_factor(idx);
		if(prev == *idx){
			isValid = 0;
			return result;
		}

		if(t == '*')result = result*rhs;
		else if(rhs != 0)result = result/rhs;
		else if(t == '/'){
			mathError = 1;
		} else {
			isValid = 0;
		}
		t = str[*idx];
	}
	return result;
}

double parse_expression(int *idx){
	double result = parse_term(idx);
	char t = str[*idx];
	while(tipe(t) == 1){
		inc(idx);
		int prev = *idx;
<<<<<<< HEAD
		double rhs = parse_term(idx);
=======
		float rhs = parse_term(idx);
>>>>>>> c754c050a69b3fb88277f95530cd866cec75352b
		if(prev == *idx){
			isValid = 0;
			return result;
		}

		if(t == '+')result = result+rhs;
		else if(t == '-')result = result-rhs;
		else isValid = 0;
		t = str[*idx];
	}
	return result;
}

int main(){
	gets(str);
	int x = strlen(str);
	int idx = 0;
	isValid = 1;
	double res = parse_expression(&idx);

	if(isValid && idx == strlen(str)){
		if(mathError)printf("Math error\n");
		else printf("%f\n", res);
	} else printf("Ekspresi tidak valid\n");
}
