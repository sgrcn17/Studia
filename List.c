#include <stdio.h>
#include <malloc.h>

struct student{
    double grade;
    char *lastname;
    struct student* next;
};

int CompareStrings(char *s1, char *s2)
{
    if(sizeof(s1) != sizeof(s2)) return 0;
    for(int i = 0 ; i < sizeof(s1)/sizeof(char) ; ++i)
    {
        if(s1[i] != s2[i]) return 0;
    }
    return 1;
}

void AddToList(struct student **list, char *lastname, double grade)
{
    struct student *new, *p = *list;
    new = malloc(sizeof(struct student));
    new->lastname = lastname;
    new->grade = grade;
    new->next = 0;
    if(p==0) *list = new;
    else
    {
        while(p->next) p = p->next;
        p->next = new;
    }
}

void PutToSortedList(struct student **list, char *lastname, double grade)
{
    struct student *new, *p = *list;
    new = malloc(sizeof(struct student));
    new->lastname = lastname;
    new->grade = grade;
    if(p == 0 || grade < p->grade)
    {
        new->next = p;
        *list = new;
    }
    else
    {
        while(p->next != 0 && grade > p->next->grade) p = p->next;
        new->next = p->next;
        p->next = new;
    }
}

void PrintList(struct  student *list)
{
    while(list)
    {
        printf("%s : %lf\n", list->lastname, list->grade);
        list = list->next;
    }
}

void DeleteGrade(struct student **list, char *lastname, double grade)
{
    struct student *copy, *p = *list;
    if(p==0) return;
    if(grade == p->grade && CompareStrings(lastname, p->lastname))
    {
        *list = p->next;
        free(p);
    }
    else
    {
        while(p->next != 0 && (grade != p->next->grade || !CompareStrings(lastname, p->next->lastname))) p = p->next;
        if(p->next!=0 && grade == p->next->grade && CompareStrings(lastname, p->next->lastname))
        {
            copy = p->next;
            p->next = p->next->next;
            free(copy);
        }
    }
}

struct student *Find(struct student *list, char *lastname, double grade)
{
    while(list && (!CompareStrings(lastname, list->lastname) || list->grade != grade)) list = list->next;
    return list;
}

struct student *CopyList(struct student *list)
{
    struct student *new, *previous, *secondList = 0;
    while(list)
    {
        new = malloc(sizeof(struct student));
        new->grade = list->grade;
        new->lastname = list->lastname;
        if(secondList==0)secondList=new;
        else previous->next = new;
        previous = new;
        list = list->next;
    }

    if(secondList) new->next=0;
    return secondList;
}

struct student *AddLists(struct student *firstList, struct student *secondList)
{
    struct student *copy1, *copy2, *p;
    copy1 = CopyList(firstList);
    copy2 = CopyList(secondList);
    if(copy1==0)return copy2;
    p = copy1;
    while(p->next) p = p->next;
    p->next = copy2;
    return copy1;
}

void ClearMemoryOfLists(struct student *list)
{
    struct student *p, *itr = list;
    while (itr)
    {
        p = itr;
        itr = itr->next;
        free(p);
    }
}

int main(void)
{
    struct student *list = 0, *st;
    PutToSortedList(&list, "b",3);
    PutToSortedList(&list, "c", 2);
    PutToSortedList(&list, "a", 1);
    DeleteGrade(&list, "a", 1);
    st = Find(list, "b", 3);
    if(st) st->grade = 4.0;
    struct student *list2 = CopyList(list);
    AddToList(&list2, "d", 5);
    struct student *list3 = AddLists(list2, list);
    PrintList(list3);
    ClearMemoryOfLists(list);
    ClearMemoryOfLists(list2);
    ClearMemoryOfLists(list3);
    return 0;
}