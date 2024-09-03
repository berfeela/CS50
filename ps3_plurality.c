#include "cs50.h"
#include <stdio.h>
#include <string.h>

#define max_candidates 9  //defined instead of const_int because a static array cannot be 'variably modified' hence max_candidates cannot be a Var

typedef struct  //candidate data type which will have a name and count of 'votes'
{
    string name;
    int votes;
}
candidate;

candidate candidates[max_candidates]; 

int candidate_count; //global var to allow usage in vote, print_winner & main fns

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)  //checking for invalid use case 1
    {
        printf("Usage: plurality [candidate1 candidate2 ...]\n");
        return 1;
    }

    candidate_count = argc - 1;  //initialize the global candidate_count

    if (candidate_count > max_candidates)  //checking for invalid use case 2
    {
        printf("Maximum number of candidates is %i\n", max_candidates);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)  //populating array of candidates
    {
        candidates[i].name = argv[i + 1];  //adjusting argument variable index to array index
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)  //collecting votes from each voter
    {
        string name = get_string("Vote: ");

        if (vote(name) == false)  //invalid vote case
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}


bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)  //count votes by using string compare
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}


void print_winner(void)
{
    int max_votes = 0;

    for (int i = 0; i < candidate_count; i++)  //finding out the max vote count of any candidate
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)  //printing candidates with 'max votes'
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
