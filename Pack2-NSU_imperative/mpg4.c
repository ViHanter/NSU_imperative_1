#include <stdio.h>

// Функции для нахождения максимума и минимума
int max(int a, int b) {
    if (a>b) return a;
    else return b;
}

int min(int a, int b) {
    if (a<b) return a;
    else return b;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int a1, a2, b1, b2, c1, c2;
    scanf("%d %d %d %d %d %d", &a1, &a2, &b1, &b2, &c1, &c2);

    int b_dlin = max(b1, b2), b_shir = min(b1, b2);
    int c_dlin = max(c1, c2), c_shir = min(c1, c2);
    
    // Проверяем ВСЕ возможные комбинации размещений
    int is_possible = 0;
    
    // Вариант 1: оба прямоугольника горизонтально
    if (b_dlin <= a1 && c_dlin <= a1 && b_shir + c_shir <= a2) is_possible = 1;
    
    // Вариант 2: B горизонтально, C вертикально
    if (b_dlin <= a1 && c_shir <= a1 && b_shir + c_dlin <= a2) is_possible = 1;
    
    // Вариант 3: B вертикально, C горизонтально  
    if (b_shir <= a1 && c_dlin <= a1 && b_dlin + c_shir <= a2) is_possible = 1;
    
    // Вариант 4: оба вертикально
    if (b_shir <= a1 && c_shir <= a1 && b_dlin + c_dlin <= a2) is_possible = 1;
    
    // Те же варианты, но с другой ориентацией A
    if (b_dlin <= a2 && c_dlin <= a2 && b_shir + c_shir <= a1) is_possible = 1;
    if (b_dlin <= a2 && c_shir <= a2 && b_shir + c_dlin <= a1) is_possible = 1;
    if (b_shir <= a2 && c_dlin <= a2 && b_dlin + c_shir <= a1) is_possible = 1;
    if (b_shir <= a2 && c_shir <= a2 && b_dlin + c_dlin <= a1) is_possible = 1;

    if (is_possible) {
        printf("YES");
    } else printf("NO");
    
    return 0;
}