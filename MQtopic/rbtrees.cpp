#include "rbtrees.h"

rbtrees::rbtrees():_num(0)
{
    _root = (rb_root_t*)malloc(sizeof(rb_root_t));
    memset(_root,0,sizeof(rb_root_t));
    _nodes = (rbnode**)malloc(sizeof(rbnode*));
}

void rbtrees::add(const void* content, int size)
{
    _nodes[_num] = (rbnode *)malloc(sizeof(rbnode));
    _nodes[_num]->_size = size;
    _nodes[_num]->_data = (char *)malloc(size);
    memcpy(_nodes[_num]->_data,content,size);
    this->insert(_nodes[_num]);
    _num++;
}

int  rbtrees::insert(rbnode *data)
{
    rb_node_t **newnode = &(_root->rb_node), *parent = NULL;
    /* Figure out where to put new node */
    while (*newnode) {
        rbnode *here = container_of(*newnode, rbnode, _rbnode);
        int result = memcmp(data->_data,here->_data,here->_size);
        parent = *newnode;
        if (result < 0)
            newnode = &((*newnode)->rb_left);
        else if (result > 0)
            newnode = &((*newnode)->rb_right);
        else
            return 0;
    }
    /* Add new node and rebalance tree. */
    rb_link_node(&data->_rbnode , parent, newnode);
    rb_insert_color(&data->_rbnode, _root);
    return 1;
}

void rbtrees::erase(const void *cnt)
{
    rbnode* data = _search(_root, cnt);
    if (data) {
        rb_erase(&data->_rbnode, _root);
        this->freeNode(data);
    }
}

void rbtrees::freeNode(rbnode* node)
{
    if (node != NULL) {
        if (node->_data  != NULL) {
            free(node->_data);
            node->_data = NULL;
            node->_size = 0;
        }
        free(node);
        node = NULL;
    }

}

rbnode* rbtrees::_search(rb_root_t *root, const void* content)
{
    rb_node_t *node = root->rb_node;
    while (node) {
        rbnode *data = container_of(node, rbnode, _rbnode);
        int result;
        result = memcmp(content, data->_data,data->_size);
        if (result < 0)
            node = node->rb_left;
        else if (result > 0)
            node = node->rb_right;
        else
            return data;
    }
    return NULL;
}

rbnode* rbtrees::search(const void* content)
{
    return _search(_root,content);
}

void    rbtrees::traverse()
{
    rb_node *node;
    printf("search all nodes: \n");
    for (node = rb_first(_root); node; node = rb_next(node)){
        printf("%d ", *(int*)content(node));
    }
    printf("\n");
}
