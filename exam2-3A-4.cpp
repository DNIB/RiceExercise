#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

int check_array(int a[100][100], int n, int x, int y)
{
    for (int cy = 0; cy < n; cy++)
    {
        for (int cx = 0; cx < 2 * n; cx++)
        {
            if (a[x][y] == a[cx][cy] && (x != cx || y != cy))
            {
                return -1;
            }
        }
    }
    return 0;
}

void random_array(int a[100][100], int n)
{
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < 2 * n; x++)
        {
            a[x][y] = rand() % (4 * n * n - n) + n;
            x += check_array(a, n, x, y);
        }
    }
}

void print_array(int a[100][100], int s[100][100], int n)
{
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < 2 * n; x++)
        {
            if (s[x][y] == 1)
            {
                printf("%4d ", a[x][y]);
            }
            else
            {
                printf("%4s ", "*");
            }
        }
        printf("\n");
    }
    puts("");
}

void set_shadow(int s[100][100], int value, int n)
{
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < 2 * n; x++)
        {
            s[x][y] = value;
        }
    }
}

int main()
{
    srand(time(0));
    int a[100][100], s[100][100] = {1}, n, temp = 0, pt[3], ct[3], pp = 0, cp = 0;
    int x1, y1, x2, y2;
    char play;
    printf("Enter n: ");
    scanf("%d", &n);
    random_array(a, n);
    set_shadow(s, 0, n);
    print_array(a, s, n);
    while (temp < 2 * n * n)
    {
        printf("Your picks: ");
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1--;
        y1--;
        x2--;
        y2--;
        while (s[x1][y1] == 1 || s[x2][y2] == 1)
        {
            printf("The numbers cannot be retaken.\n");
            printf("Your picks: ");
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1--;
            y1--;
            x2--;
            y2--;
        }
        s[x1][y1] = 1;
        s[x2][y2] = 1;
        pt[0] = a[x1][y1] + a[x2][y2];
        pt[1] = a[x1][y1];
        pt[2] = a[x2][y2];
        do
        {
            x1 = rand() % (2 * n);
            y1 = rand() % n;
        } while (s[x1][y1] == 1);
        s[x1][y1] = 1;
        do
        {
            x2 = rand() % (2 * n);
            y2 = rand() % n;
        } while (s[x2][y2] == 1);
        s[x2][y2] = 1;
        ct[0] = a[x1][y1] + a[x2][y2];
        ct[1] = a[x1][y1];
        ct[2] = a[x2][y2];
        print_array(a, s, n);
        printf("Player's number: %d %d Computers's number: %d %d \n", pt[1], pt[2], ct[1], ct[2]);
        printf("The player has %d (%d %d) points and the computer has %d (%d %d) points. ", pt[0], pt[1], pt[2], ct[0], ct[1], ct[2]);
        if (pt[0] > ct[0])
        {
            printf("The player wins %d points.\n", pt[0] + ct[0]);
            pp += pt[0] + ct[0];
        }
        if (pt[0] == ct[0])
        {
            printf("No one wins the point.\n");
        }
        if (pt[0] < ct[0])
        {
            printf("The computer wins %d points.\n", pt[0] + ct[0]);
            cp += pt[0] + ct[0];
        }
        temp += 4;
        if (temp >= 2 * n * n)
        {
            break;
        }
        printf("continue? ");
        scanf(" %c", &play);
        if (toupper(play) == 'N')
        {
            break;
        }
    }
    printf("The player gets total %d points.\nThe computer gets total %d points.\n", pp, cp);
    if (pp > cp)
    {
        printf("The player wins the game.\n");
    }
    if (pp == cp)
    {
        printf("No one wins the game.\n");
    }
    if (pp < cp)
    {
        printf("The computer wins the game.\n");
    }
}