#include <stdio.h>
#include <string.h>
#include <math.h>
char str[105],arr[105];
int isValid;

int tipe(char X){
	switch(X){
		case '+': return 1; break;
		case '-': return 1; break;
		case '*': return 2; break; 
		case '/': return 2; break;
		case '^': return 3; break;
		case '(': return 4; break;
		case ')': return 5; break;
		default: return 0;
	}
}

void inc(int *idx){
	do{
		(*idx)++;
	} while(str[*idx] == ' ');
}

float parse_expression(int *idx);

float parse_item(int *idx){
	char t = str[*idx];
	float result = 0;
	if(tipe(t) == 0){
		result = t-'0';
		inc(idx);
	} else if(t == '('){
		inc(idx);
		int prev = *idx;
		result = parse_expression(idx);
		if(prev == *idx){
			isValid = 0;
			return result;
		}
		if(str[*idx] == ')')inc(idx);
		else {
			isValid = 0;
			return result;
		}
	}
	return result;
}

float parse_factor(int *idx){
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
		int prev = *idx;
		result = parse_item(idx);
		if(prev == *idx){
			isValid = 0;
			return result;
		}
	} else return result;
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
		else *idx = strlen(str)+1;
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
		int rhs = parse_term(idx);
		if(prev == *idx){
			isValid = 0;
			return result;
		}

		if(t == '+')result = result+rhs;
		else result = result-rhs;
		t = str[*idx];
	}
	return result;
}
	
int main(){
	gets(str);
	str[strlen(str)] = ' ';
	str[strlen(str)] = '.';
	int x = strlen(str);
	int idx = 0;
	isValid = 1;
	float res = parse_expression(&idx);

	if(isValid){
		if(idx > x)printf("Math error\n");
		else printf("%f\n", res);
	} else printf("Ekspresi tidak valid\n");
}