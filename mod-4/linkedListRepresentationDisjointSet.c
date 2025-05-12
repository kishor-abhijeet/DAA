struct set_header
{
    int weight;
    struct set_object *head;     // **Pointer to first node in the list**
    struct set_object *tail;     // **Pointer to last node in the list**
};

struct set_object
{
    int item;
    struct set_object *next;     // **Pointer to next element in the list**
    struct set_header *back;     // **Pointer to the header of the set**
};

void union(struct set_object *a, struct set_object *b)
{
    if (a->back->weight < b->back->weight)  // **Compare weights to attach smaller to larger set**
    {
        // implementation NOT required
    }
    else
    {
        // **Attach b's list to end of a's list**
        a->back->tail->next = b->back->head;

        // **Update back pointer of each node in b’s list to point to a's header**
        struct set_object *temp = b->back->head;
        while (temp != NULL)
        {
            temp->back = a->back;
            temp = temp->next;
        }

        // **Update tail of the new merged list**
        a->back->tail = b->back->tail;

        // **Update weight of the merged set**
        a->back->weight += b->back->weight;
    }
}
