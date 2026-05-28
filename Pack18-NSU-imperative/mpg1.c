#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#pragma comment(linker, "/STACK:50000000")

typedef struct NumStack{
    double data;
    struct NumStack *prev;
} NumStack;
typedef struct OpStack{
    char data;
    struct OpStack *prev;
} OpStack;

NumStack* init_Numstack(double data);
OpStack* init_Opstack(char data);

NumStack* NumPush(NumStack *trail, double data);
OpStack* OpPush(OpStack *trail,char data);

NumStack* NumPop(NumStack *top, double *result);
OpStack* OpPop(OpStack *top, char *result);

double NumTop(NumStack *top);
char OpTop(OpStack *top);

void freeNumStack(NumStack *trail);
void freeOpStack(OpStack *trail);

void printNumStack(NumStack *trail);
void printOpStack(OpStack *trail);

int get_priority(char op);
void apply_operator(NumStack **nums, OpStack **ops);

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    char expr[500005];
    if (!fgets(expr, sizeof(expr), stdin)) {
        return 1;
    }
    
    NumStack *nums = NULL;
    OpStack *ops = NULL;
    
    int i = 0;
    while (expr[i]) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        if (isdigit(expr[i]) || 
            (expr[i] == '-' && (i == 0 || expr[i-1] == '(' || 
             (i > 0 && strchr("+-*/", expr[i-1]))))) {
            
            double sign = 1.0;
            if (expr[i] == '-') {
                sign = -1.0;
                i++;
            }
            
            double num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            nums = NumPush(nums, sign * num);
        }
        else if (expr[i] == '(') {
            ops = OpPush(ops, '(');
            i++;
        }
        else if (expr[i] == ')') {
            while (ops && OpTop(ops) != '(') {
                apply_operator(&nums, &ops);
            }
            char dummy;
            ops = OpPop(ops, &dummy);
            i++;
        }
        else if (strchr("+-*/", expr[i])) {
            char op = expr[i];
            while (ops && OpTop(ops) != '(' && 
                   get_priority(OpTop(ops)) >= get_priority(op)) {
                apply_operator(&nums, &ops);
            }
            ops = OpPush(ops, op);
            i++;
        }
        else {
            i++;
        }
    }
    while (ops) {
        apply_operator(&nums, &ops);
    }
    if (nums) {
        printf("%.20f\n", NumTop(nums));
    }
    
    freeNumStack(nums);
    freeOpStack(ops);
    
    return 0;
}
NumStack* init_Numstack(double data){
    NumStack *new_node = malloc(sizeof(NumStack));
    new_node->data = data;
    new_node->prev = NULL;
    
    return new_node;
}
OpStack* init_Opstack(char data){
    OpStack *new_node = malloc(sizeof(OpStack));
    new_node->data = data;
    new_node->prev = NULL;
    
    return new_node;
}

NumStack* NumPush(NumStack *trail, double data){
    NumStack *new_node = malloc(sizeof(NumStack));
    new_node->data = data;
    new_node->prev = trail;
    return new_node;
}
OpStack* OpPush(OpStack *trail,char data){
    OpStack *new_node = malloc(sizeof(OpStack));
    new_node->data = data;
    new_node->prev = trail;
    return new_node;
}

NumStack* NumPop(NumStack *top, double *result) {
    *result = top->data;
    NumStack *new_top = top->prev;
    free(top);
    return new_top;
}
OpStack* OpPop(OpStack *top, char *result) {
    *result = top->data;
    OpStack *new_top = top->prev;
    free(top);
    return new_top;
}


double NumTop(NumStack *top) {
    return top->data;
}
char OpTop(OpStack *top) {
    return top->data;
}

void freeNumStack(NumStack *trail){
    while (trail != NULL){
        NumStack *prevNode = trail;
        trail = prevNode->prev;

        free(prevNode);
    }
}
void freeOpStack(OpStack *trail){
    while (trail != NULL){
        OpStack *prevNode = trail;
        trail = prevNode->prev;

        free(prevNode);
    }
}

void printNumStack(NumStack *trail){
    while (trail != NULL){
        printf("%lf\n",trail->data);
        trail = trail->prev;
    } 
}
void printOpStack(OpStack *trail){
    while (trail != NULL){
        printf("%c\n",trail->data);
        trail = trail->prev;
    }   
}

void apply_operator(NumStack **nums, OpStack **ops) {
    double b, a, res;
    char op;
    
    *ops = OpPop(*ops, &op);
    *nums = NumPop(*nums, &b);
    *nums = NumPop(*nums, &a);
    
    switch(op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
        default: res = 0;
    }
    
    *nums = NumPush(*nums, res);
}
int get_priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}