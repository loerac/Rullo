#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

unsigned long one = 1;

typedef struct complete_set_struct {
    uint32_t value;
    struct complete_set_struct *next;
} set_s;

static set_s *head = NULL;
static uint32_t set_length = 0;

/********************************************************
 * INPUTS:
 *      val_str - The string value integer
 *      val_int - The output for the string value converted
 *
 * OUTPUTS:
 *      val_int - The string value converted to an
 *                unsigned int
 * RETURN:
 *       true - Success
 *      false - Failure
 *
 * DeSCRIPTION:
 *      Converts a string to an unsigned integer.
 ********************************************************/
static bool ok_strtol(const char *const val_str, uint32_t *val_int) {
    bool ok = false;
    char *endptr = NULL;
    uint32_t val = (uint32_t)strtol(val_str, &endptr, 10);

    if (    (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
            (errno != 0 && val == 0)) {
        printf("Error: Failed on converting string to usigned int - string(%s) error(%m)\n", val_str);
    } else if (endptr == val_str) {
        printf("Error: No digits were found - string(%s)\n", val_str);
    } else {
        ok = true;
        *val_int = val;
    }

    return ok;
}

/********************************************************
 * INPUTS:
 *      value - Data being added to the list
 *
 * OUTPUTS:
 *      head - The data being inserted prepended to the
 *             linked list
 *
 * RETURN:
 *      NONE
 *
 * DeSCRIPTION:
 *      See INPUTS
 ********************************************************/
static bool insertFirst(const uint32_t value) {
    bool ok = true;
    set_s* temp = (set_s*)calloc(1, sizeof(set_s));

    if (NULL != temp) {
        temp->value = value;
        temp->next = head;
        head = temp;
        ++set_length;
    } else {
        printf("Error: Allocating memory failed - error(%m)\n");
        ok = false;
    }

    return ok;
}

/********************************************************
 * INPUTS:
 *      NONE
 *
 * OUTPUTS:
 *      head - The first item in the list being removed
 *
 * RETURN:
 *      NONE
 *
 * DeSCRIPTION:
 *      Removes the first item in the linked list. Can be
 *      called in a loop to remove all items in the list.
 ********************************************************/
static void deleteFirst( void ) {
    set_s *temp = head;
    if (NULL != temp) {
        head = head->next;
        free(temp);
        --set_length;
    }
}

/********************************************************
 * INPUTS:
 *      NONE
 *
 * OUTPUTS:
 *      NONE
 *
 * RETURN:
 *      NONE
 *
 * DeSCRIPTION:
 *      Prints what is currently in the list
 ********************************************************/
static void printList( void ) {
    set_s *temp = head;

    printf("Found combination: [ ");
    while(temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("]\n");
}

/********************************************************
 * INPUTS:
 *      NONE
 *
 * OUTPUTS:
 *      NONE
 *
 * RETURN:
 *      sum - All the values in the linked list added up
 *
 * DeSCRIPTION:
 *      See RETURN
 ********************************************************/
static uint32_t sum( void ) {
    uint32_t sum = 0;
    set_s *temp;

    for(temp = head; temp != NULL; temp = temp->next) {
        sum += temp->value;
    }

    return sum;
}

/********************************************************
 * INPUTS:
 *        size - Size of the array
 *        need - How much bits needed to find combination
 *        list - Complete valid set
 *       rullo - Number that the set should equal
 *      chosen - Using bits to indicate what's chosen
 *          at - Current index location
 *
 * OUTPUTS:
 *      NONE
 *
 * RETURN:
 *      NONE
 *
 * DeSCRIPTION:
 *      Find all the combinations from the list
 *
 *      Implementing the combinatorics code from Rosetta Code
 *      http://rosettacode.org/wiki/Combinations#C.2B.2B
 ********************************************************/
static void comb(const uint32_t size,
                 const uint32_t need,
                 const uint32_t list[],
                 const uint32_t rullo,
                 const unsigned long chosen,
                 uint32_t at) {
    if (size < need + at) {
        return;
    }

    if (!need) {
        for (at = 0; at < size; at++) {
            if (chosen & (one << at)) {
                insertFirst(list[at]);
            }
        }

        if (sum() == rullo) {
            printList();
        }

        while (NULL != head) {
            deleteFirst();
        }
        free(head);
        return;
    }

    // If we choose the current item, "or" (|) the bit to mark it so.
    comb(size, need - 1, list, rullo, chosen | (one << at), at + 1);

    // Or don't choose it, go to next
    comb(size, need, list, rullo, chosen, at + 1);
}

int main(int argc, char **argv) {
    bool ok = true;
    if(argc < 3) {
        printf("Error: No arguments given: %s [rullo number] [set of row/column]\n", argv[0]);
        ok = false;
    }

    uint32_t i = 0;
    uint32_t rullo = 0;
    if ( ok && (! ok_strtol(argv[1], &rullo)) ) {
        ok = false;
        printf("Error: Failed to retrieve rullo number - rullo string(%s)\n", argv[1]);
    }

    if ( ok ) {
        for(i = 2; i < argc; i++) {
            uint32_t set = 0;
            if ( ok_strtol(argv[i], &set) ) {
                if ( set <= rullo ) {
                    insertFirst(set);
                }
            } else {
                ok = false;
                printf("Error: Failed to retrieve set number - set(%s)\n", argv[i]);
                break;
            }
        }
    }

    if ( ok ) {
        /*
         * Found all valid set numbers. Create
         * an array and store them. Then delete
         * the linked list.
         */
        uint32_t const SIZE = set_length;
        uint32_t list[SIZE];
        memset(list, 0, SIZE);
        for(i = 0; i < SIZE; i++) {
            list[i] = head->value;
            head = head->next;
        }

        while (NULL != head) {
            deleteFirst();
        }
        free(head);

        printf("Rullo number: %d\n", rullo);
        printf("Accepted set: [ ");
        for(i = 0; i < SIZE; i++) {
            printf("%d ", list[i]);
        }

        printf("]\n==========================================\n");
        for(i = 0; i < (SIZE + 1); i++) {
            comb(SIZE, i, list, rullo, 0, 0);
        }
        printf("\n");
    }

    return 0;
}
