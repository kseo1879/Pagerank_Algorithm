#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <omp.h>
#include "pagerank.h"

void pagerank(list* plist, int ncores, int npages, int nedges, double dampener) {

    /*
        to do:
        - implement this function
        - implement any other necessary functions
        - implement any other useful data structures
    */

    omp_set_num_threads(ncores);

    double dampener_in = dampener;

    //First we need a place to store the page rank scores and initialize them
    double *p_rank = malloc(sizeof(double) * (plist->length * 2));

    //Initial page rank score
    double initial_score = ((double) 1 / npages);

    //Initialization of double th length of plist. 
    for(int i = 0; i < (plist->length * 2); i ++) {
        p_rank[i] = initial_score;
    }

    //This is to check the index of previous and current index. 
    int current_index = 0;
    int prev_index = 1;
   
    //Here is some of the variable that we need for the calculation
    double converged_sum = 0;

    //cursor is the current page while inlink_node would the in linklink pages to the cursor
    node *cursor_1 = NULL;
    // node *inlink_node = NULL;

    //To minimize calculation here is the first part of the equation which is equal in most terms. 
    double first_calculation = ((1 - dampener_in) / npages);

    int plist_length = npages;
    // int inlink_length = 0;

    // Tempory array to store the conversenge sum.
    // double *temp_sum = malloc(sizeof(double) * plist_length);

    //Make a plist
    node **cursor = (node **)malloc(sizeof(node *) * plist_length);

    cursor_1 = plist->head;

    //Store the pages inside plist into the cursor array
    for(int i = 0; i < plist_length; i++) {
        cursor[i] = (cursor_1);
        cursor_1 = cursor_1->next;
    }


    while(1) {
        // cursor  = plist->head;
        converged_sum = 0;

        #pragma omp parallel for
        for(int i = 0; i < plist_length; i ++) {

            double inner_sum = 0;
            int inlink_length = 0;
            // int offset = prev_index * plist_length;

            //This means that there is a page that is comminginto this page. 
            if(cursor[i]->page->inlinks != NULL) {
                //Initialization
                node *inlink_node = cursor[i]->page->inlinks->head;
                inlink_length = cursor[i]->page->inlinks->length;

                for(int j = 0; j < inlink_length; j ++) {
                    inner_sum += (p_rank[inlink_node->page->index * 2 + prev_index] 
                        / inlink_node->page->noutlinks);
                    inlink_node = inlink_node->next;
                }

            }
            //Now we need to update the pscores
            p_rank[i * 2 + current_index] = first_calculation + (dampener_in * inner_sum);

        }        
        // #pragma omp parallel for
        // for(int i = 0; i < plist_length; i ++) {
        //     double temp = p_rank[i * 2 + current_index] - p_rank[i * 2 + prev_index];
        //     temp_sum[i] = (temp * temp);
        //     // converged_sum += pow(p_rank[current_index  * plist_length + i] - p_rank[prev_index * plist_length + i], 2);
        // }

        // for(int i = 0; i < plist_length; i ++) {
        //     converged_sum += temp_sum[i];
        // }

        //Parallel version of the code worsen the performance
        for(int i = 0; i < plist_length; i ++) {
            double temp = p_rank[i * 2 + current_index] - p_rank[i * 2 + prev_index];
            converged_sum += (temp * temp);
            // converged_sum += pow(p_rank[current_index  * plist_length + i] - p_rank[prev_index * plist_length + i], 2);
        }

        //The end condition
        if(EPSILON >= sqrt(converged_sum)) {
            for (int i = 0; i < plist_length; i++) {
                printf("%s %.4lf\n", cursor[i]->page->name, p_rank[i * 2 + current_index]);
                // cursor = cursor[i]->next;
            }
            break;
            
        } else {
            //We need to change the current index and previous index to continue with the interation
            int temp = 0;
            temp = current_index;
            current_index = prev_index;
            prev_index = temp;
        }
    }

    // free(temp_sum);
    free(p_rank);
    free(cursor);
}

/*
######################################
### DO NOT MODIFY BELOW THIS POINT ###
######################################
*/

int main(void) {

    /*
    ######################################################
    ### DO NOT MODIFY THE MAIN FUNCTION OR HEADER FILE ###
    ######################################################
    */

    list* plist = NULL;

    double dampener;
    int ncores, npages, nedges;

    /* read the input then populate settings and the list of pages */
    read_input(&plist, &ncores, &npages, &nedges, &dampener);

    /* run pagerank and output the results */
    pagerank(plist, ncores, npages, nedges, dampener);

    /* clean up the memory used by the list of pages */
    page_list_destroy(plist);

    return 0;
}
