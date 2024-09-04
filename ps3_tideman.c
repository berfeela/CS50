#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define max_candidates 9  //defined instead of const_int because a static array cannot be 'variably modified' hence max_candidates cannot be a Variable

int preferences[max_candidates][max_candidates];  //preferences[i][j] would be count of times 'i' over 'j' was preferred in votes

bool locked[max_candidates][max_candidates];  //locked arrays to prevent cycles

typedef struct  //pair data type to denote ranked pairs of winners and losers
{
    int winner;
    int loser;
}
pair;

string candidates[max_candidates];  //array & counts of candidates and pairs
pair pairs[max_candidates * (max_candidates - 1) / 2];
int candidate_count;
int pair_count;


bool vote(int cand_order, string cand_name, int cand_ranks[]);
void record_preferences(int cand_ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool has_cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)  //checking for invalid use-case 1: not enough candidates
    {
        printf("Usage: tideman [candidate1 candidate2 ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > max_candidates)  //checking for invalid use-case 2: too many candidates
    {
        printf("Maximum number of candidates is %i\n", max_candidates);  
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)  //populating the array of all candidates
    {
        candidates[i] = argv[i + 1];
    }

    
    for (int i = 0; i < candidate_count; i++)  //ensuring each new run of the program unlocks all values in locked[i][j]
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;  //resetting ranked pair count each time new vote is taken to accommodate new ranks --> preferences --> pairs

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)  //collecting names in the ranked order
    {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)  //function to fill ranks[i][j]
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

bool vote(int cand_order, string cand_name, int cand_ranks[])  //given the order & name in a vote, this fn writes candidate's id in the given array in the same order
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(cand_name, candidates[i]) == 0)
        {
            cand_ranks[cand_order] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int cand_ranks[])
{
    for (int i = 0; i < candidate_count; i++)  //populating preferences table in indices where the candidate is winning e.g. rank 0 vs. (rank 1 || rank 2)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[cand_ranks[i]][cand_ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)  //checking for a candidate's performance vs other candidates and creating [total of n(n-1)/2] ranked pairs of winners & losers
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
    for (int i = 0; i < pair_count - 1; i++)  //bubble sorting to find the edge/win with the least strength 
    {
        for (int j = 0; j < pair_count - i - 1; j++)  //after each iteration i we need to run (pair_count - i) times
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];
            if (strength2 > strength1)
            {
                pair temp = pairs[j];  //swapping pairs [j+1] & [j] to bubble up larger strength edges
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)  //locking edges that will not initiate a cycle, only winners from locked[] would be chosen
    {
        if (!has_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool has_cycle(int winner, int loser)
{
    if (winner == loser)  //detecting the cycle's formation in the recursion ++ eliminating self-pair edge-case from locked array
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)  //calling locked recursively to check whether loser has any edges
        {
            if (has_cycle(winner, i) == true)  //checking if the edge loser has is connecting back to winner OR if it is the winner
            {
                return true;
            }
        }
    }
    return false;
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)  //checking whether a candidate is losing any 1v1 against another
        {
            if (locked[j][i])
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner)
        {
            printf("%s\n", candidates[i]);  //printing winner when there is no locked win from an opponent found
            return;
        }
    }
}
