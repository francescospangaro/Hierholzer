#include <stdio.h>
#include <stdlib.h>

struct arch{
    int nodeFrom;
    unsigned traversed;
    int nodeTo;
};

struct analyzer{
    int nodeName;
    int outs;
    int ins;
};

struct arch pop(struct arch *stack);
int push(struct arch *stack, struct node toPush);
struct arch top(struct arch *stack);


int main() {
    int archesCount, last=-1, nodesCount;
    printf("Insert arches count,\n"
           "NB: if you have a node connected to itself, that arch counts as 2\n");
    scanf("%d", &archesCount);
    printf("Insert nodes count\n");
    scanf("%d", &nodesCount);
    struct arch *tPath = (struct node *)malloc(sizeof(struct arch)*archesCount);
    struct arch *ePath = (struct node *)malloc(sizeof(struct arch)*archesCount);
    struct arch *arches = (struct node *)malloc(sizeof(struct arch)*archesCount);
    struct analyzer *data = (struct analyzer *)malloc(sizeof(struct analyzer)*nodesCount);

    int nodeFrom, nodeTo,i=0,count=0;
    while(i<archesCount){
        printf("Insert starting node name:\n");
        scanf("%d", &nodeFrom);
        printf("Insert arriving node name:\n");
        scanf("%d", &nodeTo);
        if(nodeFrom==nodeTo)
            i++;
        arches[count].nodeFrom=nodeFrom;
        arches[count].nodeTo=nodeTo;
        arches[count].traversed=0;
        count++;
        i++;
        if(!data[0].ins){
            data[0].nodeName=nodeTo;
            data[0].ins=1;
            data[0].outs=0;
            data[1].nodeName=nodeFrom;
            data[0].ins=0;
            data[0].outs=1;
        }

    }




    return 0;
}
