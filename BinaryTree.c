#include <stdio.h>
#include <malloc.h>

struct node{
    double value;
    struct node *left, *right;
};

void PutToTree(struct node **root, double value)
{
    struct node *new, *p = *root, *next;
    new = malloc(sizeof(struct node));
    new->value = value;
    new->left = 0;
    new->right = 0;
    if(p==0) *root = new;
    else
    {
        while(1)
        {
            if(value < p->value)
            {
                if(p->left == 0)
                {
                    p->left = new;
                    break;
                }
                else p = p->left;
            }
            else
            {
                if(p->right == 0)
                {
                    p->right = new;
                    break;
                }
                p = p->right;
            }
        }
    }
}

void PrintTree(struct node *root)
{
    if(root==0) return;
    PrintTree(root->left);
    printf("%lf ", root->value);
    PrintTree(root->right);
}

struct node *Find(struct node *root, double value)
{
    struct node *acc = root;
    while(1)
    {
        if(acc == 0 || acc->value == value) return acc;
        else
        {
            if(value < acc->value) acc = acc->left;
            else acc = acc->right;
        }
    }
}

struct node *FindParent(struct node *root, double value)
{
    struct node *acc = root;
    while(1)
    {
        if(acc == 0 ||
        (acc->right!=0 && acc->right->value == value) ||
        (acc->left!=0 && acc->left->value == value)) return acc;
        else
        {
            if(value < acc->value) acc = acc->left;
            else acc = acc->right;
        }
    }
}

void AddNodeWithSubtreeToTree(struct node **root, struct node *_node)
{
    if(_node==0) return;
    PutToTree(root, _node->value);
    AddNodeWithSubtreeToTree(root, _node->left);
    AddNodeWithSubtreeToTree(root, _node->right);
}

void DeleteNode(struct node **root, double value)
{
    struct node *p = *root, *wanted, *pOfWanted;
    if(p == 0) return;
    else if(p->value == value)
    {
        *root = p->right;
        AddNodeWithSubtreeToTree(root, p->left);
        free(p);
    }
    else
    {
        wanted = Find(*root, value);
        pOfWanted = FindParent(*root, value);
        if(pOfWanted->left != 0 && pOfWanted->left->value == value) pOfWanted->left = 0;
        else pOfWanted->right = 0;
        AddNodeWithSubtreeToTree(root, wanted->left);
        AddNodeWithSubtreeToTree(root, wanted->right);
        free(wanted);
    }
}

void DeleteTree(struct node *root)
{
    if(root==0) return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    free(root);
}

struct node *CopyTree(struct node *root)
{
    if(root == 0) return 0;
    struct node *new;
    new = malloc(sizeof(struct node));
    new->value = root->value;
    new->left = CopyTree(root->left);
    new->right = CopyTree(root->right);
    return new;
}

struct node *AddTrees(struct node *firstRoot, struct node *secondRoot)
{
    struct node *firstCopy, *secondCopy;
    firstCopy = CopyTree(firstRoot);
    secondCopy = CopyTree(secondRoot);
    if(firstCopy==0) return secondCopy;
    AddNodeWithSubtreeToTree(&firstCopy, secondCopy);
    return firstCopy;
}

int main() {
    struct node *root = 0;
    PutToTree(&root, 3);
    PutToTree(&root, 1);
    PutToTree(&root, 5);
    PutToTree(&root, 7);
    PutToTree(&root, 6);
    PutToTree(&root, 8);
    PrintTree(root);
    DeleteNode(&root, 5);
    printf("\n");
    PrintTree(root);
    printf("\n");
    struct node *f = Find(root, 3);
    printf("%lf\n", f->value);

    struct node *root2 = CopyTree(root);
    PrintTree(root2);
    printf("\n");

    struct node *root3 = 0;
    PutToTree(&root3, 4);
    PutToTree(&root3, 1);
    PutToTree(&root3, 7);
    PutToTree(&root3, 3);
    PutToTree(&root3, 2);
    PutToTree(&root3, 2);

    struct node *root4 = AddTrees(root2, root3);
    PrintTree(root4);

    DeleteTree(root);
    DeleteTree(root2);
    DeleteTree(root3);
    DeleteTree(root4);
    return 0;
}