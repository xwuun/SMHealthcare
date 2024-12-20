//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    char line[100]; //���Ͽ��� �о�� ���ڸ� ������ �迭 
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fgets(line,sizeof(line),file)) {
        sscanf(line,"%s %d",diet_list[diet_list_size].food_name, 
                            &diet_list[diet_list_size].calories_intake); // �����̸��� ���� Į�θ� ���� 
        diet_list_size++;
        //�ִ� ������ �����ϸ� �б⸦ �ߴ��Ѵ�
        if (diet_list_size >= MAX_DIETS) 
			break;
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice,i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for(i=0; i<diet_list_size; i++)
    {
        printf("%d : %s - %d kcal\n",i,diet_list[i].food_name,diet_list[i].calories_intake);
    }
    
	// ToCode: to enter the diet to be chosen with exit option
    // ��ȿ�� diet code�� �Է��� �� ���� �ݺ��Ѵ�.
    while(1)
    {
        printf("\nPlease input diet code : ");
        scanf("%d",&choice);
        if (choice<0||choice>=diet_list_size)
        {
            printf("Diet code Error!!\n");
        } 
        else{
            break;
        }
    }
    printf("\n");
    // ToCode: to enter the selected diet in the health data
    // �Է¹���  diet ������ health data�� �߰��Ѵ�. 
    // �ִ� ������ �����Ͽ��ٸ� �����޽��� ����Ѵ�.
    if(health_data->diet_count== MAX_DIETS)
    {
        printf("Can't add a diet data! Storage is full!!");
        return;
    }

    // �ִ밹���� �ƴ϶�� diet ������ �����Ѵ�
    health_data->diet[health_data->diet_count]=diet_list[choice];
    health_data->diet_count++;

    // ToCode: to enter the total calories intake in the health data
    health_data->total_calories_intake += diet_list[choice].calories_intake;
}
