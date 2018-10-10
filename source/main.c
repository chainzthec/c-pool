#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "database.h"
#include "access/ingredient.h"
#include "access/recipe.h"


int main(int argc, char** argv)
{
    MYSQL* connection = connectToDatabase();

    struct Ingredient* i = getAllIngredients(connection);
    displayIngredientsList(i);
    /** example of filter on the list */
    while (i) {
        if (i->price != 0) {
            i = i->next;
            continue; // if price isn't 0, don't print it
        }
        fprintf(stdout, "%s\n", i->name);
        i = i->next;
    }
    freeIngredientList(i);

    struct Recipe* r = getAllRecipes(connection);
    displayRecipesList(r);
    /** example of filter on the list */
    while (r) {
        fprintf(stdout, "%s\n", r->name);
        r = r->next;
    }
    freeRecipesList(r);


    mysql_close(connection);
    return EXIT_SUCCESS;
}
