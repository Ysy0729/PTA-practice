#include<stdio.h>
#include<stdlib.h>
typedef int elemtype;
typedef struct stack{
    elemtype *data;
    int top;
} stack;
//初始化栈
stack* init(int max){
    stack *s = (stack *)malloc(sizeof(struct stack));
    s->data = (elemtype *)malloc(sizeof(elemtype) * max);
    s->top = -1;
    return s;
}
int push(stack *s,int max,elemtype e){
    if(s->top>=max-1){
        return 0;
    }
    s->top++;
    s->data[s->top] = e;
    return 1;
}
int main(){
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    stack* s = init(m);
    for (int i = 0; i < k;i++){
        s->top = -1;
        int flag = 1;
        int q = 1;
        for (int j = 0; j < n;j++)
        {
            int num;
        scanf("%d ", &num);
        while(s->top==-1||s->data[s->top]!=num){
            if((q>n||!push(s,m,q))){
                flag = 0;
                break;
            }
            q++;
        }
        if(flag){
            s->top--;
        }
        }
        if(flag){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
}