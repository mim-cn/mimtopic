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
#include <string.h>
typedef unsigned char level;

typedef struct __topic
{
    /* topic level id */
    level*    _tids;
    /* topic name */
    char*     _name;
}Topic;

#define tfree(p)          if(p) { free(p); p = NULL;}
#define topic_new         ((Topic*)calloc(1,sizeof(Topic)))
#define topic_free(t)     if(t) {tfree(t->_name); tfree(t->_tids);free(t);t = NULL;}
#define topic_cmp(t1, t2) (strcmp(t1->_name,t2->_name))
#define topic_lev(t)      (t._tids)
#define topic_name(t)     (t._name)

typedef struct __rbnode
{
    rb_node_t _rbnode;
    Topic*    _hook;
}rbnode;

#define hook(prb)       (prb->_hook)
#define hook_lev(prb)   (hook(prb)->_tids)
#define hook_name(prb)  (hook(prb)->_name)

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
    void    insert(const char* content, int size);
    void    erase(const char* cnt);
    void    erase(rbnode *node);
    rbnode* search(const char* content);
    void    traverse(const char* content);
    void    traverse();
private:
    int     _insert(rbnode *data);
    void    _free(rbnode* node);
    rbnode* _search(rb_root_t *root, const char* content);
    void    _traverse(rb_root_t *root);
private:
    lrbnode     _nodes;
    rb_root_t*  _root;
};

#endif // RBTREES_H
