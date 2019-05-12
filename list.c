#include "stdlib.h"
#include "stdio.h"
#include "list.h"
#include "item.h"

List *makeList() {
    List *list = malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void add(WoWMounts *mount, List *list) {
    WoWMounts *current = NULL;
    mount->next = NULL;
    mount->id = 0;

    if (list->head == NULL) {
        list->head = mount;
    } else {
        mount->id++;
        current = list->head;
        while (current->next != NULL) {
            mount->id++;
            current = (WoWMounts *) current->next;
        }
        mount->prev = (struct WoWMounts *) current;
        current->next = (struct WoWMounts *) mount;
    }
}

void addToPreLast(WoWMounts *mount, List *list) {
    WoWMounts *current = NULL;
    WoWMounts *nextMount = NULL;
    mount->next = NULL;
    mount->id = 0;

    if (list->head == NULL) {
        list->head = mount;
    } else {
        mount->id++;
        current = list->head;

        if(current->next == NULL) {
            nextMount = (WoWMounts *) current;
        }
        else {
            nextMount = (WoWMounts *) current->next;
        }

        while (nextMount->next != NULL) {
            mount->id++;
            current = (WoWMounts *) current->next;
            nextMount = (WoWMounts *) nextMount->next;
        }

        if(nextMount == current) {
            list->head = mount;
            mount->next = (struct WoWMounts *) current;
        }
        else {
            current->next = (struct WoWMounts *) mount;
            mount->next = (struct WoWMounts *) nextMount;
        }
        int k = 0;
    current = list->head;
    int l = 0;
    while (current != NULL)
    {
        l++;
        current = (WoWMounts *) current->next;
    }
    printf("%d", l);
    current = list->head;
    while (current != NULL)
    {
        if (k == 1)
            current->id = l-1;
        if (current->id == l-2)
            k = 1;
        current = (WoWMounts *) current->next;
    }
    }
}

WoWMounts *get(int id, List *list) {
    WoWMounts *current = list->head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = (WoWMounts *) current->next;
    }
    return NULL;
}

int DeletePrevious(int id, List *list) {
    WoWMounts *current = list->head;
    WoWMounts *previous = current;
    id--;
    int c = 0;
    if (id != -1)
    {
    while (current != NULL) {
        if (current->id == id) {
            previous->next = current->next;
            if (current == list->head)
                list->head = (WoWMounts *) current->next;
            free(current);
            current = (WoWMounts *) previous;
            c++;
        }
        previous = current;
        current = (WoWMounts *) current->next;
    }
    }
    else
        printf("You can't do it, there is no mount with Id = -1, please choose another Id");
    return c;
}

void display(List *list) {
    WoWMounts *current = list->head;
    if (current == NULL) {
        printf("List is empty\n");
        return;
    }

    while (current != NULL) {
        printf("Id: %d\nCost: %d\nName: %s\nQuest: %s\nAchievement: %s\nDrop from: %s\nDrop chance: %lf\nAddition: %s\nLocation: %s\nPercent of holders: %lf\nSubjective rate: %d\n\n",
               current->id,current->cost, current->name, current->quest, current->achieve, current->drop, current->chance, current->addon, current->where, current->holders, current->rate);
        current = (WoWMounts *) current->next;
    }
}

void destroy(List *list) {
    WoWMounts *current = list->head;
    WoWMounts *next = current;
    while (current != NULL) {
        next = (WoWMounts *) current->next;
        free(current);
        current = next;
    }
    free(list);
}
