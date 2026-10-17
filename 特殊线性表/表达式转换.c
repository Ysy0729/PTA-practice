
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define maxsize 30
typedef int elemtype;
typedef enum{
    left_kuohao, right_kuohao, add, sub, mul, divide, eos,
    num
} content;
typedef struct stack{
    elemtype *data;
    int top;
} stack;
// 初始化
stack* init(){
    stack *s = (stack *)malloc(sizeof(stack));
    s->data = (elemtype *)malloc(sizeof(elemtype) * maxsize);
    s->top = -1;
    return s;
}
// 入栈
int push(stack* s, elemtype e){
    if(s->top >= maxsize-1){
        return 0;
    }
    s->top++;
    s->data[s->top] = e;
    return 1;
} 
// 出栈
elemtype pop(stack *s){
    if(s->top == -1){
        return 0;
    }
    elemtype e = s->data[s->top];
    s->top--;
    return e;
}
//判断是不是正负号
int is_sign(char *str,int *index){
    if(str[*index]!='-'&&str[*index]!='+'){
        return 0;
    }
    if(!isdigit(str[*index+1])){
        return 0;
    }
    if(*index==0)
        return 1;
    char c = str[*index - 1];
    if(c=='('||c=='+'||c=='-'||c=='*'||c=='/'){
        return 1;
    }
    return 0;
}
// 获取内容
content get_token(char *str, int *index){
    char c = str[*index];
    if (c == '\0')
        return eos;
    if(c=='('){
        *index=*index+1;
        return left_kuohao;
    }
    if(c==')'){
        *index=*index+1;
        return right_kuohao;
    }
    if(c=='+'||c=='-'){
        if(is_sign(str,index)){
            return num;
        }
        *index=*index+1;
        if(c=='+'){
            return add;
        }
        if(c=='-'){
            return sub;
        }
    }
    if (c == '*') {
    (*index)++;
    return mul;
}

if (c == '/') {
    (*index)++;
    return divide;
}
if(isdigit(c)||c=='.'){
    return num;
}
}
// 打印时只输出符号本身，由外部控制空格，避免行末多余空格
void print(content token){
    switch(token){
        case add:
            printf("+");
            break;
        case sub:
            printf("-");
            break;
        case mul:
            printf("*");
            break;
        case divide:
            printf("/");
            break;
        default:
            break;
    }
}
int change(stack *s,char *str){
    int in_stack[] = {0, 3, 1, 1, 2, 2, 0};
    int out_stack[] = {4, 3, 1, 1, 2, 2, 0};
    int index = 0;
    push(s,eos);
    int flag=1;
    while(1){
        content token = get_token(str, &index);
       if(token==eos){
           break;
       }
       if(token==num){
        if(!flag){
            printf(" ");
        }
        if(str[index]=='+'){
            index++;
        }
        else if(str[index]=='-'){
            index++;
            printf("-");
        }
        while(isdigit(str[index])||str[index]=='.'){
            printf("%c", str[index]);
            index++;
             flag = 0;
        }
       }
        else if(token == right_kuohao){
            while(s->data[s->top] != left_kuohao){
                elemtype e = pop(s);
                if(!flag)printf(" ");
                print(e);
                flag=0;
            }
            pop(s);
        }
        else{
            while(in_stack[s->data[s->top]] >= out_stack[token]){
                elemtype e = pop(s);
                if(!flag)printf(" ");
                print(e);
                flag=0;
            }
            push(s, token);
        }
    }
       
    while(s->top>0){
        elemtype e = pop(s);
        if(!flag)printf(" ");
        print(e);
        flag=0;
    }
    return 1;
}

int main(){
    char str[maxsize];
    if(scanf("%s", str)!=1)return 0;
    stack *s = init();
    change(s,str);
    return 0;
}
