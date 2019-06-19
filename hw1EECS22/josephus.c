/* Assignment 1: Josephus Problem */
/*Author: Anderson Nguyen ID#68319094 */

#include <stdio.h>

int josephus_survivor(int number_of_people)
{
    /* one array keeps track of the kills for each person and the other array keeps track whether they are alive */
    int points[number_of_people];
    int person_status[number_of_people];

    /* initializes the size of the array and if they are alive or dead */
    int i;
    for (i = 0; i < number_of_people; i++)
    {
        points[i] = 0;
        person_status[i] = 1;   /* sets value of each person in array to 1. 1 means they are alive */
    }
        
    int remaining_people = number_of_people;
    int current_person_index = 0;

    /* continues until 1 person is left */
    while (remaining_people > 1)
    {
        /* determine if the person after the current person is alive or dead. */
        if (person_status[current_person_index] == 1)
        {
            int next_person_index = 1;
            /* find the next person to kill. Uses modulo to allow it to loop back to beginning */
            while (person_status[(current_person_index + next_person_index)%number_of_people] != 1)
            {
                next_person_index++;
            }
            
            /* the person to kill is the offset of the person trying to kill. We use modulo to loop back to the beginniing */
            int person_to_kill_index = (current_person_index + next_person_index) % number_of_people;
            
            /* we kill a person by setting their value to 0 */
            person_status[person_to_kill_index] = 0;

            /* gives the person a point for killing */
            points[current_person_index] = points[current_person_index] + 1;

            /* subtracts from the total amount of people after a person is killed */
            remaining_people--;

            /* selects next executioner */
            current_person_index = (person_to_kill_index + 1) % number_of_people;
        } 			
        else
        {
            current_person_index++;
        }
    }
    /* tells us the winner of Josephus Problem */
    int position;
    for (position = 0; position < number_of_people; position++) 
    {
        if (person_status[position] == 1)
        {  
            printf("The spot %d is safe.\nMost executions by an individual are %d\n", position + 1, points[position]);
        }  
    }
    return 0;
}

int main()
{
    int user_input;

    /* asks user to input the # of people and stores # in variable */
    printf("How many people are in the circle? ");
    scanf("%d", &user_input);

    josephus_survivor(user_input);

    return 0;
}
