#include <stdio.h>
#include <stdlib.h>

struct arch {
    int nodeFrom;
    unsigned traversed;
    int nodeTo;
    struct arch *next;
};

struct analyzer {
    int nodeName;
    int outs;
    int ins;
    struct analyzer *next;
};


void incrementAnalysis(struct arch node, struct analyzer *data, int nodesCount) {
    int i = 0;
    int checkFrom = 0, checkTo = 0;
    while (((data[i].nodeName != node.nodeTo) || (data[i].nodeName != node.nodeFrom)) && (i < nodesCount)) {
        if (data[i].nodeName == node.nodeTo) {
            data[i].ins++;
            checkTo = 1;
        }
        if (data[i].nodeName == node.nodeFrom) {
            data[i].outs++;
            checkFrom = 1;
        }
        i++;
    }
    if (i == nodesCount) {
        i = 0;
        while (data[i].nodeName != 0)
            i++;
    }
    if (i == 0) {
        data[i].nodeName = node.nodeTo;
        data[i].outs = 0;
        data[i].ins = 1;
        i++;
        data[i].nodeName = node.nodeFrom;
        data[i].outs = 1;
        data[i].ins = 0;
        return;
    }
    if (checkFrom == 0) {
        data[i].nodeName = node.nodeFrom;
        data[i].outs = 1;
        data[i].ins = 0;
        i++;
    }
    if (checkTo == 0) {
        data[i].nodeName = node.nodeTo;
        data[i].outs = 0;
        data[i].ins = 1;
    }
}

int checkIfPossible(struct analyzer *data, int nodeCount) {
    int i = 0, counter = 0;
    struct analyzer * temp;
    temp=data;
    while (i < nodeCount) {
        if (temp->ins - temp->outs != 0)
            counter++;
        i++;
        temp=temp->next;
    }
    free(temp);
    if (counter < 3)
        return 1;
    return 0;
}

int findStart(struct analyzer *arches, int nodeCount) {
    int i = 0;
    struct analyzer * temp;
    temp=arches;
    int archName, flagS, archBackup, flagB;
    while (i < nodeCount) {
        if (temp->ins > temp->outs) {
            archName = temp->nodeName;
            flagS = 1;
        }
        if (temp->ins == temp->outs) {
            archBackup = temp->nodeName;
            flagB = 1;
        }
        temp=temp->next;
        i++;
    }
    free(temp);
    if (flagS)
        return archName;
    if (flagB)
        return archBackup;
    return 0;
}

int findEnd(struct analyzer *arches, int nodeCount) {
    int i = 0;
    struct analyzer * temp;
    temp=arches;
    int archName, flagS, archBackup, flagB;
    while (i < nodeCount) {
        if (temp->ins < temp->outs) {
            archName = temp->nodeName;
            flagS = 1;
        }
        if (temp->ins == temp->outs) {
            archBackup = temp->nodeName;
            flagB = 1;
        }
        temp=temp->next;
        i++;
    }
    free(temp);
    if (flagS)
        return archName;
    if (flagB)
        return archBackup;
    return 0;
}

void findPath(struct arch *arches, int *tPath, int *ePath, int nodeCount, int archesCount) {
    int i = 0, counter = 0, pos = 1;
    struct arch * temp;
    temp=arches;
    while (pos < nodeCount) {
        while (((tPath[pos] != temp->nodeFrom) || (temp->traversed != 0)) &&
               (counter < archesCount))
            counter++;
        if (counter == archesCount) {
            counter = 0;
            ePath[i] = tPath[pos];
            tPath[pos] = 0;
            i++;
        } else {
            tPath[pos + 1] = temp->nodeTo;
            temp->traversed = 1;
            counter = 0;
            pos++;
        }
        temp=temp->next;
    }
}

void addArch(struct arch **arches, int nodeFrom, int nodeTo){
    struct arch *temp1;
    struct arch *temp = (struct arch *)malloc(sizeof(struct arch));
    struct arch *newNode = (struct arch *)malloc(sizeof(struct arch));
    newNode->nodeTo = nodeTo;
    newNode->nodeFrom = nodeFrom;
    newNode->traversed = 0;
    newNode->next=NULL;
    temp1=*arches;
    while(&(*arches)->next){
        *temp = *temp1;
        *temp1 = *(*arches)->next;
    }
    *temp->next=*newNode;
    free(temp);
    free(temp1);
}

void addAnNode(struct analyzer **nodes, int nodeName, int outs, int ins) {
    struct analyzer *temp1;
    struct analyzer *newNode = (struct analyzer *) malloc(sizeof(struct analyzer));
    struct analyzer *temp = (struct analyzer *) malloc(sizeof(struct analyzer));
    newNode->nodeName = nodeName;
    newNode->outs = outs;
    newNode->ins = ins;
    newNode->next = NULL;
    temp1=*(nodes);
    while (&(*nodes)->next) {
        *temp = *temp1;
        *temp1 = *(*nodes)->next;
    }
    *temp->next = *newNode;
    free(temp);
    free(temp1);
}

int main() {
    int archesCount, nodesCount, starting, ending;
    printf("Insert arches count,\n"
           "NB: if you have a node connected to itself, that arch counts as 2\n");
    scanf("%d", &archesCount);
    printf("Insert nodes count\n");
    scanf("%d", &nodesCount);
    int *tPath = (int *) malloc(sizeof(int) * archesCount);
    int *ePath = (int *) malloc(sizeof(int) * archesCount);
    struct arch **arches = (struct arch **) malloc(sizeof(struct arch) * archesCount);
    struct analyzer **data = (struct analyzer **) malloc(sizeof(struct analyzer) * nodesCount);

    for (int k = 0; k < nodesCount; k++) {
        addAnNode(data, 0, 0, 0);
    }

    int i = 0, count = 0, nodeF, nodeT;
    printf("NB: a node name cannot be 0 AND two nodes cannot share the same name\n");
    while (i < archesCount) {
        printf("Insert starting node name:\n");
        scanf("%d", &nodeF );
        printf("Insert arriving node name:\n");
        scanf("%d", &nodeT );
        if ((*arches)->nodeFrom == (*arches)->nodeTo )
            i++;
        addArch(arches, nodeF, nodeT);
        incrementAnalysis(**arches, *data, nodesCount);
        count++;
        i++;
    }

    if (checkIfPossible(*data, nodesCount) != 0) {
        starting = findStart(*data, nodesCount);
        ending = findEnd(*data, nodesCount);
        tPath[0] = starting;
        findPath(*arches, tPath, ePath, nodesCount, archesCount);
        printf("Starting node: %d \n", starting);
        printf("Ending node: %d \n", ending);
        printf("Sequence: ");
        i = archesCount - 1;
        while (i > 0) {
            printf("%d ", ePath[i]);
            i--;
        }
    } else {
        printf("Not Possible!");
    }
    return 0;
}
