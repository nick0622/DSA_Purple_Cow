#include <stdio.h>
#include <stdlib.h> // malloc / free
#include <memory.h> // memset

// flag =1 => upload judge
int flag = 0;
// M bathrooms, N situations and K groups
int M, N, K;

typedef struct node
{
    int id;
    int group;
    struct node *nxt;
    struct node *pre;
} node;

node **head;
node **tail;

node *alloc(int id, int group)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->id = id;
    tmp->group = group;
    return tmp;
}

void destory(node *head)
{
    if (head != NULL)
    {
        destory(head->nxt);
        // clean sensitive data.
        memset(head, 0, sizeof(node));
        free(head);
    }
}

void enter(int i, int j, int m)
{
    node *tmp = tail[m];
    node *USB = alloc(j, i);
    if (tmp == NULL)
    {
        // empty toilet
        USB->nxt = NULL;
        USB->pre = NULL;
        head[m] = USB;
        tail[m] = USB;
    }
    else
    {
        while (1)
        {
            if (tmp->group == i)
            {
                // find same group
                if (tmp->nxt == NULL)
                {
                    // at the end of line
                    tail[m] = USB;
                    USB->nxt = NULL;
                    USB->pre = tmp;
                    tmp->nxt = USB;
                    break;
                }
                else
                {
                    USB->nxt = tmp->nxt;
                    USB->pre = tmp;
                    tmp->nxt->pre = USB;
                    tmp->nxt = USB;
                    break;
                }
            }
            else if (tmp->pre == NULL)
            {
                // do not find same group till the first node in line
                USB->nxt = NULL;
                USB->pre = tail[m];
                tail[m]->nxt = USB;
                tail[m] = USB;
                break;
            }
            else
                tmp = tmp->pre;
        }
    }
}

void leave(int m)
{
    if (tail[m]->pre == NULL)
    {
        // only one node
        head[m] = NULL;
        tail[m] = NULL;
    }
    else
    {
        tail[m] = tail[m]->pre;
        tail[m]->nxt->pre = NULL;
        tail[m]->nxt = NULL;
    }
}

void go(int m)
{
    if (head[m]->nxt == NULL)
    {
        // only one node
        head[m] = NULL;
        tail[m] = NULL;
    }
    else
    {
        head[m] = head[m]->nxt;
        head[m]->pre->nxt = NULL;
        head[m]->pre = NULL;
    }
}

void close(int m)
{
}

void Print_Output()
{
    for (int m = 0; m < M; m++)
    {
        node *tmp = head[m];
        if (tmp == NULL)
        {
            // printf("head : %p ", head[m]);
            // printf("tail : %p ", tail[m]);
            printf("\n");
        }
        else
        {
            while (tmp != NULL)
            {
                printf("%d ", (tmp->id));
                // printf("now : %p ", tmp);
                // printf("next : %p ", tmp->nxt);
                // printf("pre : %p ", tmp->pre);
                tmp = tmp->nxt;
            }
            // printf("tail : %p ", tail[m]);
            printf("\n");
        }
    }
}

int main()
{
    FILE *fp;
    fp = fopen("D:\\nick\\Homework\\Senior\\DSA\\Homework\\b07501117\\3\\test\\0.in", "r");
    if (flag)
        scanf("%d %d %d", &M, &N, &K);
    else
        fscanf(fp, "%d %d %d", &M, &N, &K);
    head = malloc(sizeof(node *) * M);
    for (int m = 0; m < M; m++)
    {
        head[m] = NULL;
    }
    tail = malloc(sizeof(node *) * M);
    for (int m = 0; m < M; m++)
    {
        tail[m] = NULL;
    }

    for (int n = 0; n < N; n++)
    {
        char sit[6];
        //  group i, id j, line m
        int i, j, m;
        if (flag)
            scanf("%s", sit);
        else
            fscanf(fp, "%s", sit);
        switch (sit[0])
        {
        case 'e':
            if (flag)
                scanf("%d %d %d", &i, &j, &m);
            else
                fscanf(fp, "%d %d %d", &i, &j, &m);
            enter(i, j, m);
            break;
        case 'l':
            if (flag)
                scanf("%d", &m);
            else
                fscanf(fp, "%d", &m);
            leave(m);
            break;
        case 'g':
            if (flag)
                scanf("%d", &m);
            else
                fscanf(fp, "%d", &m);
            go(m);
            break;
        case 'c':
            if (flag)
                scanf("%d", &m);
            else
                fscanf(fp, "%d", &m);
            // close(m);
            break;
        default:
            break;
        }
    }
    Print_Output();
    fclose(fp);
    return 0;
}