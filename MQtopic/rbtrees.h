#ifndef RBTREES_H
#define RBTREES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef  __cplusplus
extern "C" {
#endif
#include "rbtree.h"

typedef struct _rbnode
{
    rb_node_t _rbnode;
    void*     _data;
    int       _size;
}rbnode;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */


class rbtrees
{
public:
    rbtrees();
public:
    void    add(const void* content, int size);
    int     insert(rbnode *data);
    void    erase(const void *cnt);
    void    freeNode(rbnode* node);
    rbnode* search(const void* content);
    rbnode* _search(rb_root_t *root, const void* content);
    void    traverse();
public:
    inline void* content(rb_node *node)
    {
        return (rb_entry(node, rbnode, _rbnode)->_data);
    }
private:
    rbnode**    _nodes;
    rb_root_t*  _root;
    int         _num;
};

#endif // RBTREES_H
