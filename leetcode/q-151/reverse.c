
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void reverse_a_word(char *s)
{
    int i;
    int len, k;
    
    /* special case */
    if (s == NULL) return;
    
    len = strlen(s);
    k = len / 2;
    for (i = 0; i < k; i++) {
        char p;
        
        p = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = p;
    }
}

void reverseWords(char *s)
{
    int len, i;
    char *p;
    int k;
    
    if (s == NULL) return;
    
    len = strlen(s);
    reverse_a_word(s);
    
    p = strtok(s, " ");
    while (p != NULL) {
        reverse_a_word(p);
        p = strtok(NULL, " ");
    }
    
    for (i = 0; i < len; i++) {
        if (s[i] == '\0') s[i] = ' ';
    }
    
    /* remove midium spaces */
    p = strtok(s, " ");
    k = 0;
    while (p != NULL) {
        char *p1 = strtok(NULL, " ");

        len = strlen(p);
        memmove(s + k, p, len + 1);
        k += len;
        if (p1 != NULL) s[k] = ' ';

        /* make room for space */
        k++;

        p = p1;
    }

    /* special case */
    if (k == 0) {
        len = strlen(s);
        for (i = 0; i < len; i++) {
            if (isspace(s[i])) {
                s[i] = '\0';
                break;
            }
        }
    }
}

int main()
{
    char s[] =  "    hi    this   is a  short    sentence    ";

    printf("input: %s\n", s);

    reverseWords(s);

    printf("new: %s\n", s);

    return 0;
}
