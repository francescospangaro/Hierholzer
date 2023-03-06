#include <stdio.h>
#include <stdlib.h>

struct arch {
    int nodeFrom;
    unsigned traversed;
    int nodeTo;
};

struct analyzer {
    int nodeName;
    int outs;
    int ins;
};


void incrementAnalysis(struct arch node, struct analyzer *data) {
    int i = 0;
    int checkFrom = 0, checkTo = 0;
    while ((data[i].nodeName != node.nodeTo) || (data[i].nodeName != node.nodeFrom)) {
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
        i++;
        data[i].nodeName = node.nodeFrom;
        data[i].outs = 1;
        data[i].ins = 0;
    }
    if (checkTo == 0) {
        i++;
        data[i].nodeName = node.nodeTo;
        data[i].outs = 0;
        data[i].ins = 1;
    }
}

int checkIfPossible(struct analyzer *data, int nodeCount) {
    int i = 0, counter = 0;
    while (i < nodeCount) {
        if (data[i].ins - data[i].outs != 0)
            counter++;
        i++;
    }
    if (counter < 3)
        return 1;
    return 0;
}

int findStart(struct analyzer *arches, int nodeCount) {
    int i = 0;
    int archName, flagS, archBackup, flagB;
    while (i < nodeCount) {
        if (arches[i].ins > arches[i].outs) {
            archName = arches[i].nodeName;
            flagS = 1;
        }
        if (arches[i].ins == arches[i].outs) {
            archBackup = arches[i].nodeName;
            flagB = 1;

        }
        i++;
    }
    if (flagS)
        return archName;
    if (flagB)
        return archBackup;
    return 0;
}

int findEnd(struct analyzer *arches, int nodeCount) {
    int i = 0;
    int archName, flagS, archBackup, flagB;
    while (i < nodeCount) {
        if (arches[i].ins < arches[i].outs) {
            archName = arches[i].nodeName;
            flagS = 1;
        }
        if (arches[i].ins == arches[i].outs) {
            archBackup = arches[i].nodeName;
            flagB = 1;
        }
        i++;
    }
    if (flagS)
        return archName;
    if (flagB)
        return archBackup;
    return 0;
}

void findPath(struct arch *arches, int *tPath, int *ePath, int nodeCount, int archesCount) {
    int i = 0, counter = 0, pos = 1;
    while (pos < nodeCount - 1) {
        while (((tPath[pos] != arches[counter].nodeFrom) || (arches[counter].traversed != 0)) &&
               (counter < archesCount))
            counter++;
        if (counter == archesCount) {
            ePath[i] = tPath[pos];
            tPath[pos] = 0;
            i++;
        } else {
            tPath[pos + 1] = arches[counter].nodeTo;
            arches[counter].traversed = 1;
            counter = 0;
            pos++;
        }
    }
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
    struct arch *arches = (struct arch *) malloc(sizeof(struct arch) * archesCount);
    struct analyzer *data = (struct analyzer *) malloc(sizeof(struct analyzer) * nodesCount);

    int i = 0, count = 0;
    printf("NB: a node name cannot be 0 AND two nodes cannot share ethe same name\n");
    while (i < archesCount) {
        printf("Insert starting node name:\n");
        scanf("%d", &arches[count].nodeFrom);
        printf("Insert arriving node name:\n");
        scanf("%d", &arches[count].nodeTo);
        if (arches[count].nodeFrom == arches[count].nodeTo)
            i++;
        arches[count].traversed = 0;
        count++;
        i++;
    }
    incrementAnalysis(arches[count], data);
    if (checkIfPossible(data, nodesCount) != 0) {
        starting = findStart(data, nodesCount);
        ending = findEnd(data, nodesCount);
        tPath[0] = starting;
        findPath(arches, tPath, ePath, nodesCount, archesCount);
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
