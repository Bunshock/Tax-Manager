/*
 * avlt.c
 *
 * TAD avlt implementation 
 */
#include <stdlib.h>
#include <assert.h>

#include "avlt.h"

struct _avlt_t {
    info_t data;
    avlt_t left;
    avlt_t right;
};

avlt_t avlt_empty() {
    avlt_t tree = NULL;
    tree = (avlt_t) calloc(1, sizeof(struct _avlt_t));
    tree->data = NULL;
    tree->left = NULL;
    tree->right = NULL;
    assert(tree != NULL);
    return tree;
}

avlt_t do_avlt_add(avlt_t tree, info_t data) {
    assert(tree != NULL && data != NULL);

    if(tree->data == NULL)
        tree->data = data;
    else if(eq_period(data->period, tree->data->period)) {
        tree->data = destroy_info(tree->data);
        tree->data = data;
    }
    else if(comes_before(data->period, tree->data->period)) {
        if(tree->left == NULL)
            tree->left = avlt_empty();
        tree->left = avlt_add(tree->left, data);
    }
    else {
        if(tree->right == NULL)
            tree->right = avlt_empty();
        tree->right = avlt_add(tree->right, data);
    }

    return tree;
}

avlt_t avlt_add(avlt_t tree, info_t data) {
    /*First, add the node to the tree */
    tree = do_avlt_add(tree, data);
    /* Now, balance the tree */
    /* ...to be implemented... */
    return tree;
}

info_t avlt_info(avlt_t tree, period_t period) {
    assert(tree != NULL && period != NULL);

    info_t info = NULL;

    if(eq_period(period, tree->data->period))
        info = tree->data;
    else if(comes_before(period, tree->data->period) && tree->left != NULL)
        info = avlt_info(tree->left, period);
    else if(!comes_before(period, tree->data->period) && tree->right != NULL)
        info = avlt_info(tree->right, period);

    return info;
}

bool avlt_contains(avlt_t tree, period_t period) {
    assert(tree != NULL && period != NULL);
    return avlt_info(tree, period) != NULL;
}

unsigned int avlt_length(avlt_t tree) {
    assert(tree != NULL);
    unsigned int length = 0;
    if(tree->data != NULL) {
        length++;
        if(tree->left != NULL)
            length += avlt_length(tree->left);
        if(tree->right != NULL)
            length += avlt_length(tree->right);
    }
    return length;
}

avlt_t avlt_remove(avlt_t tree, period_t period) {
    assert(tree != NULL && period != NULL);

    if(!avlt_contains(tree, period))
        return tree;

    avlt_t root = tree;
    avlt_t tree_prev = tree;
    bool dir = false;
    //Look for the word position in the tree
    while(!eq_period(period, tree->data->period)) {
        dir = comes_before(period, tree->data->period);  //dir = true -> me moved to the left, dir = false -> we moved to the right.
        tree_prev = tree;
        tree = dir ? tree->left : tree->right;
    }

    tree->data = destroy_info(tree->data);
    //No children: tell our parent that this node is empty.
    if(tree->left == NULL && tree->right == NULL) {
        if(tree != root)
            *(dir ? &tree_prev->left : &tree_prev->right) = NULL;
    }
    //Only one child: we tell our parent to point to our child, and free our node.
    //else if((right == NULL && left != NULL) || (right != NULL && left == NULL))
    else if((tree->right == NULL) != (tree->left == NULL)) {
        avlt_t aux = NULL;
        aux = tree->right == NULL ? tree->left : tree->right;
        if(tree != root)
            *(dir ? &tree_prev->left : &tree_prev->right) = aux;    
        else
            root = aux;
    }
    //We have both children: we look for our inorder successor.. that means: if our right child has a left child, we take the
    //leftmost child.. if our right child has no left child, we take our right child.
    else {
        avlt_t aux = NULL;
        aux = tree->right->left == NULL ? tree->right : tree->right->left;
        //If our right child has no left child:
        if(aux == tree->right) {
            aux->left = tree->left;
            if(tree != root)
                *(dir ? &tree_prev->left : &tree_prev->right) = aux;
            else
                root = aux;
        }
        //If our right child has left child:
        else {
            avlt_t aux_prev = tree->right;
            //we look for the leftmost key under tree->right, and its parent
            while(aux->left != NULL) {
                aux_prev = aux;
                aux = aux->left;
            }
            aux_prev->left = aux->right;
            aux->right = tree->right;
            aux->left = tree->left;
            if(tree != root)
                *(dir ? &tree_prev->left : &tree_prev->right) = aux;
            else
                root = aux;
        }
    }
    
    if((tree->left != NULL || tree->right != NULL) && (tree != root)) {
        free(tree);
        tree = NULL;
    }

    return root;
}

avlt_t avlt_remove_all(avlt_t tree) {
    assert(tree != NULL);
    unsigned int length = avlt_length(tree);
    while(length > 0) {
        tree = avlt_remove(tree, tree->data->period);
        length = avlt_length(tree);
    }
    assert(tree != NULL && avlt_length(tree) == 0);
    return tree;
}

void avlt_dump(avlt_t tree, FILE *file) {
    assert(tree != NULL && file != NULL);
    
    if(tree->left != NULL)
        avlt_dump(tree->left, file);

    info_dump(tree->data, file);

    if(tree->right != NULL)
        avlt_dump(tree->right, file);
}

avlt_t avlt_destroy(avlt_t tree) {
    assert(tree != NULL);
    tree = avlt_remove_all(tree);
    free(tree);
    tree = NULL;
    return tree;
}
