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

float parse_expression(int *idx);

float parse_item(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	char t = str[*idx];
	float result = 0;
	if (tipe(t) == 0){
		char strfloat[105];
		int idxfloat = 0;
		strfloat[idxfloat] = t;
	//	printf("value strfloat %c\n",strfloat[idxfloat]);
		while ((tipe(t) == 0) || (t == '.')) {
			/*result = result * 10;
			result = result + (t-'0');*/
			inc(idx);
			t = str[*idx];
			if ((tipe(t) == 0) || (t == '.')) {
				inc(&idxfloat);
				strfloat[idxfloat] = t;
				//printf("value strfloat %c\n",strfloat[idxfloat]);
			}
		}
		result = strtof(strfloat,NULL);
		printf("result = %f\n",result);
		memset(strfloat, 0, sizeof(strfloat));
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

float parse_factor(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	char t = str[*idx];
	float result;
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

float parse_term(int *idx){
	if(*idx == strlen(str)){
		isValid = 0;
	}
	float result = parse_factor(idx);
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

float parse_expression(int *idx){
	float result = parse_term(idx);
	char t = str[*idx];
	while(tipe(t) == 1){
		inc(idx);
		int prev = *idx;
		float rhs = parse_term(idx);
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
	float res = parse_expression(&idx);

	if(isValid && idx == strlen(str)){
		if(mathError)printf("Math error\n");
		else printf("%f\n", res);
	} else printf("Ekspresi tidak valid\n");
}
