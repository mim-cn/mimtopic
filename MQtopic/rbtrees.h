#ifndef RBTREES_H
#define RBTREES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#ifdef  __cplusplus
extern "C" {
#endif

#include "rbtree.h"
typedef struct __rbnode
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
    typedef std::list<rbnode*> lrbnode;
public:
    rbtrees();
    ~rbtrees();
public:
    void    insert(const void* content, int size);
    void    erase(const void *cnt);
    void    erase(rbnode *node);
    rbnode* search(const void* content);
    void    traverse();
private:
    int     _insert(rbnode *data);
    void    _free(rbnode* node);
    rbnode* _search(rb_root_t *root, const void* content);
public:
    inline void* content(rb_node *node)
    {
        return (rb_entry(node, rbnode, _rbnode)->_data);
    }
private:
    lrbnode     _nodes;
    rb_root_t*  _root;
};

#endif // RBTREES_H
