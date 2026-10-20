#include<stdio.h>
#include<stdlib.h>
#define maxsize 2000
//定义非零元素结构体
typedef struct {
int row,col,value;
}elemtype;
//定义稀疏矩阵
typedef struct{
    int m,n,r;
    elemtype data[maxsize];
}matrix;
//定义输入函数
void input(matrix *a){
    scanf("%d%d%d",&a->m,&a->n,&a->r);
    for(int i=0;i<a->r;i++){
        scanf("%d %d %d",&a->data[i].row,&a->data[i].col,&a->data[i].value);
    }

}
//对三元数组进行排序
void sort(matrix *a){
    //冒泡排序
    for(int i=0;i<a->r-1;i++){
        for(int j=0;j<a->r-1-i;j++){
            if(a->data[j].row>a->data[j+1].row||a->data[j].row==a->data[j+1].row&&a->data[j].col>a->data[j+1].col){
                elemtype t=a->data[j];
                a->data[j]=a->data[j+1];
                a->data[j+1]=t;
            }
        }
    }
}
//定义输出函数
void output(matrix a,char c){
    if(c=='L'){
        printf("Rows=%d,Cols=%d,r=%d",a.m,a.n,a.r);
        printf("\n");
        for(int i=0;i<a.r;i++){
            printf("%d %d %d\n",a.data[i].row,a.data[i].col,a.data[i].value);
        }
    }
    else{
        printf("    ");
        for(int i=1;i<=a.n;i++){
            printf("%4d",i);
        }
        printf("\n");
        int k=0;
        for(int i=1;i<=a.m;i++){
            printf("%4d",i);
            for(int j=1;j<=a.n;j++){
               int value=0;
               if(k<a.r&&a.data[k].row==i&&a.data[k].col==j){
                value=a.data[k].value;
                k++;
               } 
               printf("%4d",value);
            }
            printf("\n");
        }
    }
}
//转置矩阵
matrix transform(matrix a){
    matrix c;
    c.m=a.n;
    c.n=a.m;
    c.r=a.r;
    for(int i=0;i<a.r;i++){
        c.data[i].row=a.data[i].col;
        c.data[i].col=a.data[i].row;
        c.data[i].value=a.data[i].value;
    }
    sort(&c);
    return c;
}
//矩阵相加(默认可以相加)
matrix add(matrix a,matrix b){
    matrix c;
    c.m=a.m;
    c.n=a.n;
    c.r=a.r;
    for(int i=0;i<a.r;i++){
        c.data[i]=a.data[i];
    }
    for(int i=0;i<b.r;i++){
        int found=0;
        for(int j=0;j<c.r;j++){
            if(c.data[j].row==b.data[i].row&&c.data[j].col==b.data[i].col){
                c.data[j].value+=b.data[i].value;
                found=1;
                break;
            }
        }
        if(!found){
            
            c.data[c.r]=b.data[i];
            c.r++;
        }
    }
    int k=0;
    for(int i=0;i<c.r;i++){
        if(c.data[i].value!=0){
           c.data[k++]=c.data[i];
        }
    }
    c.r=k;
    sort(&c);
    return c;
}
//矩阵相乘
matrix multiply(matrix a,matrix b){
    matrix c;
    c.m=a.m;;
    c.n=b.n;
    c.r=0;
    for(int i=0;i<a.r;i++){
      for(int j=0;j<b.r;j++){
        if(a.data[i].col==b.data[j].row){
            int value=a.data[i].value*b.data[j].value;
            int row=a.data[i].row;
            int col=b.data[j].col;
            int found=0;
            for(int k=0;k<c.r;k++){
            if(c.data[k].row==row&&c.data[k].col==col){
                c.data[k].value+=value;
                found=1;
                break;
            }
        }
            if(!found){
                c.data[c.r].row=row;
                 c.data[c.r].col = col;
                    c.data[c.r].value = value;
                    c.r++;
            }
        }
        }
        
      }
      int k=0;
      for(int i=0;i<c.r;i++){
        if(c.data[i].value!=0){
            c.data[k++]=c.data[i];
        }
    }
    c.r=k;
    sort(&c);
    return c;
   
}
int main(){
    matrix a,b,t,c;
    char mode;
    input(&a);
    input(&b);
    scanf(" %c", &mode);
    t=transform(a);
    printf("The transformed matrix is:\n");
    output(t,mode);
    if(a.m!=b.m||a.n!=b.n){
         printf("Can not add!\n");
    }
    else{
        c=add(a,b);
        printf("The added matrix is:\n");
        output(c, mode);
    }
 if (a.n != b.m) {
        printf("Can not multiply!\n");
    } else {
        c = multiply(a, b);
        printf("The product matrix is:\n");
        output(c, mode);
    }
    return 0;
}