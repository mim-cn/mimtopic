#include "rbtrees.h"

rbtrees::rbtrees()
{
    _root = (rb_root_t*)malloc(sizeof(rb_root_t));
    /* This clear is very important */
    memset(_root,0,sizeof(rb_root_t));
}

rbtrees::~rbtrees()
{
    if(_root){
        rb_node_t *node = rb_first(_root), *next = NULL ;
        while (node) {
            next = rb_next(node);
            rbnode *rbn = rb_entry(node,rbnode,_rbnode);
            if (rbn) {
                this->erase(rbn);
            }
            node = next;
        }
        free(_root);
        _root = NULL;
        printf("delete all nodes OK \n");
    }
}

void rbtrees::insert(const void* content, int size)
{
    rbnode* node = (rbnode *)malloc(sizeof(rbnode));
    node->_size = size;
    node->_data = (char *)malloc(size);
    memcpy(node->_data,content,size);
    _nodes.push_back(node);
    /* insert failed, must free node memory */
    if(! this->_insert(node)){
        free(node->_data);
        node->_data = NULL;
        free(node);
        node = NULL;
    }
}

int  rbtrees::_insert(rbnode *data)
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
        this->_free(data);
    }
}

void rbtrees::erase(rbnode *node)
{
    if(node){
        rb_erase(&node->_rbnode, _root);
        this->_free(node);
    }
}

void rbtrees::_free(rbnode* node)
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

void rbtrees::traverse(const void* content)
{
    rbnode* rootnode = this->_search(_root,content);
    rb_root_t* root = (rb_root_t*)malloc(sizeof(rb_root_t));
    root->rb_node = &rootnode->_rbnode;
    this->_traverse(root);
    free(root);
    root = NULL;
}

void rbtrees::traverse()
{
    this->_traverse(_root);
}

void rbtrees::_traverse(rb_root_t *root)
{
    rb_node_t *node = rb_first(root);
    while (node) {
        rbnode *rbn = rb_entry(node, rbnode, _rbnode);
        printf("%d ", *(int*)(rbn->_data));
        node = rb_next(node);
    }
    printf("\n");
}
