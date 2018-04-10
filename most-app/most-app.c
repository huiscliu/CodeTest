
#include "most-app.h"

/* sort Pair */
int pair_cmp(const void *ag1, const void *ag2)
{
    return strcmp(((const Pair *)ag1)->att, ((const Pair *)ag2)->att);
}

/* sort appear times: reverse order */
int pair_num_cmp(const void *ag1, const void *ag2)
{
    return ((const Pair *)ag2)->size - ((const Pair *)ag1)->size;
}

/* sort excluding */
int string_cmp(const void *ag1, const void *ag2)
{
    return strcmp(*(const char **)ag1, *(const char **)ag2);
}

BdAry * bdary_find_most_appear(char *text, BdAry *ecd)
{
    BdAry *rlt = NULL;
    char *p;
    Pair *st; /* sorted text */
    Pair *h;
    int k, m, i;

    /* check pars */
    if (ecd != NULL && ecd->size > 0) assert(ecd->att != NULL);

    /* special case */
    rlt = calloc(1, sizeof(*rlt));
    if (text == NULL) {
        return rlt;
    }

    /* memory */
    m = 100;
    k = 0;
    st = malloc(m * sizeof(*st));
    if (st == NULL) {
        fprintf(stderr, "memory allocation error, line: %d\n", __LINE__);
    }

    /* parse */
    p = strtok(text, " ");
    
    while (p != NULL) {
        /* dynamic mem */
        if (k >= m) {
            m += 20;

            st = realloc(st, m * sizeof(*st));
            if (st == NULL) {
                fprintf(stderr, "memory allocation error, line: %d\n", __LINE__);
            }
        }

        /* assign */
        st[k].size = 1;
        st[k].att = p;

        /* next word */
        k++;
        p = strtok(NULL, " ");
    }

    /* sort texts */
    qsort(st, k, sizeof(*st), pair_cmp);

    /* get size of each word */
    h = st;

    /* numer of uniq words */
    m = 1;
    for (i = 1; i < k; i++) {
        if (strcmp(h->att, st[i].att) == 0) {
            h->size += 1;
        }
        else { /* found new word */
            if (m != i) {
                st[m] = st[i];
            }

            h = st + m;
            m++;
        }
    }

    /* sort texts */
    qsort(st, m, sizeof(*st), pair_num_cmp);

    fprintf(stderr, "-------------- sorted texts -------------\n");
    for (i = 0; i < m; i++) {
        fprintf(stderr, "%s %d\n", st[i].att, st[i].size);
    }
    fprintf(stderr, "-----------------------------------------\n");

    /* exclude */
    if (ecd != NULL && ecd->size > 0) {
        qsort(ecd->att, ecd->size, sizeof(*ecd->att), string_cmp);
    }

    /* init */
    k = -1;
    rlt->size = 0;
    rlt->att = malloc(m * sizeof(char *));

    if (rlt == NULL) {
        fprintf(stderr, "memory allocation error, line: %d\n", __LINE__);
    }

    for (i = 0; i < m; i++) {
        /* search if exclude */
        if (ecd == NULL || ecd->size <= 0) {
            p = NULL;
        }
        else {
            p = bsearch(&st[i].att, ecd->att, ecd->size, sizeof(*ecd->att), string_cmp);
        }

        if (p != NULL) { /* to exclude */
            continue;
        }
        else { /* to include */
            if (k < 0) { /* not initialized yet */
                k = st[i].size;
                rlt->att[rlt->size] = strdup(st[i].att);
                rlt->size += 1;
            }
            else if (st[i].size == k) {
                rlt->att[rlt->size] = strdup(st[i].att);
                rlt->size += 1;
            }
            else {
                break;
            }
        }
    }

    /* clean mess */
    free(st);
    rlt->att = realloc(rlt->att, rlt->size * sizeof(*rlt->att));

    return rlt;
}

int main()
{
    BdAry ecd;
    BdAry *rlt;
    int i;

    /* case 1 */
    {
        char test1[] = "jack said jack and jill were trying to find a hill named jack and jill";

        ecd.size = 5;
        ecd.att = malloc(ecd.size * sizeof(*ecd.att));
        if (ecd.att == NULL) {
            fprintf(stderr, "memory allocation error, line: %d\n", __LINE__);
        }

        ecd.att[0] = "a";
        ecd.att[1] = "are";
        ecd.att[2] = "the";
        ecd.att[3] = "an";
        ecd.att[4] = "is";

        printf("case 1, input text: %s\n", test1);
        printf("case 1, to exclude: ");
        for (i = 0; i < ecd.size; i++) {
            printf("%s ", ecd.att[i]);
        }
        printf("\n");

        rlt = bdary_find_most_appear(test1, &ecd);
        printf("\n** results: ");
        for (i = 0; i < rlt->size; i++) {
            printf("%s ", rlt->att[i]);
            free(rlt->att[i]);
        }
        printf("\n");

        free(rlt->att);
        free(rlt);
        free(ecd.att);
    }

    /* case 2 */
    {
        char test2[] = "hi jack and jill are trying to find a hill named jack jill a a a a a"
            " a a a b b b b b c c c c c";

        ecd.size = 7;
        ecd.att = malloc(ecd.size * sizeof(*ecd.att));
        if (ecd.att == NULL) {
            fprintf(stderr, "memory allocation error, line: %d\n", __LINE__);
        }

        ecd.att[0] = "are";
        ecd.att[1] = "the";
        ecd.att[2] = "hi";
        ecd.att[3] = "is";
        ecd.att[4] = "a";
        ecd.att[5] = "b";
        ecd.att[6] = "c";

        printf("\ncase 2, input text: %s\n", test2);
        printf("case 2, to exclude: ");
        for (i = 0; i < ecd.size; i++) {
            printf("%s ", ecd.att[i]);
        }
        printf("\n");

        rlt = bdary_find_most_appear(test2, &ecd);
        printf("\n** results: ");
        for (i = 0; i < rlt->size; i++) {
            printf("%s ", rlt->att[i]);
            free(rlt->att[i]);
        }
        printf("\n");

        free(rlt->att);
        free(rlt);
        free(ecd.att);
    }

    /* case 3 */
    {
        char test3[] = "jack said jack and jill were trying to find a hill named jack and jill jill";

        printf("\ncase 3, input text: %s\n", test3);
        printf("case 3, to exclude: \n");

        rlt = bdary_find_most_appear(test3, NULL);
        printf("\n** results: ");
        for (i = 0; i < rlt->size; i++) {
            printf("%s ", rlt->att[i]);
            free(rlt->att[i]);
        }
        printf("\n");

        free(rlt->att);
        free(rlt);
    }

    return 0;
}
