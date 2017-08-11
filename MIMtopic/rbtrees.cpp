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

void rbtrees::insert(const char* content, int size)
{
    rbnode* node = (rbnode *)malloc(sizeof(rbnode));
    hooker(node) = topic_new;
    hooker_name(node) = (char*)malloc(size);
    memcpy(hooker_name(node),content,size);
    _nodes.push_back(node);
    /* insert failed, must free node memory */
    if(! this->_insert(node)){
        topic_free(hooker(node));
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
        int result = topic_cmp(hooker(data),hooker(here));
        //int result = memcmp(data->_data,here->_data,here->_size);
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

void rbtrees::erase(const char *cnt)
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
		if (hooker(node) != NULL) {
            topic_free(hooker(node));
        }
        free(node);
        node = NULL;
    }
}

rbnode* rbtrees::_search(rb_root_t *root, const char* content)
{
    rb_node_t *node = root->rb_node;
    while (node) {
        rbnode *data = container_of(node, rbnode, _rbnode);
        int result = strcmp(content,hooker_name(data));
        if (result < 0)
            node = node->rb_left;
        else if (result > 0)
            node = node->rb_right;
        else
            return data;
    }
    return NULL;
}

rbnode* rbtrees::search(const char* content)
{
    return _search(_root,content);
}

void rbtrees::traverse(const char* content)
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
        // printf("name: %s level:%s\n", (char*)(hooker_name(rbn)),(char*)(hooker_lev(rbn)));
        printf("%s ", (char*)(hooker_name(rbn)));
        node = rb_next(node);
    }
    printf("\n");
}
