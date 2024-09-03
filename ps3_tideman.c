#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define max_candidates 9  //defined instead of const_int because a static array cannot be 'variably modified' hence max_candidates cannot be a Variable

int preferences[max_candidates][max_candidates];  //preferences[i][j] would be count of voters who prefer 'i' over 'j'

bool locked[max_candidates][max_candidates];  //locked arrays to prevent any changes while detecting cycles

typedef struct  //pair data type of winners and losers
{
    int winner;
    int loser;
}
pair;

string candidates[max_candidates];  //array & counts of candidates and pairs
pair pairs[max_candidates * (max_candidates - 1) / 2];

int candidate_count;
int pair_count;


bool vote(int input_order, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool has_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    if (argc < 2)  //checking for invalid use-case 1
    {
        printf("Usage: tideman [candidate1 candidate2 ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > max_candidates)  //checking for invalid use-case 2
    {
        printf("Maximum number of candidates is %i\n", max_candidates);  
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)  //populating the array of candidates
    {
        candidates[i] = argv[i + 1];
    }

    
    for (int i = 0; i < candidate_count; i++)  //ensuring each new run of the program removes 'locked = true' for all pairs
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;  //for resetting pairs each time new vote is taken
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)  //collecting names in the ranking order
    {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)  //function to fill the ranks array
        {
            string name = get_string("Rank %i: ", j + 1);

            if (vote(j, name, ranks) == false)
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        printf("\n");
        record_preferences(ranks);
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

bool vote(int input_order, string name, int ranks[])  //adding identifiers for candidates (by their input order) in ranks array for each voter
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[input_order] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)  //adding counts to all win instances where candidate i is ranked better than candidate j
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)  //comparing counts of all 1v1 face-offs between candidate i and j and making winner/loser pair 
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)  //looping to compare pair of pairs to order
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];
            if (strength2 > strength1)
            {
                pair temp = pairs[j];  //swap pairs [j+1] & [j]
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)  //locking non-cycled pairs to prevent overriding while checking for cycles
    {
        if (!has_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)  //checking which opponent is winning 1v1 against each opponent
        {
            if (locked[j][i])
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner)
        {
            printf("%s\n", candidates[i]);  //printing winner
            return;
        }
    }
}

bool has_cycle(int winner, int loser)  //solving for cases where comparison can cycle
{
    if (winner == loser)  //removing equal case
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])  //checking all edges with loser of the pair
        {
            if (has_cycle(winner, i))  //checking if the paired 'i' has any edges with winner
            {
                return true;
            }
        }
    }
    return false;
}
