//
//  cal_healthdata.c
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


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
	int total_cal_burn, total_cal_intake;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for(i=0; i<health_data->exercise_count; i++)
    {
    	// ��̸�, �д� Į�θ� �Ҹ��� �����Ѵ�. 
        fprintf(file,"%s - %d kcal\n",health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
        //�� �Ҹ�� Į�θ� ����ϱ�  
		total_cal_burn += health_data->exercises[i].calories_burned_per_minute;
    }
	fprintf(file, "Total calories burned: %d kcal\n", total_cal_burn);    
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    for(i=0;i<health_data->diet_count;i++)
    {
    	//�����̸�, ���� Į�θ��� �����Ѵ�. 
        fprintf(file,"%s - %d kcal\n",health_data->diet[i].food_name, health_data->diet[i].calories_intake);
        //�� ������ Į�θ� ����ϱ� 
		total_cal_intake += health_data->diet[i].calories_intake;
    }
    fprintf(file, "Total calories intake: %d kcal\n", total_cal_intake);

    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    fprintf(file,"Basal metabolic rate - %d kcal\n",BASAL_METABOLIC_RATE); // ���� ��緮�� ���� 
    fprintf(file,"The remaining calories - %d kcal\n",getRemainCal(health_data)); // ���� Į�θ� ���� 

    fclose(file);
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void recommendation_msg(const HealthData* health_data);

void printHealthData(const HealthData* health_data) {
	int i;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
    for(i=0;i<health_data->exercise_count;i++) // ����Ǿ��ִ� ��� ��������� �����. 
    {
        printf("Exercise %s, Calories burned : %d kcal\n",health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
    }
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for(i=0;i<health_data->diet_count;i++) //����Ǿ��ִ� ��� �Ĵ��������� ���. 
    {
        printf("Food %s, Calories intake: %d kcal\n",health_data->diet[i].food_name, health_data->diet[i].calories_intake);
    }

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
    printf("Basal Metabolic Rate : %d \n",BASAL_METABOLIC_RATE);
    printf("Total calories burned : %d \n", health_data->total_calories_burned );
    printf("Total calories intake : %d \n", health_data->total_calories_intake );
    printf("Total remaining calories: %d kcal\n",getRemainCal(health_data));
    
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    
    recommendation_msg(health_data);
	printf("=======================================================================\n");
}

/*
    description : �ܿ� Į�θ��� ����ϴ� �Լ�
*/
int getRemainCal(const HealthData* health_data)
{
	// �ܿ� Į�θ� = �� ����Į�θ� - �� �Ҹ� Į�θ� - ���ʴ�緮 
    int calorie=health_data->total_calories_intake - 
                health_data->total_calories_burned - BASAL_METABOLIC_RATE;

    return calorie; //����� �ܿ� Į�θ��� ��ȯ 
}

/*
    description : ����ڿ��� ��õ������ ����ϴ� �Լ�
*/

void recommendation_msg(const HealthData* health_data)
{   
    printf("[ Recommendtaion Message ] \n");
    if(getRemainCal(health_data)<0) // �ܿ� Į�θ��� 0���� ���� ��� 
    {
        printf("[Warning] Too few calories!!\n");
        if(health_data->total_calories_intake == BASAL_METABOLIC_RATE) // ������ Į�θ��� ���ʴ�緮�� ������ ��� 
        {
            printf(" *  Your total calories intake for today has reached your goal!\n");
        }
        else if(health_data->total_calories_intake < BASAL_METABOLIC_RATE) // ���� Į�θ��� ���ʴ�緮 ���� ���� ��� 
        {
            printf("Your total calories intake for today has not reached your goal,\n");
            printf("remember to eat more!!\n");
        }
        else{
        	//Į�θ� ���밡 �ʰ��Ǿ����� ����� ����  Į�θ��� ������ ��� 
            printf("You have eaten more calories than planned today,\n");  
            printf("but you have exercised too much!!\n");
        }
    }
    else{ 
    //�ܿ�  Į�θ��� 0�̻��� ��� 
        if(health_data->total_calories_intake == BASAL_METABOLIC_RATE) // ������ Į�θ��� ���ʴ�緮�� ������ ��� 
        {
            printf("Your total calories intake for today has reached your goal!\n");
        }
        else if(health_data->total_calories_intake < BASAL_METABOLIC_RATE) // ������ Į�θ��� ���ʴ�緮 ���� ���� ��� 
        {
            printf("Your total calories intake for today has not reached your goal,\n");
            printf("remember to eat more!!\n");
        }
    }
}
