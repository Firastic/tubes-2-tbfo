#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <complex.h>
const double EPS = 0.0000000001;
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

complex modified_cpow(complex a, complex b){
	if(fabs(creal(a)) <= EPS && fabs(creal(b)) <= EPS && fabs(cimag(a)) <= EPS && fabs(cimag(b)) <= EPS){
		return 1;
	} else return cpow(a,b);
}

void inc(int *idx){
	do{
		(*idx)++;
	} while(str[*idx] == ' ');
}

void outputComplex(complex X){
	printf("%.8f + %.8fi\n", creal(X), cimag(X));
}

complex parse_expression(int *idx);

complex parse_number(int *idx){
	char t = str[*idx];
	char strcomplex[105];
	memset(strcomplex,0,sizeof(strcomplex));
	int idxcomplex = 0;
	int countdot = 0;
	int isFirstNumber = 1;
	strcomplex[idxcomplex] = t;
//	printf("value strcomplex %c\n",strcomplex[idxcomplex]);
	while ((tipe(t) == 0) || (t == '.')) {
		/*result = result * 10;
		result = result + (t-'0');*/
		(*idx)++;
		t = str[*idx];
		if(isFirstNumber && tipe(t) == 0 && strcomplex[0] == '0'){
			isValid = 0;
		}
		isFirstNumber = 0;
		if ((tipe(t) == 0) || (t == '.')) {
			inc(&idxcomplex);
			strcomplex[idxcomplex] = t;
			if (t == '.')
				countdot = countdot + 1;
			if (countdot > 1)
				isValid = 0;
		}
	}
	if (strcomplex[idxcomplex] == '.'){
		isValid = 0;
		return 0;
	}
	else {
		return strtod(strcomplex,NULL);
		//printf("result = %f\n",result);
	}
}

complex parse_item(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	char t = str[*idx];
	complex result = 0;
	if (tipe(t) == 0){
		result = parse_number(idx);
	} else if(t == '('){
		inc(idx);
		int prev = *idx;
		t = str[*idx];
		if(t == '-'){
			inc(idx);
			prev = *idx;
			result = -parse_expression(idx);
			if(cimag(result) < EPS){
				result = creal(result);
			}
			if(prev == *idx){
				isValid = 0;
				return result;
			}
		} else{
			result = parse_expression(idx);
			if(prev == *idx){
				isValid = 0;
				return result;
			}
		}

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

complex parse_factor(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	char t = str[*idx];
	complex result;
	int prev = *idx;
	result = parse_item(idx);
	if(prev == *idx){
		isValid = 0;
		return result;
	}
	t = str[*idx];
	if(t == '^'){
		inc(idx);
		int prev = *idx;
		result = modified_cpow(result,parse_factor(idx));
		if(prev == *idx){
			isValid = 0;
			return result;
		}
	}
	return result;
}

complex parse_term(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	complex result = parse_factor(idx);
	char t = str[*idx];
	while(tipe(t) == 2){
		inc(idx);
		int prev = *idx;
		complex rhs = parse_factor(idx);
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

complex parse_expression(int *idx){
	complex result = parse_term(idx);
	char t = str[*idx];
	while(tipe(t) == 1){
		inc(idx);
		int prev = *idx;
		complex rhs = parse_term(idx);
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
	//int i;
	//for (i = 1 ; i < 20 ; ++i) {
		gets(str);
		int x = strlen(str);
		int idx = 0;
		isValid = 1;
		complex res = parse_expression(&idx);

		if(isValid && idx == strlen(str)){
			if(mathError)printf("Math error\n");
			else outputComplex(res);
		} else printf("Ekspresi tidak valid\n");
	//}

}
